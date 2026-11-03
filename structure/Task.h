//
// Created by Admin on 02.11.2026.
//

#ifndef INC_0_BUILD_A_CLI_TASK_H
#define INC_0_BUILD_A_CLI_TASK_H

#include "../execute/call.h"

class Task{
private:
    Task* next;
    call* data;
public:
    Task(call* new_data);
    //getter and setter
    void set_next(Task* new_next);
    void set_data(call* new_data);
    call* get_data();
    Task* get_next();
};



#endif //INC_0_BUILD_A_CLI_TASK_H
