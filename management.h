//
//  management.h
//  test_av
//
//  Created by PITV on 24.04.21.
//

#ifndef management_h
#define management_h

#include <stdio.h>
#include "elevator.h"
#include "user.h"

typedef struct{
    Elevator *elevators;
    int number_of_elevs;
    User user_play;
} ElevatorSystem;

ElevatorSystem init(int elevators_number);
void pickup(ElevatorSystem* elevator_arr);
void status(ElevatorSystem* elevator_arr, int** output_array);
void step(ElevatorSystem* elevator_arr, int step_no);

#endif /* management_h */
