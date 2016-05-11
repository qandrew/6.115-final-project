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

uint8 read_Values(uint8 Values){
    // this function reads the live value from 8255 output. 
    // connected via databus on port 3
    // and displays on the LCD
    // this function assumes that LCD_Start() has already been run;
    // And uint8 Values has been declared
    LCD_ClearDisplay();
    LCD_Position(1,0); //move to bot row
    LCD_PrintString("LAST:"); //first, we print last value
    LCD_PutChar(Values); //print ascii value
    LCD_PrintString(" HEX: ");
    LCD_PrintNumber(Values); //print value I am getting
    
    uint8 current;
    current = Pin3_Read(); //next, read a new value
    LCD_Position(0,0); //move back to top row
    LCD_PrintString("CURR:");
    LCD_PutChar(current); //print ascii value
    LCD_PrintString(" HEX: ");
    LCD_PrintNumber(current); //print value I am getting
    
    waiter(5);
    if (current == 255) return Values; // do not return new value
    else return current;
}

uint8 read_from_8255(uint8 Values){
    // this function reads the live value from 8255 output. 
    // connected via databus on port 3
    // and displays on the LCD
    // this function assumes that LCD_Start() has already been run;
    // And uint8 Values has been declared
    LCD_ClearDisplay();
    LCD_Position(1,0); //move to bot row
    LCD_PrintString("LAST:"); //first, we print last value
    LCD_PutChar(Values); //print ascii value
    LCD_PrintString(" HEX: ");
    LCD_PrintNumber(Values); //print value I am getting
    
    uint8 current;
    current = Pin3_Read(); //next, read a new value
    LCD_Position(0,0); //move back to top row
    LCD_PrintString("CURR:");
    LCD_PutChar(current); //print ascii value
    LCD_PrintString(" HEX: ");
    LCD_PrintNumber(current); //print value I am getting
    
    waiter(5);
    if (current == 255) return Values; // do not return new value
    else return current; // return current nonzero value
}