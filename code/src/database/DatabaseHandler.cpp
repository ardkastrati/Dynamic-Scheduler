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

using namespace std;


DatabaseHandler::DatabaseHandler()
{
	data_bookkeeping = new BookkeepingDatabase();
	data_statistic = new StatisticDatabase();
}

/*
 *
 */
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

//pass by value or reference? server has struct
/*
 *
 */
string DatabaseHandler::dataParserBookkeeping(TaskData *data)
{

	//timestamp abfrage
	string package;
	string part_of_task;


	if(data->event == 0)
	{
		part_of_task = to_string(data->time_appeared);
		package.append(part_of_task);
		package.append(";");
		part_of_task.clear();

		//event 0: Appeared
		package.append("Appeared");
		package.append(";");
		part_of_task.clear();
	} else if (data->event == 1)
	{
		part_of_task = to_string(data->time_started);
		package.append(part_of_task);
		package.append(";");
		part_of_task.clear();

		//event 1: Started
		package.append("Started");
		package.append(";");
		part_of_task.clear();
	} else
	{
		part_of_task = to_string(data->time_ended);
		package.append(part_of_task);
		package.append(";");
		part_of_task.clear();

		//event 2: Ended
		package.append("Ended");
		package.append(";");
		part_of_task.clear();
	}

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

	part_of_task = to_string(data->parent);
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

	part_of_task = to_string(data->time_intercommunication_start);
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

	part_of_task = to_string(data->time_intercommunication_end);
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

	part_of_task = to_string(data->rank);
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

	part_of_task = to_string(data->parameter_size);
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

	for(int i = 0; i < data->parameter_size; i++)
	{
		part_of_task = to_string(data->parameters[i]);
		package.append(";");
	}
	package.append("#");
	part_of_task.clear();

	//char* returnpackage =(char*)package.c_str();
	return package;
}

/*
 *
 */
string DatabaseHandler::dataParserStatistic(TaskData *data)
{
	string package;
	string part_of_task;

	int task_runtime = data->time_ended - data->time_started;

	part_of_task = to_string(task_runtime);
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

	for(int i = 0; i < data->parameter_size; i++)
	{
		part_of_task = to_string(data->parameters[i]);
		package.append(";");
	}
	part_of_task.clear();

	package.append("#");

	//char* returnpackage =(char*)package.c_str();
	return package;
}

