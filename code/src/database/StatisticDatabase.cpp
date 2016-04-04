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

void StatisticDatabase::readTaskData(dataInquiry* data_section)
{
	//file open?
	if(stfile.is_open())
	{
		stfile.close();
	}

	string line;
	stfile.open("Statistic.txt",std::fstream::in);
	bool data_start = false;
	string operator_string;

	//pass data_section
	while(!data_start)
	{
		getline(stfile, line);
		if(line == "####DATA_START####")
		{
			data_start = true;
		}
	}
	//read before eof()
	getline(stfile, line);
	while(!stfile.eof())
	{
		int j = 0;
		int parameter_counter = 0;
		long runtime;
		double parameter;
		for(int i = 0; i < line.length(); i++)
		{
			//save runtime
			if(line[i] == ';')
			{
				runtime = std::stol(operator_string);
				//character after ";"
				j = i + 1;
				break;
			}
			operator_string.push_back(line[i]);
		}
		data_section->runtime.push_back(runtime);
		operator_string.clear();
		//now the parameters
		for(; j < line.length(); j++)
		{
			//check again
			if(line[j] == '#')
			{
				break;
			}
			//save parameter
			if(line[j] == ';')
			{
				parameter_counter++;
				//what if 0 parameter?
				parameter = std::stod(operator_string);
				//end of line?
				if(line[j + 1] == '#')
				{
					break;
				}
				operator_string.clear();
				//character after ";"
				j = j + 1;
			}
			operator_string.push_back(line[j]);
		}
		data_section->para.push_back(parameter);
		data_section->parameter_size = parameter_counter;
		operator_string.clear();
		line.clear();
		getline(stfile, line);
	}
	stfile.close();
	//for continue write
	//stfile.open("Statistic.txt",std::fstream::out| std::fstream::app  | std::fstream::ate);
}

void StatisticDatabase::insertTaskData(string data)
{
	/*data[] is structed in runtime;parameter[0]; ... ;parameter[parameter_size]
	*/

	stfile.open("Statistic.txt",std::fstream::out| std::fstream::app  | std::fstream::ate);

	stfile << data << std::endl;
	stfile.close();
}
