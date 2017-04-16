USE ann;

SELECT DISTINCT species 
FROM iris;

SELECT COUNT(DISTINCT species) 
FROM iris;

SELECT COUNT(*)
FROM iris
GROUP BY species
HAVING COUNT(*) > 1;

(SELECT * FROM iris 
WHERE species='setosa'
ORDER BY RAND()
LIMIT 10)
UNION
(SELECT * FROM iris 
WHERE species='versicolor'
ORDER BY RAND()
LIMIT 10)
UNION
(SELECT * FROM iris 
WHERE species='virginica'
ORDER BY RAND()
LIMIT 10)
ORDER BY RAND();

/*Pick 10 random rows*/
SELECT * FROM iris
ORDER BY RAND()
LIMIT 10;

/*Pick a random row from iris*/
SELECT *
  FROM iris AS r1 JOIN
       (SELECT CEIL(RAND() *
                     (SELECT MAX(ID)
                        FROM iris)) AS id)
        AS r2
 WHERE r1.id >= r2.id
 ORDER BY r1.id ASC
 LIMIT 1;

SELECT COUNT(DISTINCT activity) 
FROM arem;

SELECT COUNT(*)
FROM arem
GROUP BY activity
HAVING COUNT(*) > 1;


SELECT *
FROM arem
WHERE avg_rss12=0 AND var_rss12=0 AND avg_rss13=0 AND var_rss13=0 AND avg_rss23=0 AND var_rss23=0;

SELECT *
FROM arem
WHERE activity='';


/*Pick a random row from arem*/
SELECT *
  FROM arem AS r1 JOIN
       (SELECT CEIL(RAND() *
                     (SELECT MAX(ID)
                        FROM arem)) AS id)
        AS r2
 WHERE r1.id >= r2.id
 ORDER BY r1.id ASC
 LIMIT 1;

SELECT DISTINCT activity
FROM arem;

/*ALTER TABLE arem DROP COLUMN time;*/

SHOW TABLES;