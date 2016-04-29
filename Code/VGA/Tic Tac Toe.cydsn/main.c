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
    
    //CyGlobalIntEnable;
    //rx_int_StartEx(RX_INT);             // start RX interrupt (look for CY_ISR with RX_INT address)
                                        // for code that writes received bytes to LCD.
    
    //PGA_Start();
    uint8 Values;
    
    
        
    int i;
    for (;;){
        
    
        Values = Pin3_Read();
        LCD_ClearDisplay();
        LCD_PrintString("ASC: ");
        LCD_PutChar(Values); //print ascii value
        LCD_PrintString(" HEX: ");
        LCD_PrintNumber(Values); //print value I am getting
        waiter(10);
        
    }
    
    

    for(;;)
    {
    }
}

/* [] END OF FILE */