DROP SCHEMA IF EXISTS iris;
CREATE SCHEMA iris;
USE ann;

DROP TABLE IF EXISTS `iris`;

CREATE TABLE `iris` (
    `ID` INT(11) NOT NULL AUTO_INCREMENT,
    `sepal_length` FLOAT NOT NULL,
    `sepal_width` FLOAT NOT NULL,
    `petal_length` FLOAT NOT NULL,
    `petal_width` FLOAT NOT NULL,
    `species` CHAR(20) NOT NULL,
    PRIMARY KEY (`ID`)
);

LOAD DATA LOCAL INFILE 'Iris.csv' INTO TABLE iris 
    FIELDS TERMINATED BY ',' 
    LINES TERMINATED BY '\n'
    (sepal_length, sepal_width, petal_length, petal_width, species);

/*DROP TABLE IF EXISTS `setosa`;

CREATE TABLE `setosa` (
    `ID` INT(11) NOT NULL AUTO_INCREMENT,
    `sepal_length` FLOAT NOT NULL,
    `sepal_width` FLOAT NOT NULL,
    `petal_length` FLOAT NOT NULL,
    `petal_width` FLOAT NOT NULL,
    PRIMARY KEY (`ID`)
);

LOAD DATA LOCAL INFILE 'setosa.csv' INTO TABLE setosa 
    FIELDS TERMINATED BY ',' 
    LINES TERMINATED BY '\n'
    (sepal_length, sepal_width, petal_length, petal_width);

DROP TABLE IF EXISTS `versicolor`;

CREATE TABLE `versicolor` (
    `ID` INT(11) NOT NULL AUTO_INCREMENT,
    `sepal_length` FLOAT NOT NULL,
    `sepal_width` FLOAT NOT NULL,
    `petal_length` FLOAT NOT NULL,
    `petal_width` FLOAT NOT NULL,
    PRIMARY KEY (`ID`)
);

LOAD DATA LOCAL INFILE 'versicolor.csv' INTO TABLE versicolor 
    FIELDS TERMINATED BY ',' 
    LINES TERMINATED BY '\n'
    (sepal_length, sepal_width, petal_length, petal_width);

DROP TABLE IF EXISTS `virginica`;

CREATE TABLE `virginica` (
    `ID` INT(11) NOT NULL AUTO_INCREMENT,
    `sepal_length` FLOAT NOT NULL,
    `sepal_width` FLOAT NOT NULL,
    `petal_length` FLOAT NOT NULL,
    `petal_width` FLOAT NOT NULL,
    PRIMARY KEY (`ID`)
);

LOAD DATA LOCAL INFILE 'virginica.csv' INTO TABLE virginica 
    FIELDS TERMINATED BY ',' 
    LINES TERMINATED BY '\n'
    (sepal_length, sepal_width, petal_length, petal_width);

*/