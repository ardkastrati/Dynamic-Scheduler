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
	 * Start to create a new file.
	 */
	StatisticDatabase();

	/*
	 * The deconstructor of statistic class.
	 */
	~StatisticDatabase();

	/*
	 * The insertTaskData writes the datastring in the file.
	 * @param data string which contains one data package of a task
	 */
	void insertTaskData(string data);

	/*
	 * Starts to create new file.
	 */
	void createFile();
private:

	/*
	 * Creates the actual new file.
	 */
	void initNewFile();
};



#endif /* STATISTICDATABASE_H_ */
