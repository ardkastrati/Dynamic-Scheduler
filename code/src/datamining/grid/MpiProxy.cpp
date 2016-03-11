/**
 * Implementes data storage of all data used in the grid data mining procedures.
 */

#include "MpiProxy.h"
#include <cmath>
#include <assert.h>
#include <stddef.h>
/**
 * MpiProxy implementation
 */

MpiProxy::MpiProxy(int nr_of_dimensions, int rank, int traget_rank)
{
	#if MPI_PROXY_DEBUG
	  GridLibrary::print_name("MpiProxy Konstruktor");
		GridLibrary::print_int("nr_of_dimensions", nr_of_dimensions);
		GridLibrary::print_int("rank", rank);
		GridLibrary::print_int("traget_rank", traget_rank);
	#endif
	assert (nr_of_dimensions > 0);
	//assert (target_rank >= 0);
	//assert (rank >= 0);
	this -> nr_of_dimensions = nr_of_dimensions;
	this -> rank = rank;
	this -> target_rank = target_rank;
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

MpiProxy::~MpiProxy()
{
	#if MPI_PROXY_DEBUG
	  GridLibrary::print_name("MpiProxy Destructor");
	#endif
	delete dimensions;
	delete time;
	delete offset;
	delete increment;
	delete correction_vector;
}

int* MpiProxy::get_dimensions()
{
	#if MPI_PROXY_DEBUG
	  GridLibrary::print_name("MpiProxy get_dimensions");
	#endif
	int* to_return = new int[nr_of_dimensions];
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		to_return[i] = dimensions[i];
	}
	return to_return;
}

double* MpiProxy::get_offset()
{
	#if MPI_PROXY_DEBUG
	  GridLibrary::print_name("MpiProxy get_offset");
	#endif
	double* to_return = new double[nr_of_dimensions];
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		to_return[i] = offset[i];
	}
	return to_return;
}

double* MpiProxy::get_increment()
{
	#if MPI_PROXY_DEBUG
	  GridLibrary::print_name("MpiProxy get_increment");
	#endif
	double* to_return = new double[nr_of_dimensions];
        for(int i = 0; i < nr_of_dimensions; i++)
        {
                to_return[i] = increment[i];
        }
        return to_return;
}

long MpiProxy::get_time(int index)
{
	#if MPI_PROXY_DEBUG
	  GridLibrary::print_name("MpiProxy get_time");
	#endif
	assert (index >= 0);
	long to_return = time[index];
	return to_return;
}

double MpiProxy::get_correction_vector(int index)
{
	#if MPI_PROXY_DEBUG
	  GridLibrary::print_name("MpiProxy get_correction_vector");
		GridLibrary::print_int("index",index);
	#endif
	assert (index >= 0);
	double to_return = correction_vector[index];
	return to_return;
}

void MpiProxy::set_new_array(int* new_dimensions, double* new_offset, double* new_increment)
{
	#if MPI_PROXY_DEBUG
	  GridLibrary::print_name("MpiProxy set_new_array");
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

void MpiProxy::push_new_array()
{
	//return;
}

void MpiProxy::set_correction_vector(int index, double new_value)
{
	#if MPI_PROXY_DEBUG
		GridLibrary::print_name("MpiProxy set_correction_vector");
		GridLibrary::print_int("index", index);
		GridLibrary::print_double("new_value", new_value);
	#endif
	assert (index >= 0);
	correction_vector[index] = new_value;
}

void MpiProxy::set_time(int index, long new_time)
{
	#if MPI_PROXY_DEBUG
		GridLibrary::print_name("MpiProxy set_time");
		GridLibrary::print_int("index", index);
		GridLibrary::print_long("new_time", new_time);
	#endif
	assert (index >= 0);
	assert (new_time >= 0);
	time[index] = new_time;
}
