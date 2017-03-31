/*
This is a class implementation for Sigma Net, which is a simple
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
//   File:      data.cpp
//   Author:    Michael Koonts
//   Date :     March 26, 2017
//============================================================================
#include "data.h"
//============================================================================
data::data(string server,
         string username, 
         string password, 
         string database)
{
    this->server = server;
    this->username = username;
    this->password = password;
    this->database = database; 
}
//============================================================================
data::~data()
{
	delete dbConn;
}
//============================================================================
void data::connect(){
    try{
		driver = get_driver_instance();
        dbConn = driver->connect(server, username, password);
	}catch (sql::SQLException e)	{
		cout << "SQL error. Error message: " << e.what() << endl;
	}
}
//============================================================================
void data::collectMetaData(){
    sql::Statement *stmt;   
    sql::ResultSet *res, *res1;
    sql::ResultSetMetaData *rsmd;
    try{
        stmt = dbConn->createStatement();
        //Select the database
        stmt->execute("USE " + database);
        res = stmt->executeQuery("SHOW TABLES");
        res->first();
        table = res->getString(1);
        res = stmt->executeQuery("SHOW FIELDS FROM " + table);
        res->last();
        catagories = res->getString(1);
        //cout << catagories << endl;
        res = stmt->executeQuery("SELECT DISTINCT " + catagories + " FROM " + table);
        res1 = stmt->executeQuery("SELECT COUNT(*) FROM " + table + " GROUP BY " + catagories + " HAVING COUNT(*) > 1");
        
        //printResultSet(res1);
        //res = stmt->executeQuery("SELECT COUNT(DISTINCT " + catagories + ") FROM " + table);
        //printResultSet(res);
        //res->first();
        int curr = 0;
        vector<double> tmp;
        catagoryCount = res->rowsCount();

        while(res->next()){
            catagoryNames.push_back(res->getString(1));
            tmp = classVector(catagoryCount, curr);
            typeToVector[catagoryNames.at(curr)] = tmp;
            vectorToType[tmp] = catagoryNames.at(curr);
            curr++;
        }
        if(catagoryCount != res1->rowsCount()){
            cout << "Error: Catagory count mismatch!" << endl;
            exit(1);
        }
        curr = 0;
        while(res1->next()){
            sampleCounts[catagoryNames.at(curr)] = res1->getInt(1);
            //cout << sampleCounts[catagoryNames.at(curr)] << endl;
            curr++;
        }
        //cout << catagoryCount << endl;
        // for(int i = 0; i < catagoryCount; i++){
        //     tmp = typeToVector[catagoryNames.at(i)];
        //     printVector(tmp);
        //     cout << endl;
        //     cout << vectorToType[tmp] << endl;
        // }
    }catch (sql::SQLException e)	{
		cout << "SQL error. Error message: " << e.what() << endl;
	} 
}
//============================================================================
void data::printMetaData(){
    cout << "Database: " << database << endl;
    cout << "Table: " << table << endl;
    cout << "Catagorized by: " << catagories << endl;
    cout << "Catagory names :";
    printVector(catagoryNames);
    cout << endl;
}
//============================================================================
void data::printResultSet(sql::ResultSet *results){
    sql::ResultSetMetaData *metaData = results->getMetaData();
    unsigned int columns = metaData->getColumnCount();
    unsigned int rows = results->rowsCount();
    cout << columns << " columns, " << rows << " rows" << endl;
    while (results->next()){
                for(int i = 1; i <= columns; i++){
                    cout << results->getString(i);
                    if(i < columns){
                        cout << ", ";
                    }
                }
                cout  << endl;
            }
}
//============================================================================
vector<vector<double>> data::getTrainingSet(){
    vector<vector<double>> set;
    return set;
}
//============================================================================
vector<vector<double>> data::getTestSet(){
    vector<vector<double>> set;
    return set;
}
//============================================================================
void data::testQuery(){
    // Create a pointer to a Statement object to hold our SQL commands
    sql::Statement *stmt;   
    // Create a pointer to a ResultSet object to hold the results of any queries we run
    sql::ResultSet *res;
    sql::ResultSetMetaData *rsmd;
    try{
        stmt = dbConn->createStatement();
    //     // Select the database
    //     stmt->execute("USE " + database);
    //     // get the names of its tables
        res = stmt->executeQuery("(SELECT * FROM iris WHERE species='setosa' LIMIT 10) UNION (SELECT * FROM iris WHERE species='versicolor' LIMIT 10) UNION (SELECT * FROM iris WHERE species='virginica' LIMIT 10)");
    //     // Look at the results of the query
        printResultSet(res);
    //     res->first();
    //     cout << res->getString(1) << endl;
    //     table = res->getString(1);
    //     res = stmt->executeQuery("SHOW FIELDS FROM " + table);
    //     res->last();
    //     catagories = res->getString(1);
    //     cout << catagories << endl;
    //     res = stmt->executeQuery("SELECT DISTINCT " + catagories + " FROM " + table);
    //     printResultSet(res);
    //     res = stmt->executeQuery("SELECT COUNT(DISTINCT " + catagories + ") FROM " + table);
    //     printResultSet(res);
    //     res->first();
    //     catagoryCount = res->getInt(1);
    //     cout << catagoryCount << endl;       
	}catch (sql::SQLException e)	{
		cout << "SQL error. Error message: " << e.what() << endl;
	}
}
//============================================================================
void data::printVector(vector<string> vec)
{
    cout << "{";
    for (unsigned int i = 0; i < vec.size(); i++) {
        cout << vec.at(i);
        if (i < vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << "}";
}
//============================================================================
vector<double> data::classVector(int length, int onePosition){
    vector<double> cVec;
    for(unsigned int i = 0; i < length; i++){
        if(i == onePosition){
            cVec.push_back(1);
        }else{
            cVec.push_back(0);
        }
    }
    return cVec;
}
//============================================================================
void data::printVector(vector<double> vec)
{
    cout << "(";
    for (unsigned int i = 0; i < vec.size(); i++) {
        cout << vec.at(i);
        if (i < vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << ")";
}
//============================================================================