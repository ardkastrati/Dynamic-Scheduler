/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _DATAMINING_H
#define _DATAMINING_H

#include "../TypesExtern.h"
#include "../database/DatabaseServer.h"
#include "../database/DatabaseHandler.h"

class DataMining {
public:
    virtual long predict(double* parameters) = 0;
    virtual void insert(double* parameters, long runtime) = 0;
};

#endif //_DATAMINING_H
