//
// Created by Admin on 30.10.2026.
//

#ifndef INC_0_BUILD_A_CLI_QEUE_H
#define INC_0_BUILD_A_CLI_QEUE_H

#include "Task.h"

class Qeue {
private:
    Task* beginning;
    Task* ending;
public:
    Qeue();
    //getter and setter
    void set_beginning(Task* beginning);
    void set_ending(Task* ending);
    Task* get_beginning();
    Task* get_ending();
    //functions
    void enque(Task* new_task);
    Task* deque();

};



#endif //INC_0_BUILD_A_CLI_QEUE_H
