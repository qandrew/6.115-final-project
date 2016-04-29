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
    UART_PutChar(0x81); // init connection; set to 16x12 image 
    for (i = 0; i < 5; i++){
        disper(0x30,0x00); //red black
        waiter(1);
        disper(0x30,0x0c); //red green
        waiter(1);
    }
    
    LCD_PutChar(0x35); //print a 5
    
    

    for(;;)
    {}
}

/* [] END OF FILE */