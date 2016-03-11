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
	initNewFile();
}

BookkeepingDatabase::~BookkeepingDatabase()
{
	//bkfile.close();
}

void BookkeepingDatabase::initNewFile()
{
	int size;
	//MPI_Comm_size(MPI_COMM_WORLD, &size);
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
	bkfile.open ("Bookkeeping.txt", std::fstream::out | std::fstream::ate);
	bkfile << "Bookkeeping: File created on: ";
	bkfile << std::ctime(&now_c) << std::endl;
	bkfile << "####DATA_SECTION####" << std::endl;
	//bkfile << "Processor_number: " << size << std::endl;
	bkfile << "####DATA_START####" << std::endl;
	bkfile.close();
}

void BookkeepingDatabase::readTaskData(dataInquiry* data_section)
{

}

void BookkeepingDatabase::insertTaskData(string data)
{
	/*data[] is structed in ID;Timestamp_APP/START/END;Event;Mode;Parent;Timestamp intercommunication start;
	* Timestamp intercommmunication end;Rank;Parameter_size
	*/

	bkfile.open("Bookkeeping.txt",std::fstream::out| std::fstream::app  | std::fstream::ate);

	bkfile << data << std::endl;
	bkfile.close();
}
