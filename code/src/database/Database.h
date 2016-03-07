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
	 * The insertTaskData writes the datastring in the file.
	 * The function need to be inherited.
	 * @param data string which contains one data package of a task
	 */
	virtual void insertTaskData(string data) = 0;

private:
};



#endif /* DATABASE_H_ */
