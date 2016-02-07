/*
 * BookkeepingDatabase.cpp
 *
 *  Created on: 21.01.2016
 *      Author: david
 */

#include "Database.h"
#include "BookkeepingDatabase.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

std::fstream bkfile;

//database initialisieren bzw laden
BookkeepingDatabase::BookkeepingDatabase()
{
	createFile();
}

void BookkeepingDatabase::initNewFile()
{

	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
	bkfile.open ("Bookkeeping.txt", std::fstream::out | std::fstream::ate);
	bkfile << "Bookkeeping: File created on: ";
	bkfile << std::ctime(&now_c) << std::endl;
	bkfile.close();
}

void BookkeepingDatabase::createFile()
{
	initNewFile();
}


void BookkeepingDatabase::insertTaskData(string data)
{
	/*data[] is structed in ID;Timestamp_APP/START/END;Mode;Parent_Process of appearing task/
	* Hosting process of starting task/Hosting process of ended task;Timestamp intercommunication start;
	* Timestamp intercommmunication end;CPU rank
	*/

	bkfile.open("datafiles/Bookkeeping.txt",std::fstream::out| std::fstream::app  | std::fstream::ate);

	bkfile << data;
	bkfile << "#" << std::endl;
	bkfile.close();
}

