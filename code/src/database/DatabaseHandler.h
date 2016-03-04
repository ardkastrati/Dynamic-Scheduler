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
	/*
	 * The constructor of the DatabaseHandler initialize an object for each database partition.
	 * In that case two objects for: bookkeeping, statistic.
	 */
	DatabaseHandler();

	/*
	 * The dataParserBookkeeping is parsing all information that are relevant for the bookkeeping
	 * of a task in a string which can be inserted for the bookkeeping.
	 * @param data TaskData is a data struct with content of a task
	 */
	string dataParserBookkeeping(TaskData* data);

	/*
	 * The dataParserBookkeeping is parsing all information that are relevant for the statistic
	 * of a task in a string which can be inserted for the statistic.
	 * @param data TaskData is a data struct with content of a task
	 */
	string dataParserStatistic(TaskData* data);

	/*
	 * The storeData function stores the data for one task in all files.
	 * @param data TaskData is a data struct with content of a task
	 */
	void storeData(TaskData* data);

	/*
	 * The dataMiningInquiry function is giving the dataMiner the statistic information
	 * from the memory.
	 * @param NumberOfParameters number of parameter dimension
	 * @return struct data* returns pointer to data
	 */
	StatisticInquiry* dataMiningInquiry();

	/*
	 * Hold the information of the task in memory for DataMiner inquiry.
	 * Data is hold in a structure of vectors.
	 * @param data TaskData is a data struct with content of a task
	 * @param runtime runtime of a task
	 */
	void storeLocalStatistic(TaskData* data, long runtime);

	/*
	 * Read the whole statistic file new.
	 */
	void readTaskData();

	/*
	 * Dataobject for the DataMiner.
	 */
	StatisticInquiry* stInq;

private:

	/*
	 * The bookkeeping partition of the database.
	 */
	Database* data_bookkeeping;

	/*
	 * The statistic partition of the database.
	 */
	Database* data_statistic;

	/*
	 * Number of Dimension.
	 */
	int size;

};



#endif /* DATABASEHANDLER_H_ */
