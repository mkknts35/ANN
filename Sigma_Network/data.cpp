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
    this->m_server = server;
    this->m_username = username;
    this->m_password = password;
    this->m_database = database; 
    m_workingSet = make_shared<vector<sample>>();
}
//============================================================================
data::~data()
{
	delete m_dbConn;
}
//============================================================================
void data::connect(){
    sql::Statement *stmt;   
    sql::ResultSet *res, *res1;
    sql::ResultSetMetaData *rsmd;
    try{
		m_driver = get_driver_instance();
        m_dbConn = m_driver->connect(m_server, m_username, m_password);
        stmt = m_dbConn->createStatement();
        stmt->execute("USE " + m_database);
        res = stmt->executeQuery("SHOW TABLES");
        res->first();
        //m_table = res->getString(1);
        res = stmt->executeQuery("SHOW FIELDS FROM " + m_table);
        res->last();
        m_catagories = res->getString(1);
        m_attributeCount = res->rowsCount() - 2; //ID and catagory shouldn't be included
        res = stmt->executeQuery("SELECT DISTINCT " + m_catagories + " FROM " + m_table);
        res1 = stmt->executeQuery("SELECT COUNT(*) FROM " + m_table + " GROUP BY " 
                                    + m_catagories + " HAVING COUNT(*) > 1");
        int curr = 0;
        vector<double> tmp;
        m_catagoryCount = res->rowsCount();

        while(res->next()){
            m_catagoryNames.push_back(res->getString(1));
            tmp = classVector(m_catagoryCount, curr);
            m_typeToVector[m_catagoryNames.at(curr)] = tmp;
            m_vectorToType[tmp] = m_catagoryNames.at(curr);
            curr++;
        }
        if(m_catagoryCount != res1->rowsCount()){
            cout << "Error: Catagory count mismatch!" << endl;
            exit(1);
        }
        curr = 0;
        while(res1->next()){
            m_sampleCounts[m_catagoryNames.at(curr)] = res1->getInt(1);
            //cout << sampleCounts[catagoryNames.at(curr)] << endl;
            curr++;
        }
	}catch (sql::SQLException e)	{
		cout << "SQL error. Error message: " << e.what() << endl;
	}
}
//============================================================================
void data::init(string database, string table){
    m_database = database;
    m_table = table;
    this->connect();
}
//============================================================================
int data::getCatagoryCount(){
    return m_catagoryCount;
}
//============================================================================
int data::getAttributeCount(){
    return m_attributeCount;
}
//============================================================================
int data::getSampleCount(){
    return m_sampleCount;
}
//============================================================================
string data::getTableName(){
    return m_table;
}
//============================================================================
map<string, vector<double>> data::getTypeToVector(){
    return m_typeToVector;
}
//============================================================================
map<vector<double>, string> data::getVectorToType(){
    return m_vectorToType;
}
//============================================================================
map<string, int> data::getSampleCounts(){
    return m_sampleCounts;
}
//============================================================================
void data::printMetaData(){
    cout << "Database: " << m_database << endl;
    cout << "Table: " << m_table << endl;
    cout << "Catagorized by: " << m_catagories << endl;
    cout << "Catagory names :";
    printVector(m_catagoryNames);
    cout << endl;
    cout << "Distingushed by " << m_attributeCount << " attributes" << endl;
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
shared_ptr<vector<sample>> data::getDataSet(bool training){
    m_workingSet->clear();
    if(training){
        fetchTrainingSet();
    }else{
        fetchDataSet();
    }
    return m_workingSet;
}
//============================================================================
void data::fetchTrainingSet(){

    sql::Statement *stmt;   
    sql::ResultSet *res;
    sql::ResultSetMetaData *rsmd;
    string query = "";
    
    try{
        stmt = m_dbConn->createStatement();
        for(int i = 0; i < m_catagoryCount; i++){
            int limit = m_sampleCounts[m_catagoryNames.at(i)] / 4;
            query = query + "(SELECT * FROM " + m_table 
                    + " WHERE " + m_catagories +"='" + m_catagoryNames.at(i) 
                    + "' ORDER BY RAND() LIMIT " + to_string(limit) + ")";
            if(i != m_catagoryCount - 1){
                query = query + " UNION ";
            }else{
                query = query + " ORDER BY RAND()";
            }
        }
        res = stmt->executeQuery(query);
        m_sampleCount = res->rowsCount();
        rsmd = res->getMetaData();
        int columns = rsmd->getColumnCount();
        while(res->next()){
            //
            sample spl;
            // i starts at 2 because the results are indexed from 1,
            // and the first column is trash for our current purposes
            for(int i = 2; i < columns; i++){
                spl.addValue(res->getDouble(i));
            }
            spl.setClassification(res->getString(columns));
            m_workingSet->push_back(spl);
            //spl.printSample();
        }
	}catch (sql::SQLException e)	{
		cout << "SQL error. Error message: " << e.what() << endl;
	}
}
//============================================================================
void data::fetchDataSet(){

    sql::Statement *stmt;   
    sql::ResultSet *res;
    sql::ResultSetMetaData *rsmd;
    string query = "SELECT * FROM " + m_table + " ORDER BY RAND()";
    
    try{
        stmt = m_dbConn->createStatement();
        //cout << query << endl;
        res = stmt->executeQuery(query);
        m_sampleCount = res->rowsCount();
        //printResultSet(res);
        //res->beforeFirst();
        rsmd = res->getMetaData();
        int columns = rsmd->getColumnCount();
        while(res->next()){
            sample spl;
            // i starts at 2 because the results are indexed from 1,
            // and the first column is trash for our current purposes
            for(int i = 2; i < columns; i++){
                spl.addValue(res->getDouble(i));
            }
            spl.setClassification(res->getString(columns));
            m_workingSet->push_back(spl);
            //spl.printSample();
        }
	}catch (sql::SQLException e)	{
		cout << "SQL error. Error message: " << e.what() << endl;
	}
}
//============================================================================
void data::testQuery(){

    // sql::Statement *stmt;   
    // sql::ResultSet *res;
    // sql::ResultSetMetaData *rsmd;
    // string query = "SELECT * FROM " + table + " ORDER BY RAND()";
    
    // try{
    //     stmt = dbConn->createStatement();
    //     /*for(int i = 0; i < catagoryCount; i++){
    //         int limit = sampleCounts[catagoryNames.at(i)] / 4;
    //         query = query + "(SELECT * FROM " + table 
    //                 + " WHERE " + catagories +"='" + catagoryNames.at(i) 
    //                 + "' ORDER BY RAND() LIMIT " + to_string(limit) + ")";
    //         if(i != catagoryCount - 1){
    //             query = query + " UNION ";
    //         }else{
    //             query = query + " ORDER BY RAND()";
    //         }
    //     }*/
    //     cout << query << endl;
    //     res = stmt->executeQuery(query);
    //     printResultSet(res);
    //     res->beforeFirst();
    //     rsmd = res->getMetaData();
    //     int columns = rsmd->getColumnCount();
    //     while(res->next()){
    //         sample spl;
    //         // i starts at 2 because the results are indexed from 1,
    //         // and the first column is trash for our current purposes
    //         for(int i = 2; i < columns; i++){
    //             spl->addValue(res->getDouble(i));
    //         }
    //         spl->setClassification(res->getString(columns));
    //         workingSet->push_back(spl);
    //     }
	// }catch (sql::SQLException e)	{
	// 	cout << "SQL error. Error message: " << e.what() << endl;
	// }
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