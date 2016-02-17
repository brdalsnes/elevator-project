#include "matrix.h"
#include "elev.h"
#include "channels.h"
#include "io.h"
#include <stdlib.h>
#include <stdbool.h>

void initMat(){
	for(int i = 0; i < N_FLOORS; i++){
		for(int j = 0; j < N_BUTTONS; j++){
			stateMatrix[i][j] = 0;
		}
	}
}

void listen(){
	for(int i = 0; i < N_FLOORS; i++){
		for(int j = 0; j < N_BUTTONS; j++){

			if(elev_get_button_signal(j, i)){
				stateMatrix[i][j] = 1;

				for(int i = 0; i < priorityQue.size(); i++){
            		printf("%i", priorityQue[i]);
        		}
			}	
		}
	}
}

void lamp(){
	for(int i = 0; i < N_FLOORS; i++){
		for(int j = 0; j < N_BUTTONS; j++){
			elev_set_button_lamp(j, i, stateMatrix[i][j]);
		}
	}
}

void setQue(){
	for(int i = 0; i < N_FLOORS; i++){
		for(int j = 0; j < N_BUTTONS; j++){
			if(notInQue(i)){
				priorityQue.push_back(i);
			}
		}
	}
}

bool notInQue(int floor){
	for(int i = 0; i < priorityQue.size(); i++){
		if(priorityQue[i] == floor){
			return false;
		}
	}
	return true;
}
