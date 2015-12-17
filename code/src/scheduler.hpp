#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "executer.hpp"
#include "schedulingstrategy.hpp"
#include <string>

using namespace std;

class Scheduler : public Executer {
private:
    SchedulingStrategy* scheduler_queue;
    const string TAG = "Scheduler";
public:
    Scheduler();
    ~Scheduler();
    virtual void execute();
};

#endif // SCHEDULER_H
