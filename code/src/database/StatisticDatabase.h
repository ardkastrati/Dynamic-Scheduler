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
	/**
	 * The constructor of statistic class.
	 * Start process to create a new file.
	 */
	StatisticDatabase();

	/**
	 * The Destructor of statistic class.
	 */
	~StatisticDatabase();

	/**
	 * The insertTaskData writes the datastring in the file.
	 * @param data string containing one data package of a task
	 */
	void insertTaskData(string data);

	/**
	 * The function reads a existing statistic file in and stores data in memory
	 * for the datamining.
	 * Afterwards the file can be extended with new entries.
	 * The file need to be named Statistic.txt and be placed in the working
	 * directory.
	 * @param data_section a defined struct which contains the data
	 */
	void readTaskData(dataInquiry* data_section);

private:

	/**
	 * Actually creates a new file.
	 */
	void initNewFile();
};



#endif /* STATISTICDATABASE_H_ */
