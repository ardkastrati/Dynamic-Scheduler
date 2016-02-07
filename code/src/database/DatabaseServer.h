#ifndef DATABASESERVER_H
#define DATABASESERVER_H

#include "../Executor.h"
#include "DatabaseHandler.h"

class DatabaseServer: public Executor
{
public:
    DatabaseServer(int rank, int number_of_processors);
    ~DatabaseServer();
    void execute(int argc, char* argv[]);
private:

    DatabaseHandler*  database_handler;

    void run();
    void preprocessing();
};

#endif // DATABASESERVER_H
