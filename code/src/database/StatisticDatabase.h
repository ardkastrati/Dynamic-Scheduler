/*
 * StatisticDatabase.h
 *
 *  Created on: 21.01.2016
 *      Author: david
 */

#ifndef STATISTICDATABASE_H_
#define STATISTICDATABASE_H_
#include "Database.h"
#include <cstring>

using namespace std;
class StatisticDatabase : Database
{
public:
	StatisticDatabase();
	//~BookkeepingDatabase();
	void insertTaskData(char data[]);
	void createFile();
private:
	void initNewFile();
};



#endif /* STATISTICDATABASE_H_ */
