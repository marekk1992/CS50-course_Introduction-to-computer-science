--In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred. 

SELECT name FROM people
WHERE not name = 'Kevin Bacon' and id IN (SELECT person_id FROM stars WHERE movie_id IN 
(SELECT movie_id FROM stars WHERE person_id =
(SELECT id FROM people WHERE name = 'Kevin Bacon' and birth = 1958)));