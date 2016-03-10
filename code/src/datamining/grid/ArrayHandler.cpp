/**
 * Implementation of ArrayHandler.h.
 */

#include "ArrayHandler.h"
#include "GridLibrary.h"
#include <cmath>
#include <cstring>
#include <assert.h>
#include <stddef.h>


/**
 * ArrayHandler implementation
 */

ArrayHandler::ArrayHandler(int nr_of_dimensions, MpiProxy* memory)
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler constructor");
	  GridLibrary::print_int("nr_of_dimensions", nr_of_dimensions);
	#endif
	assert (nr_of_dimensions > 0);
	assert (memory != NULL);
	this -> nr_of_dimensions = nr_of_dimensions;
	this -> memory = memory;
}

ArrayHandler::~ArrayHandler()
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler destructor");
	#endif
	delete memory;
}

long ArrayHandler::get_time(int* index)
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler get_time");
	  GridLibrary::print_array_int("index", index, nr_of_dimensions);
	#endif
	assert (index != NULL);
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		assert (index[i] >= 0);
	}
	int* dimensions = memory -> get_dimensions();

	int one_dimensional_index = GridLibrary::get_index(dimensions, index, nr_of_dimensions);
	delete dimensions;

	long to_return = memory -> get_time(one_dimensional_index);

	return to_return;
}

int* ArrayHandler::get_enviroment_index(double* parameter)
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler get_enviroment_index");
	  GridLibrary::print_array_double("index", parameter, nr_of_dimensions);
	#endif
	assert (parameter != NULL);
	int return_length = nr_of_dimensions * pow(2, nr_of_dimensions);
	int* to_return = new int[return_length];
	int binar_counter[nr_of_dimensions];
	int* rounded_down = get_rounded_down(parameter);

	for(int i = 0; i < nr_of_dimensions; i++)
	{
		binar_counter[i] = 0;
	}

	for(int i = 0; i < return_length; i = i + nr_of_dimensions)//jumps a vector forward
	{
		for(int j = 0; j < nr_of_dimensions; j++)
		{
			to_return[i + j] = rounded_down[j] + binar_counter[j];//the i-th vector on the j-th place
		}
		//increase binar counter
		bool found_zero = false;
		for(int j = 0; j < nr_of_dimensions && not found_zero; j++)
		{
			if(binar_counter[j] == 0) //binar_counter can only be 1 or 0
			{
				binar_counter[j] = 1;
				found_zero = true;
			}
			else
			{
				binar_counter[j] = 0;
			}
		}
	}
	delete rounded_down;
	return to_return;
}

int* ArrayHandler::get_dimensions()
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler get_dimensions");
	#endif
  int* to_return = memory -> get_dimensions();
  return to_return;
}

double ArrayHandler::get_corrected_distanz(int* index, double* parameter)
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler get_corrected_distanz");
		GridLibrary::print_array_int("index", index, nr_of_dimensions);
		GridLibrary::print_array_double("parameter", parameter, nr_of_dimensions);
	#endif
	assert (index != NULL);
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		assert (index[i] >= 0);
	}
	assert (parameter != NULL);
  double* grid_parameter = get_parameter(index);
	double* correction_vector = get_correction_vector(index);
	double* corrected_parameter = GridLibrary::add_array(correction_vector, grid_parameter, nr_of_dimensions);
	double* distance_vector = GridLibrary::subtract_array(parameter, corrected_parameter, nr_of_dimensions);
	double to_return = GridLibrary::get_length_of_vector(distance_vector, nr_of_dimensions);

	delete grid_parameter;
	delete correction_vector;
	delete corrected_parameter;
	delete distance_vector;
	return to_return;
}

void ArrayHandler::set_new_array(int* dimensions, double* increment, double* offset)
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler set_new_array");
		GridLibrary::print_array_int("dimensions", dimensions, nr_of_dimensions);
		GridLibrary::print_array_double("increment", increment, nr_of_dimensions);
		GridLibrary::print_array_double("offset", offset, nr_of_dimensions);
	#endif
  memory -> set_new_array(dimensions, offset, increment);
}

void ArrayHandler::insert_at_point(int* index, double* parameter, long time)
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler insert_at_point");
		GridLibrary::print_array_int("index", index, nr_of_dimensions);
		GridLibrary::print_array_double("parameter", parameter, nr_of_dimensions);
		GridLibrary::print_long("time", time);
	#endif
	assert (index != NULL);
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		assert (index[i] >= 0);
	}
	assert (parameter != NULL);
	assert (time >= 0);
  double* correction_vector = get_correction_vector(index);
	double* uncorrected_parameter = get_parameter(index);
	double* new_correction_vector = GridLibrary::subtract_array(parameter, uncorrected_parameter, nr_of_dimensions);
	double correction_vector_length = GridLibrary::get_length_of_vector(correction_vector, nr_of_dimensions);
	double new_correction_vector_length = GridLibrary::get_length_of_vector(new_correction_vector, nr_of_dimensions);

	if(new_correction_vector_length < correction_vector_length)
	{
		set_correction_vector(index, new_correction_vector);
		set_time(index, time);
	}//else nothing to do here
	delete correction_vector;
	delete uncorrected_parameter;
	delete new_correction_vector;
}

void ArrayHandler::set_time(int* index, long time)
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler set_time");
		GridLibrary::print_array_int("index", index, nr_of_dimensions);
		GridLibrary::print_long("time", time);
	#endif
	assert (time >= 0);
	assert (index != NULL);
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		assert (index[i] >= 0);
	}
  int* max_dimensions = memory -> get_dimensions();

	int one_dimensional_index = GridLibrary::get_index(max_dimensions, index, nr_of_dimensions);
	delete max_dimensions;
	memory -> set_time(one_dimensional_index, time);
}

double* ArrayHandler::get_parameter(int* index)
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler get_parameter");
		GridLibrary::print_array_int("index", index, nr_of_dimensions);
	#endif
	assert (index != NULL);
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		assert (index[i] >= 0);
	}
  double* offset = get_offset();
  double* increment = get_increment();
	long* long_index = new long[nr_of_dimensions];
	//cast int into long
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		long_index[i] = (long) index[i];
	}
  double* factorized_index = GridLibrary::multiply_array(long_index, increment, nr_of_dimensions);
	double* to_return = GridLibrary::add_array(factorized_index, offset, nr_of_dimensions);
	delete long_index;
	delete offset;
	delete increment;
	delete factorized_index;
	return to_return;
}

int* ArrayHandler::get_rounded_down(double* parameter)
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler get_rounded_down");
		GridLibrary::print_array_double("parameter", parameter, nr_of_dimensions);
	#endif
	assert (parameter != NULL);
	double* increment = memory -> get_increment();
	double* offset = memory -> get_offset();
	double* grounded_parameter = GridLibrary::subtract_array(parameter, offset, nr_of_dimensions);
	double* index = GridLibrary::divide_array(grounded_parameter, increment, nr_of_dimensions);
	int* dimension = memory -> get_dimensions();
	int* to_return = new int[nr_of_dimensions];

	for(int i = 0; i < nr_of_dimensions; i++)
	{
		to_return[i] = (index[i] < dimension[i]) ? (int) index[i] : dimension[i] - 2;//catch the out of bound requestst
		to_return[i] = (to_return[i] < 0) ? 0 : to_return[i];
	}

	delete dimension;
	delete increment;
	delete offset;
	delete grounded_parameter;
	delete index;
	return to_return;
}

void ArrayHandler::set_correction_vector(int* index, double* vector)
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler get_rounded_down");
		GridLibrary::print_array_int("index", index, nr_of_dimensions);
		GridLibrary::print_array_double("vector", vector, nr_of_dimensions);
	#endif
	assert (vector != NULL);
	assert (index != NULL);
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		assert (index[i] >= 0);
	}
	int* dimensions = memory -> get_dimensions();

	int extended_dimensions[nr_of_dimensions + 1];
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		extended_dimensions[i] = dimensions[i];
	}
	delete dimensions;
	extended_dimensions[nr_of_dimensions] = nr_of_dimensions;//the target array is one dimensions greater than the time add_array

	int extended_index[nr_of_dimensions + 1];
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		extended_index[i] = index[i];
	}

	for(int i = 0; i < nr_of_dimensions; i++)
	{
		extended_index[nr_of_dimensions] = i; //the last dimensions is the vector
		int one_dimensional_index = GridLibrary::get_index(extended_dimensions, extended_index, nr_of_dimensions + 1); //+1 cause we have one dimension more
		memory -> set_correction_vector(one_dimensional_index, vector[i]);
	}
}

double* ArrayHandler::get_correction_vector(int* index)
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler get_correction_vector");
		GridLibrary::print_array_int("index", index, nr_of_dimensions);
	#endif
	assert (index != NULL);
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		assert (index[i] >= 0);
	}
	int* dimensions = memory -> get_dimensions();

	int extended_dimensions[nr_of_dimensions + 1];
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		extended_dimensions[i] = dimensions[i];
	}
	delete dimensions;
	extended_dimensions[nr_of_dimensions] = nr_of_dimensions;//the target array is one dimensions greater than the time add_array

	int extended_index[nr_of_dimensions + 1];
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		extended_index[i] = index[i];
	}

	double* to_return = new double[nr_of_dimensions];
	for(int i = 0; i < nr_of_dimensions; i++)
	{
		extended_index[nr_of_dimensions] = i; //the last dimensions is the vector
		int one_dimensional_index = GridLibrary::get_index(extended_dimensions, extended_index, nr_of_dimensions + 1); //+1 cause we have one dimension more
		to_return[i] = memory -> get_correction_vector(one_dimensional_index);
	}
	return to_return;
}

double* ArrayHandler::get_offset()
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler get_offset");
	#endif
  double* to_return = memory -> get_offset();
  return to_return;
}

double* ArrayHandler::get_increment()
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler get_increment");
	#endif
  double* to_return = memory -> get_increment();
  return to_return;
}

void ArrayHandler::push_new_array()
{
	#if ARRAY_HANDLER_DEBUG
	  GridLibrary::print_name("ArrayHandler push_new_array");
	#endif
	memory -> push_new_array();
}
