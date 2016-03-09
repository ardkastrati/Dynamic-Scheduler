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
	/*
	 * Constructor of the bookkeeping class.
	 * Start process to create a new file.
	 */
	BookkeepingDatabase();

	/*
	 * Destructor of the bookkeeping class.
	 */
	~BookkeepingDatabase();

	/*
	 * The insertTaskData writes the datastring in the file.
	 * @param data string containing one data package of a task
	 */
	void insertTaskData(string data);

	void readTaskData();

private:
	/*
	 * Actually creates a new file.
	 */
	void initNewFile();
	int size;
};



#endif /* BOOKKEEPINGDATABASE_H_ */
