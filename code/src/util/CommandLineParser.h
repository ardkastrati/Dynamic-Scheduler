//
// Created by fabio on 05.02.16.
//

#ifndef CODE_COMMANDLINEPARSER_H
#define CODE_COMMANDLINEPARSER_H

#include "../scheduler/StrategyEnum.h"
#include "../scheduler/DesignEnum.h"
#include <getopt.h>
/**
 *
 */
class CommandLineParser {

private:
    /**
     *
     */
    DesignEnum design = MASTER_WORKER;
    /**
     *
     */
    StrategyEnum strategy = ENUM_FIFO;



    void parse_design();
    void parse_strategy();
public:
    void parse(int argc, char* argv[]);
    DesignEnum get_design();
    StrategyEnum get_strategy();

};


#endif //CODE_COMMANDLINEPARSER_H
