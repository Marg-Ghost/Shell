//
// Created by Admin on 02.11.2026.
//
//internal
#include "call.h"
#include "CliEnv.h"

//external
#include <iostream>
#include <vector>
#include <sstream>

//außer klasse methods
#include <cstdio>
#include <unistd.h>

call::call(std::string command, std::string directory, CliEnv *env) {
    this->command = command;
    this->directory = directory;
    this->env = env;
}

//execute help functions
std::string read_dir(std::string argument);

void call::execute() {
    std::stringstream ss(this->command);
    std::vector<std::string> args;
    while(ss >> this->command) {
        args.push_back(this->command);
    }
    if (args.size() == 0) {return;}
    std::string sepecial = args[0];
    if (args[0] == "sudo") {
        if (this->env->get_root() != 1) {
            if (this->ask_psw() == 1) {
                printf("Root privlages granted!");
            }else {
                printf("Root privlages denied!");
                return;
            }
        }
        if (args.size() < 2) {
            printf("[Error] Not enough arguments provided");
            return;
        }
        sepecial = args[1];
    }
    // ACHTUNG! DU kannst switch (sepecial) nur mit int durchführen deswegen ist hier ein if/else
    int argument = sepecial == args[0] ? 1 : 2;
    if(sepecial == "cd") {
        if (args.size() < argument) {
            printf ("Missing argument");
        }else if (args.size() > argument+1) {
            printf("cd doesn't take more than 1 input");
        }
        //ändert direkt global this->directory
        read_dir(args[argument]);
        this->env->set_directory(this->directory);
        printf("dir: %s", this->directory.c_str());
    }else if (sepecial == "pwd") {
        printf("%s",this->directory.c_str());
    }else if (sepecial == "echo") {
        printf("%s",sepecial.c_str());
    }
    printf("\n");
    return;
}
void call::read_dir(std::string argument) {
    std::string current_argument = argument;
    if (argument[0] == '.' && argument[1] == '.') {
        for (int i = this->directory.length() -1 ; i > 0; i--) {
            if (this->directory.at(i) == '/') {
                    this->directory.pop_back();
                    break;
            }else {
                this->directory.pop_back();
            }
       }
        if(argument[2] == '/') {
            call::read_dir(current_argument.substr(3));
        }
    }else if (argument[0] == '~') {
        this->directory = argument;
    }else {
        this->directory += "/"+argument;
    }
}

std::string read_input_user();

int call::ask_psw() {
    for (int i = 0; i < 3; i++) {
        std::string input = read_input_user();
        if (this->env->get_psw() == input) {
            env->set_root(input);
            return 1;
        }else {
            printf("Wrong Password Tries left : %i", 2 - i);
        }
    }
    return 0;
}
