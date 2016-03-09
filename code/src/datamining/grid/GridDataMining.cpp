/**
 * Project Dynamic Scheduler for Scientific Simulations
 */
 #define GRID_DATA_MINING_DEBUG 0
 #define PRINTGRID 0
 #define GRID_LIBARY_DEBUG 0
 #define MPI_PROXY_DEBUG 0
 #define ARRAY_HANDLER_DEBUG 0

#include "GridDataMining.h"
#include "ArrayHandler.h"
#include "MpiProxy.h"
#include "GridLibary.h"
#include <cmath>
#include <assert.h>
#include <stddef.h>

#include "../../database/DatabaseHandler.h"





/*


#if GRID_DATA_MINING_DEBUG
  GridLibary::print_name
  GridLibary::print_
#endif

*/

#if PRINTGRID
void printgrid(MpiProxy* proxy, int nr_of_dimensions)
{

  GridLibary::print_name("Gridprint:");
  int* dimension = proxy -> get_dimensions();
  int grid_lenght = 1;
  for(int i = 0; i < nr_of_dimensions; i++)
  {
    grid_lenght = grid_lenght * dimension[i];
  }
  long time[dimension[nr_of_dimensions - 1]];
  for(int i = 0; i < grid_lenght; i = i + dimension[nr_of_dimensions - 1])
  {
    for(int j = 0; j < dimension[nr_of_dimensions - 1]; j++)
    {
      time[j] = proxy -> get_time(i + j);
    }
    GridLibary::print_array_long("", time, dimension[nr_of_dimensions - 1]);
  }
}
#endif

/**
 * GridDataMining implementation
 */

GridDataMining::GridDataMining(int rank, int target_rank, DatabaseHandler* database, int parameter_count, double* initial_tasks_parameter, long* initial_task_runtime, int initial_task_count)
{
  #if GRID_DATA_MINING_DEBUG
    GridLibary::print_name("GridDataMining Konstruktor");
    GridLibary::print_int("rank", rank);
    GridLibary::print_int("target_rank", target_rank);
    GridLibary::print_int("parameter_count", parameter_count);
    GridLibary::print_array_double("initial_tasks_parameter", initial_tasks_parameter, initial_task_count * parameter_count);
    GridLibary::print_array_long("initial_task_runtime", initial_task_runtime, initial_task_count);
    GridLibary::print_int("initial_task_count", initial_task_count);
  #endif
  assert(rank >= 0);
  assert(target_rank >= 0);
  //database can be NULL
  assert(parameter_count > 0);
  assert(initial_tasks_parameter != NULL);
  assert(initial_task_count > 0);
  make_new_grid_running = true;
  for(int i = 0; i < initial_task_count; i++)
  {
    assert(initial_task_runtime >= 0);
  }
  this->database = database;
  proxy = new MpiProxy(parameter_count, rank, target_rank);
  memory = new ArrayHandler(parameter_count, proxy);
  make_new_grid_running = false;
  nr_of_dimensions = parameter_count;
  nr_of_tasks = 0;
  average_differential = 0;
  //prediction_time_range
  max_differential_time = 1000000; //1 second
  //
  max_parameter = new double[nr_of_dimensions];
  min_parameter = new double[nr_of_dimensions];
  int start_dimenison[nr_of_dimensions];
  double start_offset[nr_of_dimensions];
  double start_increment[nr_of_dimensions];
  for(int i = 0; i < nr_of_dimensions; i++)
  {//dummy values
    start_dimenison[i] = 4;
    start_offset[i] = 0;
    start_increment[i] = 1;
  }
  memory -> set_new_array(start_dimenison, start_increment, start_offset);
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
    GridLibary::print_name("GridDataMining Dekonstuktor");
  #endif
  delete proxy;
  //delete memory;
  delete max_parameter;
  delete min_parameter;
}

long GridDataMining::predict(double* parameters)
{
  #if GRID_DATA_MINING_DEBUG
    GridLibary::print_name("GridDataMining predict");
    GridLibary::print_array_double("parameters", parameters, nr_of_dimensions);
  #endif
  assert (parameters != NULL);
  int nr_of_enviroment_grid_points = pow(2, nr_of_dimensions);
  int* enviroment_index = memory -> get_enviroment_index(parameters);
  int array_lenght = nr_of_dimensions * nr_of_enviroment_grid_points;
  double* enviroment_distances = new double[nr_of_enviroment_grid_points];
  //double enviroment_distances[nr_of_enviroment_grid_points];
  long* enviroment_times = new long[nr_of_enviroment_grid_points];
  for(int i = 0; i < array_lenght; i = i + nr_of_dimensions)
  {//for each vektor in enviroment_index
    int* index = new int[nr_of_dimensions];
    for(int j = 0; j < nr_of_dimensions; j++)
    {
      index[j] = enviroment_index[i + j];
    }
    enviroment_distances[i / nr_of_dimensions] = memory -> get_corrected_distanz(index, parameters);
    enviroment_times[i / nr_of_dimensions] = memory -> get_time(index);
    delete index;
  }
  double* factors = GridLibary::kastrati_value(enviroment_distances, nr_of_enviroment_grid_points);
  double* summand = GridLibary::multiply_array(enviroment_times, factors, nr_of_enviroment_grid_points);
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
    GridLibary::print_name("GridDataMining hard_insert");
    GridLibary::print_array_double("parameters", parameters, nr_of_dimensions);
    GridLibary::print_long("runtime", runtime);
  #endif
  assert (parameters != NULL);
  assert (runtime >= 0);
  int position_vektor[nr_of_dimensions];
  for(int i = 0; i < nr_of_dimensions; i++)
  {
    position_vektor[i] = 0;
  }
  int* dimenison = memory -> get_dimensions();
  int array_lenght = 1;
  for(int i = 0; i < nr_of_dimensions; i++)
  {
    array_lenght = array_lenght * dimenison[i];
  }

  for(int i = 0; i < array_lenght; i++)
  {
    memory -> insert_at_point(position_vektor, parameters, runtime);
    //increase position_vektor
    bool incresed_yet = false;
    for(int j = 0; j < nr_of_dimensions && !incresed_yet; j++)
    {
      if(position_vektor[j] < dimenison[j] - 1)
      {
        position_vektor[j]++;
        incresed_yet = true;
      }
      else
      {
        position_vektor[j] = 0;
      }
    }
  }
  delete dimenison;
  #if PRINTGRID
    printgrid(proxy, nr_of_dimensions);
  #endif
  grid_bookkeping(parameters, runtime);
}

void GridDataMining::insert(double* parameters, long runtime)
{
  #if GRID_DATA_MINING_DEBUG
    GridLibary::print_name("GridDataMining insert");
    GridLibary::print_array_double("parameters", parameters, nr_of_dimensions);
    GridLibary::print_long("runtime", runtime);
  #endif
  assert (parameters != NULL);
  assert (runtime >= 0);
  int* enviroment_index = memory -> get_enviroment_index(parameters);
  int array_lenght = nr_of_dimensions * pow(2, nr_of_dimensions);


  for(int i = 0; i < array_lenght; i = i + nr_of_dimensions)
  {//for each vektor in enviroment_index
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
    GridLibary::print_name("GridDataMining make_new_grid");
  #endif
  make_new_grid_running = true;
  //here is at the moment some dummy code but it works
  int* dimenison = memory -> get_dimensions();
  int new_dimensions[nr_of_dimensions];
  for(int i = 0; i < nr_of_dimensions; i++)
  {
    new_dimensions[i] = dimenison[i] * 2;//this gets realy realy big soon
  }
  double new_increment[nr_of_dimensions];
  for(int i = 0; i < nr_of_dimensions; i++)
  {
    new_increment[i] = (max_parameter[i] - min_parameter[i]) / dimenison[i];
  }
  memory -> set_new_array(new_dimensions, new_increment, min_parameter);
  nr_of_tasks = 0; //reset nr of tasks
  StatisticInquiry *data = database -> dataMiningInquiry();
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

  memory -> push_new_array();
  make_new_grid_running = false;
}

void GridDataMining::grid_bookkeping(double* parameters, long runtime)
{
  #if GRID_DATA_MINING_DEBUG
    GridLibary::print_name("GridDataMining grid_bookkeping");
    GridLibary::print_array_double("parameters", parameters, nr_of_dimensions);
    GridLibary::print_long("runtime", runtime);
  #endif
  assert (parameters != NULL);
  assert (runtime >= 0);

  for(int i = 0; i < nr_of_dimensions; i++)//adapt min and max parameters
  {
     max_parameter[i] = (max_parameter[i] < parameters[i]) ? parameters[i] : max_parameter[i];
     min_parameter[i] = (min_parameter[i] > parameters[i]) ? parameters[i] : min_parameter[i];
  }

  long sceduled_time = predict(parameters);//adapt average_differential
  long differenz_time = sceduled_time - runtime;
  average_differential = (average_differential * nr_of_tasks + differenz_time) / (nr_of_tasks + 1);
  average_differential = (average_differential < 0) ? -average_differential : average_differential;
  nr_of_tasks++;//increase nr of task

  if(check_for_update())
  {
    make_new_grid();
  }
}

bool GridDataMining::check_for_update()
{
  #if GRID_DATA_MINING_DEBUG
    GridLibary::print_name("GridDataMining check_for_update");
    GridLibary::print_double("max_differential_time", max_differential_time);
    GridLibary::print_double("average_differential", average_differential);
  #endif
  if(make_new_grid_running)
  {
    cout << "grid data mining check for updates return_0 " << false << "\n";
    return false;
  }
  else if (max_differential_time < average_differential)
  {
    cout << "grid data mining check for updates return_1 " << true << "\n";
    return true;
  }
  else
  {
    cout << "grid data mining check for updates return_2 " << false << "\n";
    return false;
  }
}
