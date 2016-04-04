/*
 * DatabaseHandler.cpp
 *
 *  Created on: 21.01.2016
 *      Author: david
 */
#include "DatabaseHandler.h"
#include "Database.h"
#include "BookkeepingDatabase.h"
#include "StatisticDatabase.h"
#include <stdio.h>
#include <string>
#include <iomanip>
#include <iostream>
#include <mpi.h>

using namespace std;

DatabaseHandler::DatabaseHandler()
{
	data_bookkeeping = new BookkeepingDatabase();
	data_statistic = new StatisticDatabase();
	stInq = new dataInquiry;
	size = 0;
}

DatabaseHandler::~DatabaseHandler()
{
  stInq->para.clear();
	stInq->runtime.clear();
	delete stInq;
	delete data_bookkeeping;
	delete data_statistic;
}

void DatabaseHandler::storeLocalStatistic(TaskData* data, long runtime)
{
	stInq->parameter_size = data->parameter_size;
	stInq->runtime.push_back(runtime);

	//insert data in memory
	stInq->para.insert(stInq->para.end(), &data->parameters[0], &data->parameters[data->parameter_size]);

}

dataInquiry* DatabaseHandler::dataMiningInquiry()
{
	return stInq;
}

void DatabaseHandler::storeData(TaskData *data)
{
	string bookkeeping_package = dataParserBookkeeping(data);
	if(data->event == 2)
	{
		string statistic_package = dataParserStatistic(data);
		data_statistic->insertTaskData(statistic_package);
	}
	data_bookkeeping->insertTaskData(bookkeeping_package);

}

string DatabaseHandler::dataParserBookkeeping(TaskData *data)
{
	string package;
	string part_of_task;

	//ID of task
	part_of_task = to_string(static_cast<long long>(data->id));
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

	//1. timestamp; 2. event
	if(data->event == 0)
	{
		part_of_task = to_string(static_cast<long long>(data->time_appeared));
		package.append(part_of_task);
		package.append(";");
		part_of_task.clear();

		//event 0: Appeared
		package.append("Appeared");
		package.append(";");
		part_of_task.clear();
	} else if (data->event == 1)
	{
		part_of_task = to_string(static_cast<long long>(data->time_started));
		package.append(part_of_task);
		package.append(";");
		part_of_task.clear();

		//event 1: Started
		package.append("Started");
		package.append(";");
		part_of_task.clear();
	} else
	{
		part_of_task = to_string(static_cast<long long>(data->time_ended));
		package.append(part_of_task);
		package.append(";");
		part_of_task.clear();

		//event 2: Ended
		package.append("Ended");
		package.append(";");
		part_of_task.clear();
	}

	//scheduling mode
	if(data->mode == 0)
	{
		package.append("Master/Worker");
		package.append(";");
		part_of_task.clear();
	} else
	{
		package.append("Task-Stealing");
		package.append(";");
		part_of_task.clear();
	}

	//parent
	part_of_task = to_string(static_cast<long long>(data->parent));
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

	//intercommunication start timestamp
	part_of_task = to_string(static_cast<long long>(data->time_intercommunication_start));
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

	//intercommunication end timestamp
	part_of_task = to_string(static_cast<long long>(data->time_intercommunication_end));
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

	//rank
	part_of_task = to_string(static_cast<long long>(data->rank));
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

	//number of parameters
	part_of_task = to_string(static_cast<long long>(data->parameter_size));
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

	package.append("#");
	part_of_task.clear();

	return package;
}

string DatabaseHandler::dataParserStatistic(TaskData *data)
{
	string package;
	string part_of_task;

	//calculate runtime out of start and end timestamp
	long task_runtime = data->time_ended - data->time_started;

	part_of_task = to_string(static_cast<long long>(task_runtime));
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

	//get parameters of a task
	for(int i = 0; i < data->parameter_size; i++)
	{
		part_of_task = to_string(static_cast<long double>(data->parameters[i]));
		package.append(part_of_task);
		package.append(";");
	}
	part_of_task.clear();

	package.append("#");

	//store in local
	storeLocalStatistic(data, task_runtime);

	return package;
}

dataInquiry* DatabaseHandler::readStatistic()
{
	//make sure to clear old structure
	dataInquiry* file_section = new dataInquiry;
	data_statistic->readTaskData(file_section);
	return file_section;
}
