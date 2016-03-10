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
	/**
	 * Constructor of the DatabaseHandler. Initializes an object for each database partition.
	 * Currently two objects for: bookkeeping & statistics.
	 */
	DatabaseHandler();

	/**
	 * The destructor destroys his database objects and cleans up the local task storage in the main memory.
	 */
	~DatabaseHandler();

	/**
	 * The dataParserBookkeeping parses all information relevant for the bookkeeping
	 * of a task in a string which can be inserted in the bookkeeping file.
	 * @param data TaskData is a data struct with information about a task
	 */
	string dataParserBookkeeping(TaskData* data);

	/**
	 * The dataParserStatistic parses all information relevant for the statistic
	 * of a task in a string which can be inserted in the statistic file.
	 * @param data TaskData is a data struct with information about a task
	 */
	string dataParserStatistic(TaskData* data);

	/**
	 * The storeData function stores the data for one task in all database files.
	 * @param data TaskData is a data struct with content of a task
	 */
	void storeData(TaskData* data);

	/**
	 * The dataMiningInquiry function provides the dataMiner with statistic information
	 * from the main memory.
	 * @param NumberOfParameters number of parameter dimension
	 * @return struct data* returns pointer to data
	 */
	dataInquiry* dataMiningInquiry();

	/**
	 * Stores the information about the task in the main memory for DataMiner inquiry.
	 * Data is hold in a structure of vectors.
	 * @param data TaskData is a data struct with information about a task
	 * @param runtime runtime of the task
	 */
	void storeLocalStatistic(TaskData* data, long runtime);

	/**
	 * Read the whole statistic file again or read a new statistic file and
	 * store the data in memory.
	 * @return struct data* returns pointer to data
	 */
	dataInquiry* readStatistic();

	/**
	 * Dataobject for the DataMiner.
	 */
	dataInquiry* stInq;

private:

	/**
	 * The bookkeeping partition of the database.
	 */
	Database* data_bookkeeping;

	/**
	 * The statistic partition of the database.
	 */
	Database* data_statistic;

	/**
	 * Number of dimensions.
	 */
	int size;

};

#endif /* DATABASEHANDLER_H_ */
