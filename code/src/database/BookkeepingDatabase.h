/*
 * BookkeepingDatabase.h
 *
 *  Created on: 21.01.2016
 *      Author: david
 */

#ifndef BOOKKEEPINGDATABASE_H_
#define BOOKKEEPINGDATABASE_H_
#include "Database.h"
#include <cstring>

using namespace std;
class BookkeepingDatabase : Database
{
public:
	BookkeepingDatabase();
	//~BookkeepingDatabase();
	void insertTaskData(char data[]);
	void createFile();
private:
	void initNewFile();
};



#endif /* BOOKKEEPINGDATABASE_H_ */
