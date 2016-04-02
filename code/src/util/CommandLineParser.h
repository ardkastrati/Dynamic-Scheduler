/**
 * The command line parser search in the given command line parameters to find scheduler specific ons and parse them.
 * The given parameters are not manipulated and can be passed to the scientific code.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */

#ifndef CODE_COMMANDLINEPARSER_H
#define CODE_COMMANDLINEPARSER_H

#include "../scheduler/StrategyEnum.h"
#include "../scheduler/DesignEnum.h"
#include <getopt.h>
class CommandLineParser {

private:
    /**
     * The design.
     * Standard is master-worker.
     */
    DesignEnum design = MASTER_WORKER;
    /**
     * The Strategy.
     * Standard is FIFO.
     */
    StrategyEnum strategy = ENUM_FIFO;

    /**
     * Pareses the design parameter.
     */
    void parse_design();

    /**
     * Parses the strategy parameter.
     */
    void parse_strategy();
public:

    /**
     * Parse the given command line parameter and search scheduler specific one.
     *
     * @param argc command line parameter count
     * @param argv command line parameter
     */
    void parse(int argc, char* argv[]);

    /**
     * Returns the design.
     *
     * @return the design
     */
    DesignEnum get_design();

    /**
     * Returns the strategy.
     *
     * @return the strategy
     */
    StrategyEnum get_strategy();

};


#endif //CODE_COMMANDLINEPARSER_H
