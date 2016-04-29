/* ========================================
 *
 * Copyright HUDING ENTERPRISES, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Andrew Xia.
 *
 * ========================================
*/

//this file contains all relevant display structures and methods

#ifndef DEVICE_H
#define DEVICE_H
#include <project.h>

#endif

struct disp_grid_81{ //for 32x24 grid
    uint8 matrix[32][24];
    //uint8 damn
};

void disp_grid_init(struct disp_grid_81* disp, uint8 color){ 
    int row,col;
    for (row = 0; row < 32; row++){
        for (col = 0; col < 24; col++){
            disp->matrix[row][col] = color; // init as please
        }
    }
    //UART_PutChar(0x03); // red
}

void disp_grid_draw_square(struct disp_grid_81* disp, int x_start, int y_start, int x_width, int y_height, uint8 color){
    int x,y;
    for (x = x_start; x < x_start + x_width; x++){
        for (y = y_start; y < y_start + y_height; y++){
            disp->matrix[x][y] = color;
        }
    }
}

void disp_grid_transmit (struct disp_grid_81 * disp){ // this function displays the screen
    int row,col;
    for (col = 0; col < 24; col++){
        for (row = 0; row < 32; row++){
            UART_PutChar(disp->matrix[row][col]); 
            //UART_PutChar(20); // blue
        }
    }     
}


void waiter( int seconds )
{   // dumb wait
    int i,j;
    for (i = 0; i < seconds*10; i++){
        for (j = 0; j < seconds*100; j++){
        }
    }
}

void disper(uint8 colorA, uint8 colorB){
    int row,col;
    for (row = 0; row < 32; row++){
        for (col = 0; col < 12; col++){
            UART_PutChar(colorA); // red
            UART_PutChar(colorB); // green
        }
    }    
}


/* [] END OF FILE */
