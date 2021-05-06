SELECT name FROM people
WHERE id IN
(SELECT person_id from stars
WHERE movie_id =
(SELECT id from movies
WHERE title = "Toy Story"));