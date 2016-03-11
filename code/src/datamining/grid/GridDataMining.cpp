/**
 * Implements the GridDataMining.h.
 */
 #define GRID_DATA_MINING_DEBUG 1
 #define PRINTGRID 0
 #define GRID_LIBRARY_DEBUG 0
 #define DATASTORAGE_DEBUG 0
 #define ARRAY_HANDLER_DEBUG 0

#include "GridDataMining.h"
#include "ArrayHandler.h"
#include "DataStorage.h"
#include "GridLibrary.h"
#include <cmath>
#include <assert.h>
#include <stddef.h>

#include "../../database/DatabaseHandler.h"





/*


#if GRID_DATA_MINING_DEBUG
  GridLibrary::print_name
  GridLibrary::print_
#endif

*/

#if PRINTGRID
void printgrid(DataStorage* proxy, int nr_of_dimensions)
{

  GridLibrary::print_name("Gridprint:");
  int* dimension = proxy -> get_dimensions();
  int grid_length = 1;
  for(int i = 0; i < nr_of_dimensions; i++)
  {
    grid_length = grid_length * dimension[i];
  }
  long time[dimension[nr_of_dimensions - 1]];
  for(int i = 0; i < grid_length; i = i + dimension[nr_of_dimensions - 1])
  {
    for(int j = 0; j < dimension[nr_of_dimensions - 1]; j++)
    {
      time[j] = proxy -> get_time(i + j);
    }
    GridLibrary::print_array_long("", time, dimension[nr_of_dimensions - 1]);
  }
}
#endif

/**
 * GridDataMining implementation
 */

GridDataMining::GridDataMining(DatabaseHandler* database, int parameter_count, double* initial_tasks_parameter, long* initial_task_runtime, int initial_task_count, double max_deviation_time, double start_offset, double start_increment, int start_dimension)
{
  #if GRID_DATA_MINING_DEBUG
    GridLibrary::print_name("GridDataMining constructor");
    GridLibrary::print_int("parameter_count", parameter_count);
    GridLibrary::print_array_double("initial_tasks_parameter", initial_tasks_parameter, initial_task_count * parameter_count);
    GridLibrary::print_array_long("initial_task_runtime", initial_task_runtime, initial_task_count);
    GridLibrary::print_int("initial_task_count", initial_task_count);
  #endif
  assert(database != NULL);
  assert(parameter_count > 0);
  assert(initial_tasks_parameter != NULL);
  assert(initial_task_count > 0);
  make_new_grid_running = true;
  for(int i = 0; i < initial_task_count; i++)
  {
    assert(initial_task_runtime >= 0);
  }
  this -> database = database;
  proxy = new DataStorage(parameter_count);
  memory = new ArrayHandler(parameter_count, proxy);
  nr_of_dimensions = parameter_count;
  nr_of_tasks = 0;
  average_deviation = 0;
  //prediction_time_range
  this -> max_deviation_time = max_deviation_time;
  //
  max_parameter = new double[nr_of_dimensions];
  min_parameter = new double[nr_of_dimensions];
  int dimension[nr_of_dimensions];
  double offset[nr_of_dimensions];
  double increment[nr_of_dimensions];
  for(int i = 0; i < nr_of_dimensions; i++)
  {
    dimension[i] = start_dimension;
    offset[i] = start_offset;
    increment[i] = start_increment;
  }
  memory -> set_new_array(dimension, increment, offset);
  for(int i = 0; i < initial_task_count * nr_of_dimensions; i = i + nr_of_dimensions)
  {
    double parameter[nr_of_dimensions];
    for(int j = 0; j < nr_of_dimensions; j++)
    {
      parameter[j] = initial_tasks_parameter[i + j];
      if(i == 0)
      {
        max_parameter[j] = parameter[j];
        min_parameter[j] = parameter[j];
      }
    }
    hard_insert(parameter, initial_task_runtime[i / nr_of_dimensions]);
  }
  make_new_grid_running = false;
}

GridDataMining::~GridDataMining()
{
  #if GRID_DATA_MINING_DEBUG
    GridLibrary::print_name("GridDataMining Destructor");
  #endif
  delete proxy;
  //delete memory;
  delete max_parameter;
  delete min_parameter;
}

long GridDataMining::predict(double* parameters)
{
  #if GRID_DATA_MINING_DEBUG
    GridLibrary::print_name("GridDataMining predict");
    GridLibrary::print_array_double("parameters", parameters, nr_of_dimensions);
  #endif
  assert (parameters != NULL);
  int nr_of_enviroment_grid_points = pow(2, nr_of_dimensions);
  int* enviroment_index = memory -> get_enviroment_index(parameters);
  int array_length = nr_of_dimensions * nr_of_enviroment_grid_points;
  double* enviroment_distances = new double[nr_of_enviroment_grid_points];
  //double enviroment_distances[nr_of_enviroment_grid_points];
  long* enviroment_times = new long[nr_of_enviroment_grid_points];
  for(int i = 0; i < array_length; i = i + nr_of_dimensions)
  {//for each vector in enviroment_index
    int* index = new int[nr_of_dimensions];
    for(int j = 0; j < nr_of_dimensions; j++)
    {
      index[j] = enviroment_index[i + j];
    }
    enviroment_distances[i / nr_of_dimensions] = memory -> get_corrected_distanz(index, parameters);
    enviroment_times[i / nr_of_dimensions] = memory -> get_time(index);
    delete index;
  }
  double* factors = GridLibrary::kastrati_value(enviroment_distances, nr_of_enviroment_grid_points);
  double* summand = GridLibrary::multiply_array(enviroment_times, factors, nr_of_enviroment_grid_points);
  //sum the array
  double sum = 0;
  for(int i = 0; i < nr_of_enviroment_grid_points; i++)
  {
    sum = sum + summand[i];
  }
  delete enviroment_index;
  delete enviroment_distances;
  delete enviroment_times;
  delete factors;
  delete summand;
  return (long) sum;
}


void GridDataMining::hard_insert(double* parameters, long runtime)
{
  #if GRID_DATA_MINING_DEBUG
    GridLibrary::print_name("GridDataMining hard_insert");
    GridLibrary::print_array_double("parameters", parameters, nr_of_dimensions);
    GridLibrary::print_long("runtime", runtime);
  #endif
  assert (parameters != NULL);
  assert (runtime >= 0);
  int position_vector[nr_of_dimensions];
  for(int i = 0; i < nr_of_dimensions; i++)
  {
    position_vector[i] = 0;
  }
  int* dimension = memory -> get_dimensions();
  int array_length = 1;
  for(int i = 0; i < nr_of_dimensions; i++)
  {
    array_length = array_length * dimension[i];
  }

  for(int i = 0; i < array_length; i++)
  {
    memory -> insert_at_point(position_vector, parameters, runtime);
    //increase position_vector
    bool incresed_yet = false;
    for(int j = 0; j < nr_of_dimensions && !incresed_yet; j++)
    {
      if(position_vector[j] < dimension[j] - 1)
      {
        position_vector[j]++;
        incresed_yet = true;
      }
      else
      {
        position_vector[j] = 0;
      }
    }
  }
  delete dimension;
  #if PRINTGRID
    printgrid(proxy, nr_of_dimensions);
  #endif
  grid_bookkeping(parameters, runtime);
}

void GridDataMining::insert(double* parameters, long runtime)
{
  #if GRID_DATA_MINING_DEBUG
    GridLibrary::print_name("GridDataMining insert");
    GridLibrary::print_array_double("parameters", parameters, nr_of_dimensions);
    GridLibrary::print_long("runtime", runtime);
  #endif
  assert (parameters != NULL);
  assert (runtime >= 0);
  int* enviroment_index = memory -> get_enviroment_index(parameters);
  int array_length = nr_of_dimensions * pow(2, nr_of_dimensions);


  for(int i = 0; i < array_length; i = i + nr_of_dimensions)
  {//for each vector in enviroment_index
    int* index = new int[nr_of_dimensions];
    for(int j = 0; j < nr_of_dimensions; j++)
    {
      index[j] = enviroment_index[i + j];
    }
    memory -> insert_at_point(index, parameters, runtime);
    delete index;
  }
  delete enviroment_index;

  #if PRINTGRID
    printgrid(proxy, nr_of_dimensions);
  #endif
  grid_bookkeping(parameters, runtime);
}

void GridDataMining::make_new_grid()
{
  #if GRID_DATA_MINING_DEBUG
    GridLibrary::print_name("GridDataMining make_new_grid");
  #endif
  make_new_grid_running = true;
  //here is at the moment some dummy code but it works
  int* dimension = memory -> get_dimensions();
  int new_dimensions[nr_of_dimensions];
  for(int i = 0; i < nr_of_dimensions; i++)
  {
    new_dimensions[i] = dimension[i] * 2;//this gets really big really soon
  }
  double new_increment[nr_of_dimensions];
  for(int i = 0; i < nr_of_dimensions; i++)
  {
    new_increment[i] = (max_parameter[i] - min_parameter[i]) / dimension[i];
  }
  memory -> set_new_array(new_dimensions, new_increment, min_parameter);
  nr_of_tasks = 0; //reset nr of tasks
  dataInquiry *data = database -> dataMiningInquiry();
  int former_task_count = data->runtime.size();
  long runtime;
  double* parameter;
  for(int i = 0; i < former_task_count; i++)
  {
    parameter = new double[nr_of_dimensions];
    runtime = data -> runtime[i];
    for(int j = 0; j < nr_of_dimensions; j++)
    {
      assert(j + i * nr_of_dimensions < data->para.size());
      parameter[j] = data -> para[j + i * nr_of_dimensions];
    }
    if(i == 0)
    {
      hard_insert(parameter, runtime);//to create default values
    }
    else
    {
      insert(parameter, runtime);
    }
    delete parameter;
  }
  make_new_grid_running = false;
}

void GridDataMining::grid_bookkeping(double* parameters, long runtime)
{
  #if GRID_DATA_MINING_DEBUG
    GridLibrary::print_name("GridDataMining grid_bookkeping");
    GridLibrary::print_array_double("parameters", parameters, nr_of_dimensions);
    GridLibrary::print_long("runtime", runtime);
  #endif
  assert (parameters != NULL);
  assert (runtime >= 0);

  for(int i = 0; i < nr_of_dimensions; i++)//adapt min and max parameters
  {
     max_parameter[i] = (max_parameter[i] < parameters[i]) ? parameters[i] : max_parameter[i];
     min_parameter[i] = (min_parameter[i] > parameters[i]) ? parameters[i] : min_parameter[i];
  }

  long sceduled_time = predict(parameters);//adapt average_deviation
  long difference_time = sceduled_time - runtime;
  difference_time = (difference_time < 0) ? -difference_time : difference_time;
  average_deviation = (average_deviation * nr_of_tasks + difference_time) / (nr_of_tasks + 1);
  nr_of_tasks++;//increase nr of task

  if(check_for_update())
  {
    make_new_grid();
  }
}

bool GridDataMining::check_for_update()
{
  #if GRID_DATA_MINING_DEBUG
    GridLibrary::print_name("GridDataMining check_for_update");
    GridLibrary::print_double("max_deviation_time", max_deviation_time);
    GridLibrary::print_double("average_deviation", average_deviation);
  #endif
  if(make_new_grid_running)
  {
    return false;
  }
  else if (max_deviation_time < average_deviation)
  {
    return true;
  }
  else
  {
    return false;
  }
}
