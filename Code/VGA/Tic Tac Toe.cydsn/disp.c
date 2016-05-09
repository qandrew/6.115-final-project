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

void waiter( int seconds ){   // dumb wait
    int i,j;
    for (i = 0; i < seconds*10; i++){
        for (j = 0; j < seconds*100; j++){
        }
    }
}

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

void disp_grid_draw_xia(struct disp_grid_81* disp, int x_start, int y_start, uint8 color){ // displays character 下 at x,y
    disp_grid_draw_square(disp,x_start,y_start,5,1,color);
    disp_grid_draw_square(disp,x_start+2,y_start+1,1,6,color);
    disp_grid_draw_square(disp,x_start+3,y_start+3,2,1,color);
    disp->matrix[x_start+4][y_start+4] = color;
}

void disp_grid_draw_hu(struct disp_grid_81* disp){ // draws black H U on board
    disp_grid_draw_square(disp,5,5,2,10,0x00); //H
    disp_grid_draw_square(disp,10,5,2,10,0x00);
    disp_grid_draw_square(disp,7,10,3,2,0x00);
    disp_grid_draw_square(disp,14,5,2,10,0x00); //U
    disp_grid_draw_square(disp,19,5,2,10,0x00);
    disp_grid_draw_square(disp,16,13,3,2,0x00);
}

uint8 disp_grid_ttc_getval(struct disp_grid_81* disp, int i){
    int x,y; // first, we want to get the x,y coords
    if (i < 16 && i >= 0){ //z = 0
        x = i%4;
        y = (i-x)/4; // we want to start at 1,1
        x = 2*x + 1;
        y = 2*y + 1;
    }
    else if (i < 32){ // z = 1
        i -= 16;
        x = i%4;
        y = (i-x)/4; // we want to start at 1,11
        x = 2*x + 1;
        y = 2*y + 11;
    }
    else if (i < 48){ // z = 2
        i -= 32;
        x = i%4;
        y = (i-x)/4; // we want to start at 13,4
        x = 2*x + 13;
        y = 2*y + 4;
    }
    else if (i < 64){ // z = 3
        i -= 48;
        x = i%4;
        y = (i-x)/4; // we want to start at 13,14
        x = 2*x + 13;
        y = 2*y + 14;
    }
    uint8 toreturn;
    toreturn = disp->matrix[x][y]; //get the value out of it
    return toreturn;
}

void disp_grid_ttc_place_value(struct disp_grid_81* disp, int i, uint8 value){ // place color based on 
    int x,y; // first, we want to get the x,y coords
    if (i < 16 && i >= 0){ //z = 0
        x = i%4;
        y = (i-x)/4; // we want to start at 1,1
        x = 2*x + 1;
        y = 2*y + 1;
    }
    else if (i < 32){ // z = 1
        i -= 16;
        x = i%4;
        y = (i-x)/4; // we want to start at 1,11
        x = 2*x + 1;
        y = 2*y + 11;
    }
    else if (i < 48){ // z = 2
        i -= 32;
        x = i%4;
        y = (i-x)/4; // we want to start at 13,4
        x = 2*x + 13;
        y = 2*y + 4;
    }
    else if (i < 64){ // z = 3
        i -= 48;
        x = i%4;
        y = (i-x)/4; // we want to start at 13,14
        x = 2*x + 13;
        y = 2*y + 14;
    }
    disp_grid_draw_square(disp,x,y,2,2,value); //dark gray
}

void disp_grid_ttc_place(struct disp_grid_81* disp, int i, int value){ // place color based on 
    int x,y; // first, we want to get the x,y coords
    if (i < 16 && i >= 0){ //z = 0
        x = i%4;
        y = (i-x)/4; // we want to start at 1,1
        x = 2*x + 1;
        y = 2*y + 1;
    }
    else if (i < 32){ // z = 1
        i -= 16;
        x = i%4;
        y = (i-x)/4; // we want to start at 1,11
        x = 2*x + 1;
        y = 2*y + 11;
    }
    else if (i < 48){ // z = 2
        i -= 32;
        x = i%4;
        y = (i-x)/4; // we want to start at 13,4
        x = 2*x + 13;
        y = 2*y + 4;
    }
    else if (i < 64){ // z = 3
        i -= 48;
        x = i%4;
        y = (i-x)/4; // we want to start at 13,14
        x = 2*x + 13;
        y = 2*y + 14;
    }
    if (value == 0){ //now check what color we want to change
        disp_grid_draw_square(disp,x,y,2,2,(i%3)); //deviations from black
    }
    else if (value == 1){
        disp_grid_draw_square(disp,x,y,2,2,0x2A); //light gray
    }
    else if (value == -1){
        disp_grid_draw_square(disp,x,y,2,2,0x15); //dark gray
    }
}

void disp_grid_init_ttc(struct disp_grid_81* disp, int grid[64]){ // initialize the TTC board
    // tags for boards
    disp_grid_draw_square(disp,8,10,1,1,0x30); //second plane with 1 red
    disp_grid_draw_square(disp,19,3,2,1,0x30); //third plane with 2 red
    disp_grid_draw_square(disp,18,13,3,1,0x30); //fourth plane with 3 red
    int i;
    for (i = 0; i < 64; i++){
        disp_grid_ttc_place(disp,i, grid[i]);
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
    waiter(7); //minimum waiting time for 32x24
}


//void run(){
//    UART_Start();                       // initialize UART
//    UART_PutChar(0x81); // init connection; set to 16x12 image 
//    struct disp_grid_81 disp; 
//    
//    struct tic_tac_toe lolz;
// 	  ttc_init(&lolz,4,3);
//    
//    int i;
//    for(i = 0; i < 10; i++){
//        disp_grid_init(&disp,0x3F); // init our display grid matrix to white  
//        disp_grid_transmit(&disp);
//        
//        disp_grid_draw_xia(&disp,26,16,0x30); // draw xia
//        disp_grid_transmit(&disp);
//        
//        disp_grid_init_ttc(&disp,lolz.grid); // init the board
//        disp_grid_transmit(&disp);
//        
//        ttc_step(&disp,&lolz,2,2,2); // step & print
//        disp_grid_transmit(&disp);
//        
//        ttc_step(&disp,&lolz,2,2,3); // step & print
//        disp_grid_transmit(&disp);
//      }
//}

/* [] END OF FILE */
