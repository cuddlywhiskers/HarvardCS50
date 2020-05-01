--  write a SQL query to list the titles and release years of all Harry Potter movies, in chronological order
-- You may assume that the title of all Harry Potter movies will begin with the words “Harry Potter”, and that if a movie title begins with the words “Harry Potter”, it is a Harry Potter movie

SELECT
    title,
    year
FROM movies
WHERE title LIKE "Harry Potter%"
ORDER BY 2
