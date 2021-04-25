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

void new_floor_call(User* single_user){
    int iter = 1;
    int direction = 0;
    while (true) {
        printf("Insert floor call no. %d or any letter to finish: ", iter);
        char input[MAX_INPUT_NUMBER] = "";
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
            single_user->floor_call[single_user->floor_call_size] = (int)strtol(input, NULL, 10);
            single_user->floor_call_size++;
            while (true) {
                printf("Insert direction [UP or DOWN] for call no. %d: ", iter);
                char input2[MAX_INPUT_NUMBER] = "";
                scanf("%s", input2);
                if (strcmp(input2, "UP") == 0){
                    direction = 1;
                    break;
                }
                else if (strcmp(input2, "DOWN") == 0){
                    direction = -1;
                    break;
                }
                else {
                    printf("Wrong direction, try again\n");
                }
            }
            single_user->direction_requests[single_user->direction_requests_size] = direction;
            single_user->direction_requests_size++;
        }
        iter++;
    }
}

void new_floor_request(User* single_user){
    int iter = 1;
    while (true) {
        printf("Insert destination floor no. %d or any letter to finish: ", iter);
        char input[MAX_INPUT_NUMBER] = "";
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
            single_user->floor_request[single_user->floor_request_size] = (int)strtol(input, NULL, 10);
            single_user->floor_request_size++;
        }
        iter++;
    }
}
