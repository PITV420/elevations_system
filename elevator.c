//
//  elevator->c
//  test_av
//
//  Created by PITV on 24.04.21.
//

#include "elevator.h"

// Initiation of elevator structer. Input number is unique ID
Elevator elevator_init(int ID){
    Elevator single_elevator;
    single_elevator.ID = ID;
    single_elevator.floor = 0;
    single_elevator.status = 0;
    single_elevator.queue_size = 0;
    return single_elevator;
}
// Utility function (oparating on pointer to the structure) insert single 'value' in the requested 'position'
void insert_element_array(Elevator* single_elevator, int value, int position){
    single_elevator->queue = realloc(single_elevator->queue, (single_elevator->queue_size+1)*sizeof(int));
    for (int i=single_elevator->queue_size; i>position; i--){
        single_elevator->queue[i] = single_elevator->queue[i-1];
    }
    single_elevator->queue[position] = value;
    single_elevator->queue_size++;
}
// Utility function, removing element from array (mostly used when elevator reached destitnation floor)
void remove_from_queue(Elevator* single_elevator, int position){
    for (int j=position; j<single_elevator->queue_size-1; j++){
        single_elevator->queue[j] = single_elevator->queue[j+1];
    }
    single_elevator->queue = realloc(single_elevator->queue, (single_elevator->queue_size-1)*sizeof(int));
    single_elevator->queue_size--;
}
// Main purpose of this function is to remove duplicates from queue array
// Also, this function checks if the elevator reached destitnation floor and if yes, remove it from array
void check_floor_queue(Elevator* single_elevator){
    single_elevator->status = 1;
    if(single_elevator->queue_size != 0){
        for (int i=0; i<single_elevator->queue_size; i++){
            for (int j=i+1; j<single_elevator->queue_size; j++){
                if (single_elevator->queue[i] == single_elevator->queue[j]) {
                    remove_from_queue(single_elevator, j);
                }
            }
        }
        for (int i=0; i<single_elevator->queue_size; i++) {
            if (single_elevator->floor == single_elevator->queue[i]) {
                single_elevator->floor = single_elevator->queue[i];
                remove_from_queue(single_elevator, i);
                single_elevator->status = 0;
            }
        }
    }
}
// This function determines the direction in which elevator is moving: -1 is down, 1 is up or 0 is free
int get_direction(Elevator* single_elevator){
    if(single_elevator->queue_size != 0){
        check_floor_queue(single_elevator);
        if(single_elevator->queue[0] < single_elevator->floor){
            return -1;
        }
        else if(single_elevator->queue[0] > single_elevator->floor){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        single_elevator->status = 0;
        return 0;
    }
}
// Last but not least: requested function from the task that update queue and state of the elevator
// Function returns void pointer and gets void pointer becaus of multithreading puropose
void* update(void* arg){
    Elevator* single_elevator = (Elevator*)arg;
    check_floor_queue(single_elevator);
    // Allocate memory if queue is empty
    if (single_elevator->queue_size == 0){
        single_elevator->queue = malloc(sizeof(int));
        single_elevator->queue[0] = single_elevator->requests;
        single_elevator->queue_size++;
    }
    else{
        // for loop will scroll through all elemenets in queue to find the most ergonomic position for new request
        for (int j=0; j<single_elevator->queue_size; j++){
            // Location of new element in queue depends on direction in which elevator is moving
            if (get_direction(single_elevator) < 0) {
                // when elevator is moving down and element is smaller than current floor, it is compared with elements in queue for best fit
                if (single_elevator->queue[j] < single_elevator->requests && single_elevator->requests < single_elevator->floor){
                    insert_element_array(single_elevator, single_elevator->requests, j);
                    break;
                }
                // skip the element tha already is in queue
                else if (single_elevator->queue[j] == single_elevator->requests){
                    break;
                }
                // if there are no better options, element is being added at the end of the queue
                else if (j == single_elevator->queue_size-1){
                    single_elevator->queue_size++;
                    single_elevator->queue = realloc(single_elevator->queue, (single_elevator->queue_size)*sizeof(int));
                    single_elevator->queue[single_elevator->queue_size-1] = single_elevator->requests;
                }
            }
            else {
                // same as befor, but elevator is moving up or free - element needs to be bigger than current floor
                if (single_elevator->queue[j] > single_elevator->requests && single_elevator->requests > single_elevator->floor){
                    insert_element_array(single_elevator, single_elevator->requests, j);
                    break;
                }
                else if (single_elevator->queue[j] == single_elevator->requests){
                    break;
                }
                else if (j == single_elevator->queue_size-1){
                    single_elevator->queue_size++;
                    single_elevator->queue = realloc(single_elevator->queue, (single_elevator->queue_size)*sizeof(int));
                    single_elevator->queue[single_elevator->queue_size-1] = single_elevator->requests;
                }
            }
        }
    }
    return 0;
}
