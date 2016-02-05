/*
 * BookkeepingDatabase.cpp
 *
 *  Created on: 21.01.2016
 *      Author: david
 */

#include "Database.h"
#include "BookkeepingDatabase.h"
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <iomanip>
//#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>



std::fstream myfile;


//database initialisieren bzw laden
BookkeepingDatabase::BookkeepingDatabase()
{
	createFile();
}

void BookkeepingDatabase::initNewFile()
{

	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
	myfile.open ("datafiles/Bookkeeping.txt", std::fstream::out | std::fstream::ate);
	myfile << "Bookkeeping: File created on: ";
	myfile << std::ctime(&now_c) << std::endl;
	myfile.close();
}

void BookkeepingDatabase::createFile()
{
	initNewFile();
}


void BookkeepingDatabase::insertTaskData(char data[])
{
	/*data[] is structed in ID;Timestamp_APP/START/END;Mode;Parent_Process of appearing task/
	* Hosting process of starting task/Hosting process of ended task;Timestamp intercommunication start;
	* Timestamp intercommmunication end;CPU rank
	*/
/*
	string datapackage;
	string datastring = data;
	int length = datastring.length();
	int j = 0;
	*/
	myfile.open("datafiles/Bookkeeping.txt",std::fstream::out| std::fstream::app  | std::fstream::ate);
/*
	for(int i = 0; i <= length; i++)
	{
		if(data[i] == ";")
		{
			datapackage.append(data,j,i-1);
			j = i + 1;
		}
	}
	*/
	myfile << data;
	myfile << "#" << std::endl;
	myfile.close();
}

