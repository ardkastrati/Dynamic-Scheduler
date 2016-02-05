/*
 * DatabaseHandler.h
 *
 *  Created on: 21.01.2016
 *      Author: david
 */

#ifndef DATABASEHANDLER_H_
#define DATABASEHANDLER_H_
#include "../TypesExtern.h"

class DatabaseHandler
{
public:
	DatabaseHandler();
	~DatabaseHandler();
	//char* dataParser(double[][]); //return pointer to an char array
	char* dataParser(TaskData* data);
	void storeData(char[]);
	struct data* dataMiningInquiry(int NumberOfParameters);

private:
	//Database db;
};



#endif /* DATABASEHANDLER_H_ */
