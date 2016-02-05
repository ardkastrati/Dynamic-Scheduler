//
// Created by fabio on 03.02.16.
//

#ifndef CODE_DUMMYDATAMINING_H
#define CODE_DUMMYDATAMINING_H

#include "DataMining.h"

class DummyDataMining : public DataMining {

    void init(int rank, int target_rank, int number_of_important_parameters);

    long predict(double* parameters);

    void insert(double* parameters, long runtime);
};


#endif //CODE_DUMMYDATAMINING_H
