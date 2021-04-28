/*
    Header file for structure elevator (single) and it's methodes
    As requested in task:
        - fields in structer are: ID, current floor, and queue (from which destination will be taken)
    Also, has the elevator structure two fileds:
        - status to determine if the elevator is busy (1) or free (0)
        - queue where sorted floors are stored (with it's size as different variable)
        - requests for new floor that will be added to the queue in proper position (for data flow)
    
*/

#ifndef elevator_h
#define elevator_h

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int ID;
    int status;
    int floor;
    int *queue;
    int queue_size;
    int requests;
} Elevator;

Elevator elevator_init(int ID);
void insert_element_array(Elevator* single_elevator, int value, int position);
void remove_from_queue(Elevator* single_elevator, int position);
void check_floor_queue(Elevator* single_elevator);
int get_direction(Elevator* single_elevator);
void* update(void* arg);

#endif /* elevator_h */
