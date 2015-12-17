#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "executer.hpp"
#include <string>

using namespace std;

class Scheduler : public Executer {
private:
    const string TAG = "Scheduler";
public:
    Scheduler();
    virtual void execute();
};

#endif // SCHEDULER_H
