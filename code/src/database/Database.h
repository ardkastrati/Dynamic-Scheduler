/*
 * Database.h
 *
 *  Created on: 21.01.2016
 *      Author: david
 */

#ifndef DATABASE_H_
#define DATABASE_H_
#include "../TypesExtern.h"
#include <string.h>


class Database
{
public:
	//darf nur einmal initialisiert werden
	Database();
	//virtual ~Database() =0;
	virtual void insertTaskData(char data[]) = 0;
	//virtual void getDataPackage() = 0; //nur statistic, gibt noch zurück, virtual?
	void deleteLastEntry();
	void exportDatabase();
	virtual void createFile() = 0;
	//virtual void deleteFile() = 0;


private:
};



#endif /* DATABASE_H_ */
