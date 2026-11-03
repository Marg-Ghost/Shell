//
// Created by Admin on 02.11.2026.
//

#include "Task.h"
#include "../execute/call.h"

Task::Task(call* new_data) {
    this->data = new_data;
}
//getter and setter
void Task::set_next(Task* new_next) {
    this->next = new_next;
}
void Task::set_data(call* new_data) {
    this->data = new_data;
}
call* Task::get_data() {
    return this->data;
}
Task* Task::get_next() {
    return this->next;
}