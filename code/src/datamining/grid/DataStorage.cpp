/**
 * Implementes data storage of all data used in the grid data mining procedures.
 */

#include "DataStorage.h"
#include <cmath>
#include <assert.h>
#include <stddef.h>
/**
 * DataStorage implementation
 */

DataStorage::DataStorage(int nr_of_dimensions)
{
	#if DATASTORAGE_DEBUG
	  GridLibrary::print_name("DataStorage Konstruktor");
		GridLibrary::print_int("nr_of_dimensions", nr_of_dimensions);
	#endif
	assert (nr_of_dimensions > 0);
	this -> nr_of_dimensions = nr_of_dimensions;
	dimensions = new int[nr_of_dimensions];
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		dimensions[i] = 0;
	}

	time = new long[1];
	time[0] = 0;

	offset = new double[nr_of_dimensions];
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		offset[i] = 0;
	}

	increment = new double[nr_of_dimensions];
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		increment[i] = 1;
	}

	correction_vector = new double[nr_of_dimensions];
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		correction_vector[i] = INFINITY;
	}
}

DataStorage::~DataStorage()
{
	#if DATASTORAGE_DEBUG
	  GridLibrary::print_name("DataStorage Destructor");
	#endif
	delete dimensions;
	delete time;
	delete offset;
	delete increment;
	delete correction_vector;
}

int* DataStorage::get_dimensions()
{
	#if DATASTORAGE_DEBUG
	  GridLibrary::print_name("DataStorage get_dimensions");
	#endif
	int* to_return = new int[nr_of_dimensions];
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		to_return[i] = dimensions[i];
	}
	return to_return;
}

double* DataStorage::get_offset()
{
	#if DATASTORAGE_DEBUG
	  GridLibrary::print_name("DataStorage get_offset");
	#endif
	double* to_return = new double[nr_of_dimensions];
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		to_return[i] = offset[i];
	}
	return to_return;
}

double* DataStorage::get_increment()
{
	#if DATASTORAGE_DEBUG
	  GridLibrary::print_name("DataStorage get_increment");
	#endif
	double* to_return = new double[nr_of_dimensions];
        for(int i = 0; i < nr_of_dimensions; i++)
        {
                to_return[i] = increment[i];
        }
        return to_return;
}

long DataStorage::get_time(int index)
{
	#if DATASTORAGE_DEBUG
	  GridLibrary::print_name("DataStorage get_time");
	#endif
	assert (index >= 0);
	long to_return = time[index];
	return to_return;
}

double DataStorage::get_correction_vector(int index)
{
	#if DATASTORAGE_DEBUG
	  GridLibrary::print_name("DataStorage get_correction_vector");
		GridLibrary::print_int("index",index);
	#endif
	assert (index >= 0);
	double to_return = correction_vector[index];
	return to_return;
}

void DataStorage::set_new_array(int* new_dimensions, double* new_offset, double* new_increment)
{
	#if DATASTORAGE_DEBUG
	  GridLibrary::print_name("DataStorage set_new_array");
		GridLibrary::print_array_int("new_dimensions", new_dimensions, nr_of_dimensions);
		GridLibrary::print_array_double("new_offset", new_offset, nr_of_dimensions);
		GridLibrary::print_array_double("new_increment", new_increment, nr_of_dimensions);
	#endif
	assert (new_dimensions != NULL);
	assert (new_offset != NULL);
	assert (new_increment != NULL);
	delete dimensions;
	dimensions = new int[nr_of_dimensions];

	int new_time_array_size = 1;

	for(int i = 0; i < nr_of_dimensions; i++)
	{
		dimensions[i] = new_dimensions[i];
		new_time_array_size = new_time_array_size * dimensions[i];
	}

	delete time;
	time = new long[new_time_array_size];
	for(int i = 0; i < new_time_array_size; i++)
	{
		time[i] = 0;
	}

	delete offset;
	offset = new double[nr_of_dimensions];

	for(int i = 0; i < nr_of_dimensions; i++)
	{
		offset[i] = new_offset[i];
	}

	delete increment;
	increment = new double[nr_of_dimensions];

	for(int i = 0; i < nr_of_dimensions; i++)
	{
		increment[i] = new_increment[i];
	}

	delete correction_vector;
	correction_vector = new double[new_time_array_size * nr_of_dimensions];
	for(int i = 0; i < new_time_array_size * nr_of_dimensions; i++)
	{
		correction_vector[i] = INFINITY;
	}
}

void DataStorage::set_correction_vector(int index, double new_value)
{
	#if DATASTORAGE_DEBUG
		GridLibrary::print_name("DataStorage set_correction_vector");
		GridLibrary::print_int("index", index);
		GridLibrary::print_double("new_value", new_value);
	#endif
	assert (index >= 0);
	correction_vector[index] = new_value;
}

void DataStorage::set_time(int index, long new_time)
{
	#if DATASTORAGE_DEBUG
		GridLibrary::print_name("DataStorage set_time");
		GridLibrary::print_int("index", index);
		GridLibrary::print_long("new_time", new_time);
	#endif
	assert (index >= 0);
	assert (new_time >= 0);
	time[index] = new_time;
}
