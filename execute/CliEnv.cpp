//
// Created by Admin on 30.10.2026.
//

//internal
#include "CliEnv.h"
#include "../structure/Qeue.h"

//external
#include <string>
#include <termios.h>
#include <stdio.h>
#include <unistd.h> // -> für STDIN_FILENO

CliEnv::CliEnv(std::string user,std::string psw, std::string directory) {
    this->root = 0;
    this->user = user;
    this->directory = directory;
    this->psw = psw;
    this->chain = new Qeue();
}
//========================
//Getter und Setter
//========================
void CliEnv::set_user(std::string user) {
    this->user = user;
}
void CliEnv::set_directory(std::string directory) {
    this->directory = directory;
}
void CliEnv::set_root(std::string try_psw) {
    if (try_psw == this->psw) {
        this->root = 1;
    }
    return;
}

std::string CliEnv::get_user() {
    return this->user;
}
std::string CliEnv::get_directory() {
    return this->directory;
}
std::string CliEnv::get_psw() {
    return this->psw;
}
int CliEnv::get_root() {
    return this->root;
}
Qeue* CliEnv::get_chain() {
    return this->chain;
}

//========================
//logic
//========================

void CliEnv::raw_terminal() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &this->orig);
    raw = this->orig;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void CliEnv::norm_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &this->orig);
}

void CliEnv::init_env() {
    this->display_asset(1);
    this->raw_terminal();
}
//============================
//qeue
//===========================
void CliEnv::execute(Task* exe) {
    exe->get_data()->execute();
}

//========================
//Display
//========================
void CliEnv::display_asset(int i){
    FILE *datei;
    switch (i) {
        case 1:
            datei = fopen("assets/start.txt", "r");
            break;
        case 2:
            datei = fopen("assets/help.txt", "r");
            break;
    }

    if (datei == NULL) {
        printf("[Error 001] Cannot open file start.txt\n ");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), datei) != NULL) {
        printf("%s", line);
    }
    fclose(datei);
    printf("\n");
    return;
}
void CliEnv::display_input_cursur() {
    printf("%s $ ", this->user.c_str()); //converts std::string into char* || converts C++ to C
    fflush(stdout); // clear chach bevor input
}