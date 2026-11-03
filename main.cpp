//d
// Created by Admin on 30.10.2026.
//

//internal
#include "execute/CliEnv.h"
//external
#include <stdlib.h>
#include <stdio.h>
#include <filesystem>
#include <iostream>


#include <cstdio>
#include <unistd.h>
std::string read_input_user();

int main() {
    std::string name = "admin";
    std::string psw = "123";
    std::string dir = std::filesystem::current_path().string();

    CliEnv* cli_window = new CliEnv(name,psw, dir); //new wegen pointer instance
    cli_window->init_env();


    while (true) {
        cli_window->display_input_cursur();
        std::string input = read_input_user();

        if (input == "exit") {
            exit(0);
        }else if (input == "help") {
            cli_window->display_asset(2);
        }else {
            call* k = new call(input, cli_window->get_directory(), cli_window);
            Task* n = new Task(k);
            cli_window->get_chain()->enque(n);
        }

        while (cli_window->get_chain()->get_beginning() != NULL) {
            cli_window->execute(cli_window->get_chain()->deque());
        }

    }
    return 0;
}
std::string read_input_user() {
    std::string input;
    char c;
    while (read(STDIN_FILENO,&c, 1) == 1) {
        if (c == '\n' || c == '\r') {
            break;
        }else if (c == '\b' || c=='127') {
            if (!input.empty()) {
                input.pop_back();
                std::fflush(stdout);
            }
        }else if (c >= 32 && c <= 126) { // aka im bereich sichtbarer ASCI'S
            input += c;
            //std::putchar(c); // als print out to termminal dynamisch
            std::fflush(stdout); // txt erschein dann direkt im outp. cli
        }
    }
    return input;
}