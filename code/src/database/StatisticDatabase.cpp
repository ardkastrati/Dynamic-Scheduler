/*
 * StatisticDatabase.cpp
 *
 *  Created on: 21.01.2016
 *      Author: david
 */

#include "Database.h"
#include "StatisticDatabase.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

using namespace std;

std::fstream stfile;

/*
 *
 */
StatisticDatabase::StatisticDatabase()
{
	createFile();
}

/*
 *
 */
void StatisticDatabase::initNewFile()
{

	fstream stfile;
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
	mkdir("databases");
	stfile.open ("Statistic.txt", std::fstream::out | std::fstream::ate);
	stfile << "Statistic: File created on: ";
	stfile << std::ctime(&now_c) << std::endl;
	stfile.close();
}

/*
 *
 */
void StatisticDatabase::createFile()
{
	initNewFile();
}

/*
 *
 */
void StatisticDatabase::insertTaskData(string data)
{
	/*data[] is structed in ID;Timestamp_APP/START/END;Mode;Parent_Process of appearing task/
	* Hosting process of starting task/Hosting process of ended task;Timestamp intercommunication start;
	* Timestamp intercommmunication end;CPU rank
	*/

	stfile.open("datafiles/Statistic.txt",std::fstream::out| std::fstream::app  | std::fstream::ate);

	stfile << data;
	stfile << "#" << std::endl;
	stfile.close();
}
