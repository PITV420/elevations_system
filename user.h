//
//  user.h
//  test_av
//
//  Created by PITV on 24.04.21.
//

#ifndef user_h
#define user_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

typedef struct{
    int *floor_call;
    int floor_call_size;
    int *direction_requests;
    int direction_requests_size;
    int *floor_request;
    int floor_request_size;
} User;

User user_init(void);
void new_floor_call(User* single_user);
void new_floor_request(User* single_user);

#endif /* user_h */
