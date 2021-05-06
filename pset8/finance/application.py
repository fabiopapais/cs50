import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    if request.method == "GET":
        user_id = session["user_id"]

        user_current_stocks = db.execute("SELECT * FROM holdings WHERE user_id = :user_id", user_id=user_id)
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=user_id)[0]["cash"]

        filtered_stocks = []
        filtered_total = cash
        for stock in user_current_stocks:
            response = lookup(stock["symbol"])

            name = response["name"]
            price = response["price"]
            total = price * stock["shares"]

            filtered_total += total

            tmp_stock = {
                "symbol": stock["symbol"],
                "name": name,
                "shares": stock["shares"],
                "price": price,
                "total": total
            }

            filtered_stocks.append(tmp_stock)

        return render_template("index.html", stocks=filtered_stocks, cash=cash, total=filtered_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buys stocks and register"""

    if request.method == "GET":
        return render_template("buy.html")
    elif request.method == "POST":
        shares = int(request.form.get("shares"))
        symbol = request.form.get("symbol")

        # Initial validations
        if not shares or not symbol:
            return apology("You must complete all the fields")
        elif shares < 1:
            return apology("Shares must be positive")

        # IEX request and validation
        response = lookup(symbol)
        if response == None:
            return apology("This Symbol doesn't exist")

        stock_name = response["name"]
        price = response["price"]
        user_id = session["user_id"]

        # Getting user current cash and validate to the shares * price
        user_current_cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=user_id)

        user_new_cash = user_current_cash[0]["cash"] - (shares * price)
        if user_new_cash < 0:
            return apology("Can't afford")

        # Subtracting the value from user's cash
        db.execute("UPDATE users SET cash = :user_new_cash WHERE id = :user_id", user_new_cash=user_new_cash, user_id=user_id)

        # Registering the buy in HISTORY table
        db.execute("INSERT INTO history (user_id, symbol, stock_name, price, shares, type) VALUES (:user_id, :symbol, :stock_name, :price, :shares, 'buy')", user_id=user_id, symbol=symbol, stock_name=stock_name, price=price, shares=shares)

        # Registering the buy in HOLDINGS table
        check_hold = db.execute("SELECT * FROM holdings WHERE user_id = :user_id AND symbol = :symbol", user_id=user_id, symbol=symbol)
        if not check_hold:
            db.execute("INSERT INTO holdings (user_id, symbol, shares) VALUES (:user_id, :symbol, :shares)", user_id=user_id, symbol=symbol, shares=shares)
        else:
            db.execute("UPDATE holdings SET shares = shares + :shares WHERE user_id = :user_id AND symbol = :symbol", shares=shares, user_id=user_id, symbol=symbol)

        # future possible implementation (Conditional INSERT/UPDATE)
        # db.execute("CASE WHEN (SELECT * FROM holdings WHERE id = :user_id AND symbol = :symbol) IS NOT NULL THEN UPDATE holdings SET shares = shares + :shares ELSE INSERT INTO holdings (user_id, symbol, shares) VALUES (:user_id, :symbol, :shares) END", user_id=user_id, symbol=symbol, shares=shares)

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]
    if request.method == "GET":
        stocks_history = db.execute("SELECT * FROM history WHERE user_id = :user_id", user_id=user_id)

        for stock in stocks_history:
            if stock["type"] == "sell":
                stock["shares"] = -stock["shares"]
                stock["price"] = stock["price"]

        return render_template("history.html", stocks_history=stocks_history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Shows price of stock"""

    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("You must complete all the fields")

        response = lookup(symbol)

        if response == None:
            return apology("This Symbol doesn't exist")

        name = response["name"]
        symbol = response["symbol"]
        price = response["price"]

        return render_template("quoted.html", name=name, symbol=symbol, price=price)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    elif request.method == "POST":
        primary_password = request.form.get("password")
        confirmed_password = request.form.get("confirmation")
        username = request.form.get("username")

        if not primary_password or not confirmed_password or not username:
            return apology("You must complete all the fields")
        elif primary_password != confirmed_password:
            return apology("The passwords don't match")

        check_username = db.execute("SELECT * FROM users WHERE username = :username", username=username)
        if check_username:
            return apology("This username already exists")
        else:
            password_hash = generate_password_hash(primary_password, method='pbkdf2:sha256', salt_length=8)
            user_id = db.execute("INSERT INTO users (username, hash) VALUES (:username, :password_hash)", username=username, password_hash=password_hash)

            session["user_id"] = user_id

            return redirect("/")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"]
    if request.method == "GET":
        symbols = db.execute("SELECT symbol FROM holdings WHERE user_id = :user_id", user_id=user_id)
        return render_template("sell.html", symbols=symbols)
    elif request.method == "POST":
        symbol = request.form.get("symbol")
        print(request.form)
        shares = int(request.form.get("shares"))
        user_shares = int(db.execute("SELECT shares FROM holdings WHERE user_id = :user_id AND symbol = :symbol", user_id=user_id, symbol=symbol)[0]["shares"])

        print(type(user_shares))

        # Initial validations
        if not shares or not symbol:
            return apology("You must complete all the fields")
        elif shares < 1:
            return apology("Shares must be positive")
        elif user_shares < shares:
            return apology("Too many shares")

        # Getting IEX current price
        response = lookup(symbol)

        # Calculating return
        total_return = response["price"] * shares

        # Updating holdings
        db.execute("UPDATE holdings SET shares = shares - :shares WHERE :user_id AND symbol = :symbol", shares=shares, user_id=user_id, symbol=symbol)
        # Updating cash
        db.execute("UPDATE users SET cash = cash + :total_return WHERE id = :user_id", total_return=total_return, user_id=user_id)
        # Inserting history
        db.execute("INSERT INTO history (user_id, symbol, stock_name, price, shares, type) VALUES (:user_id, :symbol, :stock_name, :price, :shares, 'sell')", user_id=user_id, symbol=symbol, stock_name=response["name"], price=response["price"], shares=shares)

        return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
