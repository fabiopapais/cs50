SELECT name FROM people
WHERE id IN
(SELECT person_id from movies
JOIN stars ON stars.movie_id = movies.id
WHERE year = 2004)
ORDER BY birth;