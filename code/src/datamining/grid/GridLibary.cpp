/**
 * Project Dynamic Scheduler for Scientific Simulations
 */

#include "GridLibary.h"
#include <cmath>
#include <iostream>
#include <string>
/**
 * GridLibary implementation
 */

int GridLibary::get_index(int* dimensions, int* index, int nr_of_dimensions)
{
  #if GRID_LIBARY_DEBUG
    GridLibary::print_name("GridLibary get_index");
    GridLibary::print_array_int("dimensions", dimensions, nr_of_dimensions);
    GridLibary::print_array_int("index", index, nr_of_dimensions);
    GridLibary::print_int("nr_of_dimensions", nr_of_dimensions);
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

double GridLibary::get_length_of_vektor(double* vektor, int nr_of_dimensions)
{
  #if GRID_LIBARY_DEBUG
    GridLibary::print_name("GridLibary get_length_of_vektor");
    GridLibary::print_array_double("vektor", vektor, nr_of_dimensions);
    GridLibary::print_int("nr_of_dimensions", nr_of_dimensions);
  #endif
  double sum = 0;
  for(int i = 0; i < nr_of_dimensions; i++)
  {
    sum = sum + pow(vektor[i], 2);
  }
  return sqrt(sum);
}

double* GridLibary::subtract_array(double* first_array, double* second_array, int lenght)
{
  #if GRID_LIBARY_DEBUG
    GridLibary::print_name("GridLibary subtract_array");
    GridLibary::print_array_double("first_array", first_array, lenght);
    GridLibary::print_array_double("second_array", second_array, lenght);
    GridLibary::print_int("lenght", lenght);
  #endif
  double* to_return = new double[lenght];
  for(int i = 0; i < lenght; i++)
  {
    to_return[i] = first_array[i] - second_array[i];
  }
  return to_return;
}

double* GridLibary::divide_array(double* array, double* factor, int lenght)
{
  #if GRID_LIBARY_DEBUG
    GridLibary::print_name("GridLibary divide_array");
    GridLibary::print_array_double("array", array, lenght);
    GridLibary::print_array_double("factor", factor, lenght);
    GridLibary::print_int("lenght", lenght);
  #endif
  double* to_return = new double[lenght];
  for(int i = 0; i < lenght; i++)
  {
    to_return[i] = array[i] / factor[i];
  }
  return to_return;
}

double* GridLibary::add_array(double* first_array, double* second_array, int lenght)
{
  #if GRID_LIBARY_DEBUG
    GridLibary::print_name("GridLibary add_array");
    GridLibary::print_array_double("first_array", first_array, lenght);
    GridLibary::print_array_double("second_array", second_array, lenght);
    GridLibary::print_int("lenght", lenght);
  #endif
  double* to_return = new double[lenght];
  for(int i = 0; i < lenght; i++)
  {
    to_return[i] = first_array[i] + second_array[i];
  }
  return to_return;
}

double* GridLibary::multiply_array(long* array, double* factor, int lenght)
{
  #if GRID_LIBARY_DEBUG
    GridLibary::print_name("GridLibary multiply_array");
    GridLibary::print_array_long("array", array, lenght);
    GridLibary::print_array_double("factor", factor, lenght);
    GridLibary::print_int("lenght", lenght);
  #endif
  double* to_return = new double[lenght];
  for(int i = 0; i < lenght; i++)
  {
    to_return[i] = array[i] * factor[i];
  }
  return to_return;
}

double* GridLibary::kastrati_value(double* lenght, int lenght_lenght)
{
  #if GRID_LIBARY_DEBUG
    GridLibary::print_name("GridLibary kastrati_value");
    GridLibary::print_array_double("lenght", lenght, lenght_lenght);
    GridLibary::print_int("lenght_lenght", lenght_lenght);
  #endif
  double* to_return = new double[lenght_lenght];
  double lenght_sum = 0;
  for(int i = 0; i < lenght_lenght; i++)
  {
		if(lenght[i] == 0)
		{
			for(int j = 0; j < lenght_lenght; j++)
			{
				to_return[j] = 0;
			}
			to_return[i] = 1;
			return to_return;
		}
		lenght_sum = lenght_sum + lenght[i];
	}

	double relativ_lenght[lenght_lenght];
	for(int i = 0; i < lenght_lenght; i++)
	{
		relativ_lenght[i] = lenght[i] / lenght_sum;
	}

	for(int i = 0; i < lenght_lenght; i++)
	{
		double denominator = 0;
		for(int j = 0; j < lenght_lenght; j++)
		{
			denominator = denominator + (relativ_lenght[i] / relativ_lenght[j]);
		}
		to_return[i] = 1 / denominator;
	}
	//delete lenght;
	return to_return;
}

//#if PRINTGRID || ARRAY_HANDLER_DEBUG || GRID_DATA_MINING_DEBUG || GRID_LIBARY_DEBUG || MPI_PROXY_DEBUG

void GridLibary::print_name(std::string name)
{
  std::cout << name << "\n";
}

void GridLibary::print_array_int(std::string name, int* array, int lenght)
{
  std::cout << name << " {";
  for(int i = 0; i < lenght - 1; i++)
  {
    std::cout << array[i] << ", ";
  }
  std::cout << array[lenght - 1] << "}" << "\n";
}

void GridLibary::print_array_long(std::string name, long* array, int lenght)
{
  std::cout << name << " {";
  for(int i = 0; i < lenght - 1; i++)
  {
    std::cout << array[i] << ", ";
  }
  std::cout << array[lenght - 1] << "}" << "\n";
}

void GridLibary::print_array_double(std::string name, double* array, int lenght)
{
  std::cout << name << " {";
  for(int i = 0; i < lenght - 1; i++)
  {
    std::cout << array[i] << ", ";
  }
  std::cout << array[lenght - 1] << "}" << "\n";
}

void GridLibary::print_int(std::string name, int to_print)
{
  std::cout << name << " hat den Wert: " << to_print << "\n";
}

void GridLibary::print_long(std::string name, long to_print)
{
  std::cout << name << " hat den Wert: " << to_print << "\n";
}

void GridLibary::print_double(std::string name, double to_print)
{
  std::cout << name << " hat den Wert: " << to_print << "\n";
}

//#endif
