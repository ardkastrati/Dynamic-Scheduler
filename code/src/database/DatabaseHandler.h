/*
 * DatabaseHandler.h
 *
 *  Created on: 21.01.2016
 *      Author: david
 */

#ifndef DATABASEHANDLER_H_
#define DATABASEHANDLER_H_
#include "../TypesExtern.h"
#include "Database.h"
#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

class DatabaseHandler
{
public:
	DatabaseHandler();
	~DatabaseHandler();
	//char* dataParser(double[][]); //return pointer to an char array
	void initDatabase();
	string dataParserBookkeeping(TaskData* data);
	string dataParserStatistic(TaskData* data);
	void storeData(TaskData* data);
	struct data* dataMiningInquiry(int NumberOfParameters);


private:
	Database* data_bookkeeping;
	Database* data_statistic;
};



#endif /* DATABASEHANDLER_H_ */
