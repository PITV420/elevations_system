//
//  elevator->c
//  test_av
//
//  Created by PITV on 24.04.21.
//

#include "elevator.h"

Elevator elevator_init(int ID){
    Elevator single_elevator;
    single_elevator.ID = ID;
    single_elevator.floor = 0;
    single_elevator.status = 0;
    single_elevator.queue_size = 0;
    return single_elevator;
}

void insert_element_array(int* arr, int* arr_count, int value, int position){
    for (int i=*arr_count; i>position; i--){
        arr[i] = arr[i-1];
    }
    arr[position] = value;
    *arr_count = *arr_count + 1;
}

void remove_from_queu(Elevator* single_elevator, int position){
    for (int j=position; j<single_elevator->queue_size-1; j++){
        single_elevator->queue[j] = single_elevator->queue[j+1];
    }
    single_elevator->queue[single_elevator->queue_size] = 0;
    single_elevator->queue_size--;
}

void check_floor_queue(Elevator* single_elevator){
    if(single_elevator->queue_size != 0){
        for (int i=0; i<single_elevator->queue_size; i++){
            for (int j=i+1; j<single_elevator->queue_size; j++){
                if (single_elevator->queue[i] == single_elevator->queue[j]) {
                    remove_from_queu(single_elevator, j);
                }
            }
        }
        for (int i=0; i<single_elevator->queue_size; i++) {
            if (single_elevator->floor == single_elevator->queue[i]) {
                single_elevator->floor = single_elevator->queue[i];
                remove_from_queu(single_elevator, i);
            }
        }
    }
}

int get_direction(Elevator* single_elevator){
    if(single_elevator->queue_size != 0){
        if(single_elevator->queue[0] < single_elevator->floor){
            single_elevator->status = 1;
            return -1;
        }
        else if(single_elevator->queue[0] > single_elevator->floor){
            single_elevator->status = 1;
            return 1;
        }
        else{
            check_floor_queue(single_elevator);
            single_elevator->status = 0;
            return 0;
        }
    }
    else{
        single_elevator->status = 0;
        return 0;
    }
}

void update(Elevator* single_elevator, int requests){
    check_floor_queue(single_elevator);
    if (single_elevator->queue_size == 0){
        single_elevator->queue[0] = requests;
        single_elevator->queue_size++;
    }
    else{
        for (int j=0; j<single_elevator->queue_size; j++){
            if (get_direction(single_elevator) < 0) {
                if (single_elevator->queue[j] < requests && requests < single_elevator->floor){
                    insert_element_array(single_elevator->queue, &single_elevator->queue_size, requests, j);
                    break;
                }
                else if (single_elevator->queue[j] == requests){
                    break;
                }
                else if (j == single_elevator->queue_size-1){
                    single_elevator->queue[j + 1] = requests;
                    single_elevator->queue_size++;
                }
            }
            else {
                if (single_elevator->queue[j] > requests && requests > single_elevator->floor){
                    insert_element_array(single_elevator->queue, &single_elevator->queue_size, requests, j);
                    break;
                }
                else if (single_elevator->queue[j] == requests){
                    break;
                }
                else if (j == single_elevator->queue_size-1){
                    single_elevator->queue[j + 1] = requests;
                    single_elevator->queue_size++;
                }
            }
        }
    }
}