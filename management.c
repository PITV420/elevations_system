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
    for (int i=0; i<elevators_number; i++){
        elevations_go.elevators[i] = elevator_init(i);
    }
    elevations_go.user_play = user_init();
    return elevations_go;
}

void pickup(ElevatorSystem* elevator_arr){
    for (int i=0; i<elevator_arr->user_play.floor_call_size; i++){
        int closest_ID = -1;
        if (closest_ID == -1){
            int distance = 100;
            for (int j=0; j<elevator_arr->number_of_elevs; j++){
                if (abs(elevator_arr->elevators[j].floor - elevator_arr->user_play.floor_call[i]) < distance && get_direction(&elevator_arr->elevators[j]) == elevator_arr->user_play.direction_requests[i]) {
                    closest_ID = j;
                    distance = abs(elevator_arr->elevators[j].floor - elevator_arr->user_play.floor_call[i]);
                }
            }
        }
        if (closest_ID == -1) {
            int queue_size = 100;
            for (int j=0; j<elevator_arr->number_of_elevs; j++){
                if (elevator_arr->elevators[j].queue_size < queue_size) {
                    closest_ID = j;
                    queue_size = elevator_arr->elevators[j].queue_size;
                }
            }
        }
        update(&elevator_arr->elevators[closest_ID], elevator_arr->user_play.floor_call[i]);
        elevator_arr->user_play.floor_call[i] = 0;
        elevator_arr->user_play.direction_requests[i] = 0;
    }
    elevator_arr->user_play.floor_call_size = 0;
    elevator_arr->user_play.direction_requests_size = 0;
}

void status(ElevatorSystem* elevator_arr, int** output_array){
    for (int i=0; i<elevator_arr->number_of_elevs; i++){
        output_array[i][0] = elevator_arr->elevators[i].ID;
        output_array[i][1] = elevator_arr->elevators[i].floor;
        output_array[i][2] = elevator_arr->elevators[i].queue[0];
    }
}

void step(ElevatorSystem* elevator_arr, int step_no){
    if (step_no == 1){
        printf("Step: %d \n Currently all elevators are at level 0\n", step_no);
        printf("Any destinations from floor 0?\n");
        new_floor_request(&elevator_arr->user_play);
        int busy_iter = 0;
        for (int i=0; i<elevator_arr->user_play.floor_request_size; i++) {
            if (busy_iter >= elevator_arr->number_of_elevs) {
                busy_iter = 0;
            }
            update(&elevator_arr->elevators[busy_iter], elevator_arr->user_play.floor_request[i]);
            elevator_arr->user_play.floor_request[i] = 0;
            busy_iter++;
        }
        printf("Any calls for elevator?\n");
        elevator_arr->user_play.floor_request_size = 0;
        new_floor_call(&elevator_arr->user_play);
        busy_iter = 0;
        for (int i=0; i<elevator_arr->user_play.floor_call_size; i++) {
            if (busy_iter >= elevator_arr->number_of_elevs){
                busy_iter = 0;
            }
            update(&elevator_arr->elevators[busy_iter], elevator_arr->user_play.floor_call[i]);
            elevator_arr->user_play.floor_call[i] = 0;
            elevator_arr->user_play.direction_requests[i] = 0;
            busy_iter++;
        }
        elevator_arr->user_play.floor_call_size = 0;
        elevator_arr->user_play.direction_requests_size = 0;
    }
    else{
        printf("Step: %d \n", step_no);
        for (int i=0; i<elevator_arr->number_of_elevs; i++){
            if (get_direction(&elevator_arr->elevators[i]) == 0) {
                printf("Elevator no. %d reached floor %d\n", elevator_arr->elevators[i].ID, elevator_arr->elevators[i].floor);
                new_floor_request(&elevator_arr->user_play);
                for (int j=0; j<elevator_arr->user_play.floor_request_size; j++){
                    update(&elevator_arr->elevators[i], elevator_arr->user_play.floor_request[j]);
                    elevator_arr->user_play.floor_request[j] = 0;
                }
                elevator_arr->user_play.floor_request_size = 0;
            }
        }
        printf("Any calls for elevator?\n");
        new_floor_call(&elevator_arr->user_play);
        pickup(elevator_arr);
    }
    int **stats_for_all;
    stats_for_all = malloc((elevator_arr->number_of_elevs+1)*sizeof(int));
    for (int i=0; i<elevator_arr->number_of_elevs; i++){
        stats_for_all[i] = malloc(3*sizeof(int));
        elevator_arr->elevators[i].floor = elevator_arr->elevators[i].floor + get_direction(&elevator_arr->elevators[i]);
    }
    status(elevator_arr, stats_for_all);
    for (int i=0; i<elevator_arr->number_of_elevs; i++){
        printf("Status for elevator: %d \n Current floor: %d \n Destination: %d \n\n", stats_for_all[i][0], stats_for_all[i][1],stats_for_all[i][2]);
    }
}
