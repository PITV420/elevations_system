//
//  main.c
//  test_av
//
//  Created by PITV on 24.04.21.
//

#include <stdio.h>
#include "management.h"

int main(int argc, const char * argv[]) {
    ElevatorSystem new_game = init(4);
    int **stats_for_all;
    stats_for_all = malloc((new_game.number_of_elevs)*sizeof(int));
    for (int i=0; i<new_game.number_of_elevs; i++){
        stats_for_all[i] = malloc(3*sizeof(int));
    }
    
    int step_game = 1;
    while(true){
        step(&new_game, step_game);
        status(&new_game, stats_for_all);
        step_game++;
    }
    return 0;
}
