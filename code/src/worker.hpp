#ifndef WORKER_H
#define WORKER_H

#include <string>
#include "executer.hpp"

using namespace std;

class Worker : public Executer
{
private:
    const string TAG = "Worker";
public:
    Worker();
    virtual void execute();
};

#endif // WORKER_H
