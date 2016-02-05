//
// Created by fabio on 05.02.16.
//

#ifndef CODE_COMMANDLINEPARSER_H
#define CODE_COMMANDLINEPARSER_H

#include <string>
/**
 *
 */
class CommandLineParser {

private:
    /**
     *
     */
    std::string design;
    /**
     *
     */
    std::string strategy;
    std::string command_line_for_scientific_code[];

    void parse(int argc, char* argv[]);

public:
    CommandLineParser(int argc, char* argv[], char* buffer[]);
    std::string get_design();
    std::string get_strategy();
    void get_command_line_for_scientific_code(char** command_line_parameters[]);

};


#endif //CODE_COMMANDLINEPARSER_H
