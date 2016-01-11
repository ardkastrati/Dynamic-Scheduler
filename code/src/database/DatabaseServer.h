#ifndef DATABASESERVER_H
#define DATABASESERVER_H

#include "../Executer.h"

class DatabaseServer: public Executer
{
public:
    DatabaseServer(int rank, int number_of_processors);
    void execute(int argc, char* argv[]);
private:
    void run();
    void preprocessing();
};

#endif // DATABASESERVER_H
