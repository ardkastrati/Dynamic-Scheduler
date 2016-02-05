/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _GRIDDATAMINING_H
#define _GRIDDATAMINING_H

#include "../DataMining.h"

class GridDataMining : public DataMining {
private:
    int parameter_count;
    long default_value;
public:
    GridDataMining(int parameter_count, long default_value);
    long predict(double* parameters);
    void insert(double* parameters, long runtime);
};

#endif //_GRIDDATAMINING_H
