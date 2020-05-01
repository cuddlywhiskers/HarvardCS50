-- write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred
-- Kevin Bacon born in 1958.
-- Kevin Bacon himself should not be included in the resulting list.

SELECT
    DISTINCT name AS name
FROM people
JOIN stars
    ON people.id = stars.person_id
WHERE stars.movie_id IN
    (SELECT
        movie_id
    FROM stars
    WHERE person_id in
        (SELECT
            id
        FROM people
        WHERE name = 'Kevin Bacon'
        AND birth = 1958))
AND name != 'Kevin Bacon'
