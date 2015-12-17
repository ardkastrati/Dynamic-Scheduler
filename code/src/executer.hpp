#ifndef EXECUTER_H
#define EXECUTER_H

#include <string>

using namespace std;

class Executer
{
private:
    const string TAG = "Executer";
public:
    Executer();
    static Executer* get_executer_by_rank(int rank, int number_of_processors);
    virtual void execute();

};

#endif // EXECUTER_H
