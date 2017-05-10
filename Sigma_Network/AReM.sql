DROP SCHEMA IF EXISTS arem;
CREATE SCHEMA arem;
USE ann;

DROP TABLE IF EXISTS `arem`;

CREATE TABLE `arem` (
    `ID` INT(11) NOT NULL AUTO_INCREMENT,
    `time` FLOAT NOT NULL,
    `avg_rss12` FLOAT NOT NULL,
    `var_rss12` FLOAT NOT NULL,
    `avg_rss13` FLOAT NOT NULL,
    `var_rss13` FLOAT NOT NULL,
    `avg_rss23` FLOAT NOT NULL,
    `var_rss23` FLOAT NOT NULL,
    `activity` CHAR(20) NOT NULL,
    PRIMARY KEY (`ID`)
);

/*LOAD DATA LOCAL INFILE '/home/michael/datatest/bending1/dataset1.csv' INTO TABLE arem 
    FIELDS TERMINATED BY ',' 
    LINES TERMINATED BY '\n'
    (time, avg_rss12, var_rss12, avg_rss13, var_rss13, avg_rss23, var_rss23, activity);*/


/*time,avg_rss12,var_rss12,avg_rss13,var_rss13,avg_rss23,var_rss23,activity*/

/*C:/Users/Michael/Source/Repos/ANN/Sigma_Network/

SELECT order_id,product_name,qty
FROM orders
WHERE foo = 'bar'
INTO OUTFILE '/var/lib/mysql-files/orders.csv'
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n';

*/