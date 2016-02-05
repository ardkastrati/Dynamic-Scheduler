//
// Created by fabio on 05.02.16.
//

#include "CommandLineParser.h"

CommandLineParser::CommandLineParser(int argc, char *argv[], char* buffer[])
{
    parse(argc, argv);
}

void CommandLineParser::parse(int argc, char *argv[])
{

}

std::string CommandLineParser::get_design()
{
    return this->design;
}

std::string CommandLineParser::get_strategy()
{
    return this->strategy;
}

void CommandLineParser::get_command_line_for_scientific_code(char ***command_line_parameters)
{

}