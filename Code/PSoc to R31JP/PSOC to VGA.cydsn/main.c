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

void wait( int seconds )
{   // Pretty crossplatform, both ALL POSIX compliant systems AND Windows
    int i,j;
    for (i = 0; i < seconds*1000; i++){
        for (j = 0; j < seconds*1000; j++){
        }
    }
}

void disp(uint8 colorA, uint8 colorB){
    int row,col;
    for (row = 0; row < 16; row++){
        for (col = 0; col < 6; col++){
            UART_PutChar(colorA); // red
            UART_PutChar(colorB); // green
        }
    }    
}

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
   
    
    int i;
    for (i = 0; i < 5; i++){
        UART_PutChar(0x80); // init connection; set to 16x12 image 
        disp(0x30,0x00); //red black
        wait(1);
        UART_PutChar(0x80); // init connection; set to 16x12 image 
        disp(0x30,0x0c); //red green
        wait(1);
    }
    
    LCD_PutChar(0x35); //print a 5
    
    

    for(;;)
    {}
}

/* [] END OF FILE */