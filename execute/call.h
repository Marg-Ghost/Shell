//
// Created by Admin on 02.11.2026.
//

#ifndef INC_0_BUILD_A_CLI_CALL_H
#define INC_0_BUILD_A_CLI_CALL_H
//external
#include <string>
#include <vector>
//internal
//#include "CliEnv.h"
class CliEnv;

class call {
private:
    int needs_root; // if ture ? 1 : 0
    std::string command;
    std::string directory;
    CliEnv* env;

public:
    call(std::string command, std::string directory, CliEnv* env);
    void execute();
    int ask_psw();

    //help execute functions
    //müssen hier sein sonst wird recucrsion unnötig komplex
    void read_dir(std::string argument);
};



#endif //INC_0_BUILD_A_CLI_CALL_H
