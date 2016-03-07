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
	/**
	 * The constructor of bookkeeping class.
	 * Start to create a new file.
	 */
	BookkeepingDatabase();

	/**
	 * The deconstructor of bookkeeping class.
	 */
	~BookkeepingDatabase();

	/**
	 * The insertTaskData writes the datastring in the file.
	 * @param data string which contains one data package of a task
	 */
	void insertTaskData(string data);

	/**
	 * Starts to create new file.
	 */
	void createFile();
private:
	/**
	 * Creates the actual new file.
	 */
	void initNewFile();
	int size;
};



#endif /* BOOKKEEPINGDATABASE_H_ */
