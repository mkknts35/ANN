USE ann;

SELECT DISTINCT species 
FROM iris;

SELECT COUNT(DISTINCT species) 
FROM iris;

SELECT COUNT(*)
FROM iris
GROUP BY species
HAVING COUNT(*) > 1;

(SELECT * 
FROM iris 
WHERE species='setosa'
LIMIT 10)
UNION
(SELECT * 
FROM iris 
WHERE species='versicolor'
LIMIT 10)
UNION
(SELECT * 
FROM iris 
WHERE species='virginica'
LIMIT 10);
