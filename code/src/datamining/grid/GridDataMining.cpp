#include "GridDataMining.h"
#include "../../../lib/easylogging++.h"
/**
 * GridDataMinig implementation
 */

GridDataMining::GridDataMining(int parameter_count, long default_value) :
  parameter_count(parameter_count),
  default_value(default_value)
{
}

long GridDataMining::predict(double* parameters)
{
    return 0;
}

void GridDataMining::insert(double* parameters, long runtime)
{

}
