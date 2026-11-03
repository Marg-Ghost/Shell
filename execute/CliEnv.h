//
// Created by Admin on 30.10.2026.
//

#ifndef INC_0_BUILD_A_CLI_TERMINALINSTANCE_H
#define INC_0_BUILD_A_CLI_TERMINALINSTANCE_H

//internal
#include "../structure/Qeue.h"
#include "../structure/Task.h"
//external
#include <string>
#include <termios.h>

class CliEnv {
private:
    int root; // if root ? 1 : 0
    std::string user;
    std::string directory;
    struct termios orig;
    Qeue* chain;
    std::string psw;

public:
    CliEnv(std::string user, std::string psw, std::string directory);
    //getter und setter
    void set_user(std::string user);
    void set_directory(std::string directory);
    void set_root(std::string try_psw);

    std::string get_user();
    std::string get_directory();
    std::string get_psw();
    int get_root();
    Qeue* get_chain();
    //logic
    void init_env();
    void raw_terminal();
    void norm_terminal();
    //qeue
    void execute(Task* exe);
    //display
    void display_asset(int i);
    void display_input_cursur();
};

#endif //INC_0_BUILD_A_CLI_TERMINALINSTANCE_H
