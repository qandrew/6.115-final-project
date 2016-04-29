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


void main()
{	
	LCD_Start();					    // initialize lcd
	LCD_ClearDisplay();
    
    //CyGlobalIntEnable;
    //rx_int_StartEx(RX_INT);             // start RX interrupt (look for CY_ISR with RX_INT address)
                                        // for code that writes received bytes to LCD.
    
    UART_Start();                       // initialize UART
    //UART_ClearRxBuffer();
    
    LCD_PutChar(0x35); //print a 5
   
    
    UART_PutChar(0x81); // init connection; set to 16x12 image 
    
    struct disp_grid_81 disp;
    
    disp_grid_init(&disp,0x3F);
    disp_grid_draw_square(&disp,5,5,2,10,0x00);
    disp_grid_draw_square(&disp,10,5,2,10,0x00);
    disp_grid_draw_square(&disp,7,10,3,2,0x00);
    
    disp_grid_draw_square(&disp,14,5,2,10,0x00);
    disp_grid_draw_square(&disp,19,5,2,10,0x00);
    disp_grid_draw_square(&disp,16,13,3,2,0x00);
    
    //disp_grid_draw_square(&disp,23,5,6,2,0x00);
    //disp_grid_draw_square(&disp,25,7,2,8,0x00);
    
    disp_grid_transmit(&disp);
    

    
    LCD_PrintString(" HUDING "); //print a 5
    
    LCD_PrintNumber(35); //print a 5
    
    

    for(;;)
    {}
}

/* [] END OF FILE */