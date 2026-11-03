//
// Created by Admin on 30.10.2026.
//

#include "Qeue.h"

Qeue::Qeue() {
    this->beginning = NULL;
    this->ending = NULL;
}
//getter and setter
void Qeue::set_beginning(Task* beginning) {
    this->beginning = beginning;
}
void Qeue::set_ending(Task* ending) {
    this->ending = ending;
}
Task* Qeue::get_beginning() {
    return this->beginning;
}
Task* Qeue::get_ending() {
    return this->ending;
}
//functions
void Qeue::enque(Task* new_task) {
    if (this->ending == NULL && this->beginning == NULL) {
        this->beginning = new_task;
        this->ending = new_task;
    }
    this->ending->set_next(new_task);
    this->ending = new_task;
}
Task* Qeue::deque() {
    if (this->beginning == NULL && this->ending == NULL) {
        return NULL;
    }
    if (this->beginning == this->ending) {
        Task* temp = this->beginning;
        this->beginning = NULL;
        this->ending = NULL;
        return temp;
    }
    Task* temp = this->beginning;
    this->beginning = this->beginning->get_next();
    return temp;
}
