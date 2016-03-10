
/**
 * Implements basic functionalities used in the 'Arrayhandler' and 'GridDatamining' classes.
 */

#include "GridLibrary.h"
#include <cmath>
#include <iostream>
#include <string>
/**
 * GridLibrary implementation
 */

int GridLibrary::get_index(int* dimensions, int* index, int nr_of_dimensions)
{
  #if GRID_Library_DEBUG
    GridLibrary::print_name("GridLibrary get_index");
    GridLibrary::print_array_int("dimensions", dimensions, nr_of_dimensions);
    GridLibrary::print_array_int("index", index, nr_of_dimensions);
    GridLibrary::print_int("nr_of_dimensions", nr_of_dimensions);
  #endif
  int to_return = 0;
  int sub_space = 1;
  for(int i = nr_of_dimensions - 1; i >= 0; i--)
  {
    to_return = to_return + index[i] * sub_space;
    sub_space = sub_space * dimensions[i];
  }
  return to_return;
}

double GridLibrary::get_length_of_vector(double* vector, int nr_of_dimensions)
{
  #if GRID_Library_DEBUG
    GridLibrary::print_name("GridLibrary get_length_of_vector");
    GridLibrary::print_array_double("vector", vector, nr_of_dimensions);
    GridLibrary::print_int("nr_of_dimensions", nr_of_dimensions);
  #endif
  double sum = 0;
  for(int i = 0; i < nr_of_dimensions; i++)
  {
    sum = sum + pow(vector[i], 2);
  }
  return sqrt(sum);
}

double* GridLibrary::subtract_array(double* first_array, double* second_array, int length)
{
  #if GRID_Library_DEBUG
    GridLibrary::print_name("GridLibrary subtract_array");
    GridLibrary::print_array_double("first_array", first_array, length);
    GridLibrary::print_array_double("second_array", second_array, length);
    GridLibrary::print_int("length", length);
  #endif
  double* to_return = new double[length];
  for(int i = 0; i < length; i++)
  {
    to_return[i] = first_array[i] - second_array[i];
  }
  return to_return;
}

double* GridLibrary::divide_array(double* array, double* factor, int length)
{
  #if GRID_Library_DEBUG
    GridLibrary::print_name("GridLibrary divide_array");
    GridLibrary::print_array_double("array", array, length);
    GridLibrary::print_array_double("factor", factor, length);
    GridLibrary::print_int("length", length);
  #endif
  double* to_return = new double[length];
  for(int i = 0; i < length; i++)
  {
    to_return[i] = array[i] / factor[i];
  }
  return to_return;
}

double* GridLibrary::add_array(double* first_array, double* second_array, int length)
{
  #if GRID_Library_DEBUG
    GridLibrary::print_name("GridLibrary add_array");
    GridLibrary::print_array_double("first_array", first_array, length);
    GridLibrary::print_array_double("second_array", second_array, length);
    GridLibrary::print_int("length", length);
  #endif
  double* to_return = new double[length];
  for(int i = 0; i < length; i++)
  {
    to_return[i] = first_array[i] + second_array[i];
  }
  return to_return;
}

double* GridLibrary::multiply_array(long* array, double* factor, int length)
{
  #if GRID_Library_DEBUG
    GridLibrary::print_name("GridLibrary multiply_array");
    GridLibrary::print_array_long("array", array, length);
    GridLibrary::print_array_double("factor", factor, length);
    GridLibrary::print_int("length", length);
  #endif
  double* to_return = new double[length];
  for(int i = 0; i < length; i++)
  {
    to_return[i] = array[i] * factor[i];
  }
  return to_return;
}

double* GridLibrary::kastrati_value(double* length, int length_length)
{
  #if GRID_Library_DEBUG
    GridLibrary::print_name("GridLibrary kastrati_value");
    GridLibrary::print_array_double("length", length, length_length);
    GridLibrary::print_int("length_length", length_length);
  #endif
  double* to_return = new double[length_length];
  double length_sum = 0;
  for(int i = 0; i < length_length; i++)
  {
		if(length[i] == 0)
		{
			for(int j = 0; j < length_length; j++)
			{
				to_return[j] = 0;
			}
			to_return[i] = 1;
			return to_return;
		}
		length_sum = length_sum + length[i];
	}

	double relativ_length[length_length];
	for(int i = 0; i < length_length; i++)
	{
		relativ_length[i] = length[i] / length_sum;
	}

	for(int i = 0; i < length_length; i++)
	{
		double denominator = 0;
		for(int j = 0; j < length_length; j++)
		{
			denominator = denominator + (relativ_length[i] / relativ_length[j]);
		}
		to_return[i] = 1 / denominator;
	}
	//delete length;
	return to_return;
}

#if PRINTGRID || ARRAY_HANDLER_DEBUG || GRID_DATA_MINING_DEBUG || GRID_LIBRARY_DEBUG || MPI_PROXY_DEBUG

void GridLibrary::print_name(std::string name)
{
  std::cout << name << "\n";
}

void GridLibrary::print_array_int(std::string name, int* array, int length)
{
  std::cout << name << " {";
  for(int i = 0; i < length - 1; i++)
  {
    std::cout << array[i] << ", ";
  }
  std::cout << array[length - 1] << "}" << "\n";
}

void GridLibrary::print_array_long(std::string name, long* array, int length)
{
  std::cout << name << " {";
  for(int i = 0; i < length - 1; i++)
  {
    std::cout << array[i] << ", ";
  }
  std::cout << array[length - 1] << "}" << "\n";
}

void GridLibrary::print_array_double(std::string name, double* array, int length)
{
  std::cout << name << " {";
  for(int i = 0; i < length - 1; i++)
  {
    std::cout << array[i] << ", ";
  }
  std::cout << array[length - 1] << "}" << "\n";
}

void GridLibrary::print_int(std::string name, int to_print)
{
  std::cout << name << " has value: " << to_print << "\n";
}

void GridLibrary::print_long(std::string name, long to_print)
{
  std::cout << name << " has value: " << to_print << "\n";
}

void GridLibrary::print_double(std::string name, double to_print)
{
  std::cout << name << " has value: " << to_print << "\n";
}

#endif
