//
// Created by fabio on 05.02.16.
//

#include "CommandLineParser.h"
#include <string>


DesignEnum CommandLineParser::get_design()
{
    return this->design;
}

StrategyEnum CommandLineParser::get_strategy()
{
    return this->strategy;
}

void CommandLineParser::parse(int argc, char **argv)
{
    struct option long_options[] {
            {"design", required_argument, 0, 'd'},
            {"strategy", required_argument, 0, 's'}};

    int iarg = 0;
    int index;
    while (iarg != -1) {
        iarg = getopt_long(argc, argv, "", long_options, &index);

        switch (iarg)
        {
            case 'd':
                parse_design();
                break;
            case 's':
                parse_strategy();
                break;
        }
    }
}

void CommandLineParser::parse_design()
{
    std::string taskstealing_as_string("taskstealing");
    std::string master_as_string("master-worker");
    if (taskstealing_as_string.compare(optarg) == 0) {
        design = TASK_STEALING;
    } else if (master_as_string.compare(optarg) == 0)
    {
        design = MASTER_WORKER;
    } else
    {
        throw "Design does not exist";
    }
}

void CommandLineParser::parse_strategy()
{
    std::string fifo_as_string("fifo");
    std::string lifo_as_string("lifo");
    std::string sjf_as_string("sjf");
    std::string ljf_as_string("ljf");

    if (fifo_as_string.compare(optarg) == 0)
    {
        strategy = ENUM_FIFO;
    } else if (lifo_as_string.compare(optarg) == 0)
    {
        strategy = ENUM_LIFO;
    }else if (sjf_as_string.compare(optarg) == 0)
    {
        strategy = ENUM_SJF;
    } else if (ljf_as_string.compare(optarg) == 0)
    {
        strategy = ENUM_LJF;
    } else
    {
        throw "Strategy does not exist";
    }
}