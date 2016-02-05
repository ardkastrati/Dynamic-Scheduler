/*
 * DatabaseHandler.cpp
 *
 *  Created on: 21.01.2016
 *      Author: david
 */

#include "DatabaseHandler.h"
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <iomanip>
//#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//pass by value or reference? server has struct
char* DatabaseHandler::dataParser(TaskData *data)
{

	//timestamp abfrage
	string package;
	string part_of_task;

	part_of_task = to_string(data->time_appeared);
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

	part_of_task = to_string(data->event);
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

	part_of_task = to_string(data->mode);
	package.append(part_of_task);
	package.append(";");
	part_of_task.clear();

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



}



