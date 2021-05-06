SELECT name FROM people
WHERE id IN
(SELECT person_id FROM movies
JOIN directors ON movies.id = directors.movie_id
WHERE id IN
(SELECT movie_id from ratings
WHERE rating >= 9.0));