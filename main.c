//
//  main.c
//  test_av
//
//  Created by PITV on 24.04.21.
//

#include <stdio.h>
#include "management.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    ElevatorSystem new_game = init(4);
    int step_game = 1;
    while(true){
        step(&new_game, step_game);
        step_game++;
    }
    printf("Hello, World!\n");
    return 0;
}
