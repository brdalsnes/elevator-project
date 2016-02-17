#include <stdio.h>

#include "elev.h"
#include "matrix.h"
#include "channels.h"
#include "io.h"

void driveToFloor(int destionationFloor){
    int startFloor = elev_get_floor_sensor_signal();

    while(elev_get_floor_sensor_signal() != destionationFloor){

        if(elev_get_floor_sensor_signal() != -1){
            elev_set_floor_indicator(elev_get_floor_sensor_signal());
        }

        if(startFloor < destionationFloor){
            elev_set_motor_direction(DIRN_UP);
        }
        else if(startFloor > destionationFloor){
            elev_set_motor_direction(DIRN_DOWN);
        }
    }
    elev_set_motor_direction(DIRN_STOP);

    elev_set_floor_indicator(destionationFloor);
}

int main() {
    elev_init();
    initMat();

    printf("Press STOP button to stop elevator and exit program.\n");

    while (1) {
        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            return 0;
        }

        listen();
        lamp();
        setQue();


    } 
}
