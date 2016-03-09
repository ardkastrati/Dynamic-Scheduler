/*
 * StatisticDatabase.h
 *
 *  Created on: 21.01.2016
 *      Author: david
 */

#ifndef STATISTICDATABASE_H_
#define STATISTICDATABASE_H_
#include "Database.h"
#include <string>

using namespace std;

class StatisticDatabase : public Database
{
public:
	/*
	 * The constructor of statistic class.
	 * Start process to create a new file.
	 */
	StatisticDatabase();

	/*
	 * The Destructor of statistic class.
	 */
	~StatisticDatabase();

	/*
	 * The insertTaskData writes the datastring in the file.
	 * @param data string containing one data package of a task
	 */
	void insertTaskData(string data);

	/**
	 *
	 */
	void readTaskData();

private:

	/*
	 * Actually creates a new file.
	 */
	void initNewFile();
};



#endif /* STATISTICDATABASE_H_ */
