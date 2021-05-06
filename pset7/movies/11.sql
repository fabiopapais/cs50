SELECT title FROM movies
JOIN ratings ON ratings.movie_id = movies.id
WHERE movie_id IN
(SELECT movie_id FROM stars
    JOIN people
        ON people.id = stars.person_id
    WHERE name = "Chadwick Boseman")
ORDER BY rating DESC
LIMIT 5;