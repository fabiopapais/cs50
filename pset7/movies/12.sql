SELECT title from movies
WHERE id IN
    (SELECT movie_id from people
    JOIN stars ON people.id = stars.person_id
        WHERE name = "Johnny Depp")
INTERSECT
SELECT title from movies
WHERE id IN
    (SELECT movie_id from people
    JOIN stars ON people.id = stars.person_id
        WHERE name = "Helena Bonham Carter");
