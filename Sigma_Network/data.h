/*
This is a class definition for Sigma Net, which is a simple
Artificial Neural Network

Copyright(C) 2016  Michael Brett Koonts

This program is free software : you can redistribute it and / or modify
it under the terms of the GNU Affero General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//============================================================================
//   File:          data.h
//   Author:        Michael Koonts
//   Date:          March 26, 2017
//   Description:   Class definition of data
//============================================================================
#pragma once
#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/resultset_metadata.h>

using namespace std;

class data
{

private:
    // Specify our connection target and credentials
    string server;
    string username;
    string password;
    string database;
    string table;
    string catagories;
    int catagoryCount = 0;
    vector<string> catagoryNames;
    // Create a pointer to a MySQL driver object
    sql::Driver *driver;
    // Create a pointer to a database connection object
    sql::Connection *dbConn;

    map<string, vector<double>> typeToVector;
    map<vector<double>, string> vectorToType;
    map<string, int> sampleCounts;
    
 
public:
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    data(string server = "tcp://127.0.0.1:3306",
         string username = "neuralnet", 
         string password = "tenlaruen", 
         string database = "ann");
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    ~data();
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    void connect();
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    void collectMetaData();
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    void printMetaData();
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    void printResultSet(sql::ResultSet *results);
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    vector<vector<double>> getTrainingSet();
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    vector<vector<double>> getTestSet();
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    void testQuery();
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    void printVector(vector<string> vec);
    void printVector(vector<double> vec);
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    vector<double> classVector(int length, int onePosition);
};

#endif