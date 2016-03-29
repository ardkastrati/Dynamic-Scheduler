/*
 * Database.h
 *
 *  Created on: 21.01.2016
 *      Author: david
 */

#ifndef DATABASE_H_
#define DATABASE_H_
#include "../TypesExtern.h"
#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

class Database
{
public:

	/**
	 * insertTaskData writes a datastring in the file.
	 * The function must be inherited.
	 * @param data string containing one data package of a task
	 */
	virtual void insertTaskData(string data) = 0;

	/**
	 * The function reads a existing file in and stores data in memory
	 * for the datamining.
	 * Afterwards the file can be extended with new entries.
	 * The file need to be placed in the working
	 * directory.
	 * @param data_section a defined struct which contains the data
	 */
	virtual void readTaskData(dataInquiry* data_section) = 0;

private:
};

#endif /* DATABASE_H_ */
