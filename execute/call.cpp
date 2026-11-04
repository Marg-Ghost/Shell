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
#include <filesystem>

call::call(std::string command, std::string directory, CliEnv *env) {
    this->command = command;
    this->directory = directory;
    this->env = env;
}

//execute help functions
std::string read_dir(std::string argument);
std::vector<std::string> get_folder(std::string dir, int dot_folder);
std::string get_home_dir();
namespace fs = std::filesystem;

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
    }else if (sepecial == "ls") {
        int complete = 0;
        if (args.size() < argument) {
            printf("Not enough arguments provided");
        }else if (args.size() > argument+1) {
            if (args.size() > argument+2) {
                if (args[argument+1] == "-la") {
                    complete = 1;
                }else {
                    printf("extra argument doesn't match any option");
                }
            }else {
                printf("only accepts one extra parameter");
            }
        }
        std::vector<std::string> folder =  get_folder(this->directory, complete);
        std::string placeholder = "     |--";
        printf("-----------------------------------\n");
        for (int i = 0; i < folder.size(); i++) {
            printf("%s %s\n", placeholder.c_str(), folder.at(i).c_str());
        }
        printf("-----------------------------------");
    }
    printf("\n");
    return;
}

std::vector<std::string> get_folder(std::string dir, int dot_folder) {
    std::vector<std::string> all_folders;

    for (const auto& entry : fs::directory_iterator(dir)) {
        std::string filename = entry.path().filename().string();
        if ((!fs::exists(dir) || !fs::is_directory(dir)) && dot_folder != 3) {
            all_folders.push_back(filename);
            continue;
        }
        if (dot_folder == 0 && !filename.empty() && filename[0] == '.') {
            continue;
        }
        all_folders.push_back('/'+filename);
    }
    return all_folders;
}

void call::read_dir(std::string argument) {
    std::string current_argument = argument;
    std::string backup_dir = this->directory;
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

    }else if (argument[0] == '.') {
        return;
    }else if (argument[0] == '~') {
        std::string target_path = get_home_dir();
        std::string new_folder;
        argument.pop_back(); //entferne '/' nach Tilde
        for (int i = 0; i < argument.length(); i++) {
            if (argument.at(i) == '/') {
                new_folder += argument.at(i);
                argument.pop_back();
                continue;
            }else {
                new_folder += argument.at(i);
                argument.pop_back();
            }
        }
        std::vector<std::string> folder =get_folder("~", 3);
        int is_in_folder = 0;
        for (int i = 0; i < folder.size(); i++) {
            if (folder.at(i) == new_folder) {
                is_in_folder = 1;
            }
        }
        if (is_in_folder == 1) {
            if (argument.length() > 1) {
                this->directory += "~"+new_folder;
                read_dir(argument);
            }else {
                this->directory += "~"+new_folder;
            }
        }else {
            printf("The folder ~ does not contain the folder: %s",argument.c_str());
        }
    }else {
        std::vector<std::string> folder =get_folder(backup_dir, 3);
        int is_in_folder = 0;
        for (int i = 0; i < folder.size(); i++) {
            if (folder.at(i) == '/'+argument) {
                is_in_folder = 1;
            }
        }
        if (is_in_folder == 1) {
            this->directory += "/"+argument;
        }else {
            printf("The folder %s does not contain the folder: %s", this->directory.c_str(), argument.c_str());
        }
        return;

    }
}
std::string get_home_dir() {
    const char* home = std::getenv("HOME"); // Standard für Linux / WSL
    if (!home) {
        home = std::getenv("USERPROFILE");  // Fallback für Windows
    }
    return home ? std::string(home) : "";
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
