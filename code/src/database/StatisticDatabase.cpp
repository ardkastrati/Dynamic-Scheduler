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

using namespace std;

std::fstream stfile;

StatisticDatabase::StatisticDatabase()
{
	initNewFile();
}

StatisticDatabase::~StatisticDatabase()
{
	//stfile.close();
}

void StatisticDatabase::initNewFile()
{

	fstream stfile;
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
	stfile.open ("Statistic.txt", std::fstream::out | std::fstream::ate);
	stfile << "Statistic: File created on: ";
	stfile << std::ctime(&now_c) << std::endl;
	stfile << "####DATA_SECTION####" << std::endl;
	stfile << "####DATA_START####" << std::endl;
	stfile.close();
}

void StatisticDatabase::readTaskData()
{
	string line;
	stfile.open("Statistic.txt",std::fstream::in);
	std::getline(stfile, line);
	std::getline(stfile, line);
	std::getline(stfile, line);
	std::getline(stfile, line);
	stfile.close();
	//cout << line << "\n";
}

void StatisticDatabase::insertTaskData(string data)
{
	/*data[] is structed in ID;Timestamp_APP/START/END;Mode;Parent_Process of appearing task/
	* Hosting process of starting task/Hosting process of ended task;Timestamp intercommunication start;
	* Timestamp intercommmunication end;CPU rank
	*/

	stfile.open("Statistic.txt",std::fstream::out| std::fstream::app  | std::fstream::ate);

	stfile << data << std::endl;
	stfile.close();
}
