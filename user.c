//
//  user.c
//  test_av
//
//  Created by PITV on 24.04.21.
//

#include "user.h"

User user_init(void){
    User single_user;
    single_user.direction_requests_size = 0;
    single_user.floor_call_size = 0;
    single_user.floor_request_size = 0;
    return single_user;
}
// Call from floor where are no free elevators
void new_floor_call(User* single_user){
    int iter = 0;
    int direction = 0;
    while (true) {
        iter++;
        // potenatialy could be replaced with push buttons - when pressed two informations are being send to the management system. Here just a command line input
        printf("Insert floor call no. %d or any letter to finish: ", iter);
        char input[] = "";
        scanf("%s", input);
        bool digit = true;
        for (int i=0; i<strlen(input); i++){
            if (isdigit(input[i])){
                digit = false;
                break;
            }
        }
        // firstly needs to check if input is a number
        if (digit){
            break;
        }
        // then digit is being added to the calling floor number's queue
        else{
            single_user->floor_call_size++;
            if (single_user->floor_call_size == 1){
                single_user->floor_call = malloc(sizeof(int));
            }
            else{
                single_user->floor_call = realloc(single_user->floor_call, single_user->floor_call_size*sizeof(int));
            }
            single_user->floor_call[single_user->floor_call_size-1] = (int)strtol(input, NULL, 10);
            // secondly, calling floor needs to give direction of call - only two options UP or DOWN
            while (true) {
                printf("Insert direction [UP or DOWN] for call no. %d: ", iter);
                char input2[] = "";
                scanf("%s", input2);
                if (strcmp(input2, "UP") == 0){
                    direction = 1;
                    break;
                }
                else if (strcmp(input2, "DOWN") == 0){
                    direction = -1;
                    break;
                }
                // calling floor must specify direction - otherwise it does not make sens
                else {
                    printf("Wrong direction, try again\n");
                }
            }
            // same as with the calling floor number - directions are also being put into array at floor number's corresponding positions
            single_user->direction_requests_size++;
            if (single_user->direction_requests_size == 1){
                single_user->direction_requests = malloc(sizeof(int));
            }
            else{
                single_user->direction_requests = realloc(single_user->direction_requests, single_user->direction_requests_size*sizeof(int));
            }
            single_user->direction_requests[single_user->direction_requests_size-1] = direction;
        }
    }
}
// requests from within the elevator - when one of them is free at the current floor
void new_floor_request(User* single_user){
    int iter = 0;
    while (true) {
        iter++;
        // identically as before - but now only requested floor matters
        printf("Insert destination floor no. %d or any letter to finish: ", iter);
        char input[] = "";
        scanf("%s", input);
        bool digit = true;
        for (int i=0; i<strlen(input); i++){
            if (isdigit(input[i])){
                digit = false;
                break;
            }
        }
        if (digit){
            break;
        }
        else{
            single_user->floor_request_size++;
            if (single_user->floor_request_size == 1){
                single_user->floor_request = malloc(sizeof(int));
            }
            else{
                single_user->floor_request = realloc(single_user->floor_request, single_user->floor_request_size*sizeof(int));
            }
            single_user->floor_request[single_user->floor_request_size-1] = (int)strtol(input, NULL, 10);
        }
    }
}
