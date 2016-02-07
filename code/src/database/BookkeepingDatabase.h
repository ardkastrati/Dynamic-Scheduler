/*
 * BookkeepingDatabase.h
 *
 *  Created on: 21.01.2016
 *      Author: david
 */

#ifndef BOOKKEEPINGDATABASE_H_
#define BOOKKEEPINGDATABASE_H_
#include "Database.h"
#include <string>

using namespace std;
class BookkeepingDatabase : public Database
{
public:
	BookkeepingDatabase();
	//~BookkeepingDatabase();
	void insertTaskData(string data);
	void createFile();
private:
	void initNewFile();
};



#endif /* BOOKKEEPINGDATABASE_H_ */
