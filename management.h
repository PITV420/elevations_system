/*
    Header file for structure elevator system - brain of the operation. This structure combines bothe user and elevators and implifies logic, elevators and requests handling
    As requested in the task:
        - function pickup performs proper floor calls handling and logic in order to make most efficient and ergonomic system
        - status shows the current situtation of all elevators in the building: working on matrix (array of arrays) works most efficient when using pointers
        - step performs a single step of simulation in which all elevators are moving one floor up/down - in real embedded implementation, possibly could be replaced with RTOS that will handle real state of the elevators in real time
    Distribution requests function works with pickup function and also handle and distribute requests that are receved from within an elevator
*/

#ifndef management_h
#define management_h

#include <stdio.h>
#include <pthread.h>
#include "elevator.h"
#include "user.h"

typedef struct{
    Elevator *elevators;
    int number_of_elevs;
    User user_play;
    pthread_t* threads;
    pthread_mutex_t lock;
} ElevatorSystem;

ElevatorSystem init(int elevators_number);
void distribute_requests(ElevatorSystem* elevator_arr, int type);
void pickup(ElevatorSystem* elevator_arr);
void status(ElevatorSystem* elevator_arr, int** output_array);
void step(ElevatorSystem* elevator_arr, int step_no);

#endif /* management_h */
