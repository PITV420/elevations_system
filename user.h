/*
    Header file for structure user (single) and it's methodes - that could be easly replaced as an inteface for new requests for real embedded implementation
    As requested in task:
        - two methodes for handling new requests and calls
    First methode simulates calls from other floors then elevators are:
        - user gives two variables: calling floor and requested direction
    Second methode simulates request from within an elevator:
        - user gives only one variable - requested floor
*/

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
