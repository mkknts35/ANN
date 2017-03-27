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
data::data()
{
    try{
        // Try to get a driver to use to connect to our DBMS
		driver = get_driver_instance();
        // Try to connect to the DBMS server
        dbConn = driver->connect(server, username, password);
        // Specify which connection our SQL statement should be executed on
        stmt = dbConn->createStatement();
        // Try to query the database
        // Select which database to use. Notice that we use "execute" to perform a command.
        stmt->execute("USE ann");
         // Perform a query and get the results. Notice that we use "executeQuery" to get results back
        res = stmt->executeQuery("SHOW TABLES");
        // While there are still results (i.e. rows/records) in our result set...
        while (res->next())
        {
            // ...get each field we want and output it to the screen
            // Note: The first field/column in our result-set is field 1 (one) and -NOT- field 0 (zero)
            // Also, if we know the name of the field then we can also get it directly by name by using:
            // res->getString("TheNameOfTheField");
            cout << res->getString(1) << endl;
            res1 = stmt->executeQuery("SHOW FIELDS FROM " + res->getString(1));
            while (res1->next()){
                cout << res1->getString(1) << endl;
            }
            int columns = res1->rowsCount();
            cout << columns << endl;
            res1 = stmt->executeQuery("SELECT * FROM " + res->getString(1));
            cout << res1->rowsCount() << endl;
            while (res1->next()){
                for(int i = 1; i <= columns; i++){
                    cout << res1->getString(i);
                    if(i < columns){
                        cout << ", ";
                    }
                }
                cout  << endl;
            }

        }
	}
	catch (sql::MethodNotImplementedException e){
		cout << "Could not get a database driver. Error message: " << e.what() << endl;
	}catch (sql::InvalidArgumentException e){
		cout << "Could not connect to database. Error message: " << e.what() << endl;
	}catch (sql::SQLException e)	{
		cout << "SQL error. Error message: " << e.what() << endl;
	}
 
}
//============================================================================
data::~data()
{
    delete res;
	delete stmt;
	delete dbConn;
}
//============================================================================