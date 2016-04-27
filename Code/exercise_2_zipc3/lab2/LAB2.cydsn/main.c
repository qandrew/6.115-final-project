/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * This file is necessary for your project to build.
 * Please do not delete it.
 *
 * ========================================
*/

#include <device.h>
#include <tic_tac_toe.c>

void main()
{
    tic_tac_toe tic = {1,3};	
	
	LCD_Char_1_Start();					// initialize lcd
	LCD_Char_1_ClearDisplay();
    LCD_Char_1_PrintString("HELLO");
    char c = tic.x;
	LCD_Char_1_PrintString(c);
    
}

/* [] END OF FILE */