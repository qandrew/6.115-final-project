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

//CY_ISR(RX_INT)
//{
//    LCD_PutChar(UART_ReadRxData());     // RX ISR
//}

#include <unistd.h>

struct disp_grid_81{ //for 32x24 grid
    uint8 matrix[32][24]; 
};

struct tic_tac_toe{
	int size;
	int dimension;
	// grid = {'A','B','A'}; // make this an array of length 64
	int player; // 1 is player A, -1 is player B
	int turn;
	int game_not_won;
	// int grid_eval[]; //this keeps track of scores of all diagonals
	int grid[64]; // a usually size 64 grid containing our board
	// if don't specify grid size, could get memory overlap
};


void main()
{	
	LCD_Start();					    // initialize lcd
	LCD_ClearDisplay();
    
    //CyGlobalIntEnable;
    //rx_int_StartEx(RX_INT);             // start RX interrupt (look for CY_ISR with RX_INT address)
                                        // for code that writes received bytes to LCD.
    
    UART_Start();                       // initialize UART
    UART_PutChar(0x81); // init connection; set to 16x12 image 
    struct disp_grid_81 disp; 
    
    struct tic_tac_toe lolz;
 	ttc_init(&lolz,4,3);
    
    //int i;
    //for(i = 0; i < 10; i++){
        disp_grid_init(&disp,0x3F); // init our display grid matrix to white  
        disp_grid_transmit(&disp);
        
        disp_grid_draw_xia(&disp,26,16,0x30); // draw xia
        disp_grid_transmit(&disp);
        
        disp_grid_init_ttc(&disp,lolz.grid); // init the board
        disp_grid_transmit(&disp);
        
        ttc_step(&disp,&lolz,2,2,2); // step & print
        disp_grid_transmit(&disp);
        
        ttc_step(&disp,&lolz,2,2,3); // step & print
        disp_grid_transmit(&disp);
        
    //}
    
    LCD_PrintString(" HUDING ");
    //LCD_PrintNumber(35);
    
    

    for(;;)
    {}
}

/* [] END OF FILE */