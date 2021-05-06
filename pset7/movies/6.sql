SELECT SUM(rating) / COUNT(*) title
FROM movies
JOIN ratings ON ratings.movie_id = movies.id
WHERE year = 2012;