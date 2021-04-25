//
//  elevator.h
//  test_av
//
//  Created by PITV on 24.04.21.
//

#ifndef elevator_h
#define elevator_h

#include <stdio.h>
#include "utilities.h"

#define MAX_QUEUE_SIZE 100

typedef struct{
    int ID;
    int status;
    int floor;
    int queue[MAX_QUEUE_SIZE];
    int queue_size;
} Elevator;

Elevator elevator_init(int ID);
void insert_element_array(int* arr, int* arr_count, int value, int position);
void remove_from_queu(Elevator* single_elevator, int position);
void check_floor_queue(Elevator* single_elevator);
int get_direction(Elevator* single_elevator);
void update(Elevator* single_elevator, int requests);

#endif /* elevator_h */