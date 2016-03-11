/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _EXECUTER_H
#define _EXECUTER_H

#include <string>

class Executer {
protected:
    int rank;
    int number_of_processors;
public: 
    Executer(int rank, int number_of_processors);
    virtual void execute(int argc, char* argv[]) = 0;
    
    /**
     * Returns a executer instance depending on the 
     * @param rank
     * @param number_of_processors
     */
    static Executer* get_new_executer_by_rank(int rank, int number_of_processors, std::string design, std::string strategy);
};

#endif //_EXECUTER_H
