//
//  management.c
//  test_av
//
//  Created by PITV on 24.04.21.
//

#include "management.h"

ElevatorSystem init(int elevators_number){
    ElevatorSystem elevations_go;
    elevations_go.number_of_elevs = elevators_number;
    elevations_go.elevators = malloc(elevators_number*sizeof(Elevator));
    elevations_go.threads = malloc(elevators_number*sizeof(pthread_t));
    // it is neccessery to properly initialize all elevators in the system and user interface
    for (int i=0; i<elevators_number; i++){
        elevations_go.elevators[i] = elevator_init(i);
    }
    elevations_go.user_play = user_init();
    return elevations_go;
}
// distribute all requests and calls in current step
void distribute_requests(ElevatorSystem* elevator_arr, int type){
    // check if request is from within or from calling floors - as an assumption: calling floors have priority in distribution
    if (elevator_arr->user_play.floor_call_size != 0){
        pickup(elevator_arr);
    }
    if (elevator_arr->user_play.floor_request_size != 0){
        // type below zero describe situation when there are more then one free elevator at specific floor
        if (type < 0){
            int busy_iter = 0;
            for (int i=0; i<elevator_arr->user_play.floor_request_size; i++) {
                // multithreading: handling with request sent to specific elevators can be done simulatniously
                elevator_arr->elevators[busy_iter].requests = elevator_arr->user_play.floor_request[i];
                pthread_create(&elevator_arr->threads[busy_iter], NULL, update, (void*)&elevator_arr->elevators[busy_iter]);
                busy_iter++;
                // multithreading: check if elevator that will be handling new call has handled in the queue all previous requests
                if (busy_iter >= elevator_arr->number_of_elevs) {
                    busy_iter = 0;
                    pthread_join(elevator_arr->threads[busy_iter], NULL);
                }
            }
            // All elevators must handled their new calls till that time
            for (int i=0; i<elevator_arr->number_of_elevs; i++){
                pthread_join(elevator_arr->threads[i], NULL);
            }
            // clear requests queue when after all requests are handled
            if (elevator_arr->user_play.floor_request_size != 0){
                free(elevator_arr->user_play.floor_request);
                elevator_arr->user_play.floor_request_size = 0;
            }
        }
        // for a single elevator, multitasking will not speed up system
        else {
            for (int j=0; j<elevator_arr->user_play.floor_request_size; j++){
                elevator_arr->elevators[type].requests = elevator_arr->user_play.floor_request[j];
                update(&elevator_arr->elevators[type]);
            }
            if (elevator_arr->user_play.floor_request_size != 0){
                free(elevator_arr->user_play.floor_request);
                elevator_arr->user_play.floor_request_size = 0;
            }
        }
    }
}
// handling with calls - number of calling floor and direction
void pickup(ElevatorSystem* elevator_arr){
    for (int i=0; i<elevator_arr->user_play.floor_call_size; i++){
        int closest_ID = -1;
        if (closest_ID == -1){
            int distance = 100;
            // need to figure out which elevator is closest to the calling floor and moving in the same diraction as call - checking all elevators and picking up the closest one's ID
            for (int j=0; j<elevator_arr->number_of_elevs; j++){
                if (abs(elevator_arr->elevators[j].floor - elevator_arr->user_play.floor_call[i]) < distance && get_direction(&elevator_arr->elevators[j]) == elevator_arr->user_play.direction_requests[i]) {
                    closest_ID = j;
                    distance = abs(elevator_arr->elevators[j].floor - elevator_arr->user_play.floor_call[i]);
                }
            }
        }
        // if none of elevators are moving in the same diraction as call - algorithm pick the one with smallest queue
        if (closest_ID == -1) {
            pthread_join(elevator_arr->threads[closest_ID], NULL);
            int queue_size = 10000;
            for (int j=0; j<elevator_arr->number_of_elevs; j++){
                if (elevator_arr->elevators[j].queue_size < queue_size) {
                    closest_ID = j;
                    queue_size = elevator_arr->elevators[j].queue_size;
                }
            }
        }
        elevator_arr->elevators[closest_ID].requests = elevator_arr->user_play.floor_call[i];
        update(&elevator_arr->elevators[closest_ID]);
    }
    // clear calls and their directions when all calls are handled
    if (elevator_arr->user_play.direction_requests_size != 0) {
        free(elevator_arr->user_play.floor_call);
        elevator_arr->user_play.floor_call_size = 0;
        free(elevator_arr->user_play.direction_requests);
        elevator_arr->user_play.direction_requests_size = 0;
    }
}
// as requested: status presenting [[ID, current floor, destitnation (next floor in queue)], ...]
void status(ElevatorSystem* elevator_arr, int** output_array){
    // working on matrix - best option is from without this function
    for (int i=0; i<elevator_arr->number_of_elevs; i++){
        output_array[i][0] = elevator_arr->elevators[i].ID;
        output_array[i][1] = elevator_arr->elevators[i].floor;
        if (elevator_arr->elevators[i].queue_size != 0){
            output_array[i][2] = elevator_arr->elevators[i].queue[0];
        }
        else{
            output_array[i][2] = 0;
        }
    }
}
// simulation steps - with a few asumptions
void step(ElevatorSystem* elevator_arr, int step_no){
    // in step 1 all elevators are at level 0. Requests are being distributed comparatively
    if (step_no == 1){
        printf("Step: %d \n Currently all elevators are at level 0\n", step_no);
        printf("Any destinations from floor 0?\n");
        new_floor_request(&elevator_arr->user_play);
        distribute_requests(elevator_arr, -1);
        printf("Any calls for elevator?\n");
        new_floor_call(&elevator_arr->user_play);
        distribute_requests(elevator_arr, -1);
    }
    else{
        printf("Step: %d \n", step_no);
        // firstly check on which floors are all elevators and if one of them is free (get direction = 0) if yes, it can handle new requests from within (simulating people moving inside and choosing destitnation floors)
        for (int i=0; i<elevator_arr->number_of_elevs; i++){
            if (get_direction(&elevator_arr->elevators[i]) == 0) {
                printf("Elevator no. %d reached floor %d\n", elevator_arr->elevators[i].ID, elevator_arr->elevators[i].floor);
                new_floor_request(&elevator_arr->user_play);
                distribute_requests(elevator_arr, i);
            }
        }
        // secondly, simulation asks if there are new calls from other floors
        printf("Any calls for elevator?\n");
        new_floor_call(&elevator_arr->user_play);
        distribute_requests(elevator_arr, -1);
    }
    // lastely, all elevators are moving one floor up/down at the end of every step
    for (int i=0; i<elevator_arr->number_of_elevs; i++){
        elevator_arr->elevators[i].floor = elevator_arr->elevators[i].floor + get_direction(&elevator_arr->elevators[i]);
    }
    for (int i=0; i<elevator_arr->number_of_elevs; i++){
        printf("Eleva ID: %d\n Queue: ", elevator_arr->elevators[i].ID);
        for (int j=0; j<elevator_arr->elevators[i].queue_size; j++){
            printf("%d, ", elevator_arr->elevators[i].queue[j]);
        }
        printf("\n");
    }
}
