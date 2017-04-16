#!/bin/bash

for f in /home/michael/datatest/*/*.csv
do
    mysql -e "LOAD DATA LOCAL INFILE '"$f"' INTO TABLE arem FIELDS TERMINATED BY ',' LINES TERMINATED BY '\n' (time, avg_rss12, var_rss12, avg_rss13, var_rss13, avg_rss23, var_rss23, activity);" -u neuralnet --password=tenlaruen ann
done