/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

//huding huding

#ifndef DEVICE_H
#define DEVICE_H
#include <project.h>

#endif

#ifndef WAITER
#define WAITER

void waiter( int seconds )
{   // Pretty crossplatform, both ALL POSIX compliant systems AND Windows
    int i,j;
    for (i = 0; i < seconds*1000; i++){
        for (j = 0; j < seconds*1000; j++){
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


#endif
/* [] END OF FILE */
