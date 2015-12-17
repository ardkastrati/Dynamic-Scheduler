#include <iostream>
#include "AbstractExecuter.hpp"

int main(int argc, char* argv[]) {
    AbstractExecuter executer = AbstractExecuter::get_new_executer_by_id(0, 10);
}
