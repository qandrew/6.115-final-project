/* ========================================
 *
 * Copyright Andrew MIT 6.115, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF MIT 6.115.
 *
 * This file is necessary for your project to build.
 * Please do not delete it.
 *
 * ========================================
*/

#include <device.h>
#include <unistd.h>

struct disp_grid_81{ //for 32x24 grid
    uint8 matrix[32][24]; 
};

struct tic_tac_toe{
	int size;
	int dimension;
	int player; // 1 is player A, -1 is player B
	int turn;
	int game_not_won;
	// int grid_eval[]; //this keeps track of scores of all diagonals
	int grid[64]; // a usually size 64 grid containing our board
};


void main()
{	
    UART_Start();                       // initialize UART
    UART_PutChar(0x81); // init connection; set to 16x12 image 
    struct disp_grid_81 disp; 
    disp_grid_init(&disp,0x3F); // init our display grid matrix to white  
    
    struct tic_tac_toe lolz;
 	ttc_init(&lolz,4,3);    
    disp_grid_init_ttc(&disp,lolz.grid); // init the board
    disp_grid_draw_xia(&disp,26,16,0x30); // draw xia
    disp_grid_transmit(&disp);
    
	LCD_Start();					    // initialize lcd
    uint8 Values;
    int x,y;
    
    
    while (lolz.game_not_won == 0){
        Values = read_from_8255(Values);
        if (Values >= 48 && Values <= 57){ //integer value
            y = Values - 48; // convert from ASCII to int
            x = y % 4; //get row value
            y = y / 4; // 
        }
        if (ttc_get_grid(&lolz,x,y,0) == 0){ // has not been accessed
            ttc_step(&disp,&lolz,x,y,0); // step & print
            disp_grid_transmit(&disp);
            LCD_PrintString("HU");
        }
        
    }
    LCD_ClearDisplay();
    LCD_Position(0,0); //move to bot row
    LCD_PrintString("GAME OVER!");
    
    

    for(;;)
    {
    }
}

/* [] END OF FILE */


//CY_ISR(RX_INT)
//{
//    LCD_PutChar(UART_ReadRxData());     // RX ISR
//}

//CyGlobalIntEnable;
//rx_int_StartEx(RX_INT);             // start RX interrupt (look for CY_ISR with RX_INT address)
                                    // for code that writes received bytes to LCD.

//PGA_Start();