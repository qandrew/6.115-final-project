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

// files I made
#include <disp.h>
#include <tic_tac_all.h>
#include <8051_read.h>

//methods in main
void main_play_ttc(); //the two player one
void main_play_tta_ai(); //ai vs ai

void main()
{	    
    
    //main_play_ttc() ;
    main_play_tta_ai();
    
    for(;;){} //pause
}

void main_play_tta_ai(){
    LCD_Start();					    // initialize lcd
    LCD_ClearDisplay();
    UART_Start();                       // initialize UART
    UART_PutChar(0x81); // init connection; set to 16x12 image 
    
    struct disp_grid_81 disp; 
    disp_grid_init(&disp,0x3F); // init our display grid matrix to white  
    disp_grid_transmit(&disp);
    
    int x,y; uint8 Values; 
    
    struct tic_tac_ai tta;
    tta_init(&tta,4,3,true,false); //first bool for player 1, second bool for player 2
    disp_grid_init_ttc(&disp, tta.game.grid);
    disp_grid_draw_xia(&disp,26,16,0x30); // draw xia
    disp_grid_transmit(&disp);
    
    while (tta.game.game_not_won == 0){
        Values = read_from_8255(Values); //read and print
        if (Values >= 48 && Values <= 63){ //integer value
            y = Values - 48; // convert from ASCII to int
            x = y % 4; //get row value
            y = y / 4; // 
        }
        tta_step(&disp,&tta,x,y,Pin0_Read()); //increment a turn
        disp_grid_transmit(&disp);
//        LCD_ClearDisplay();
//        LCD_PrintString("TURN ");   
//        LCD_PrintNumber(tta.game.turn);
    }
    LCD_ClearDisplay();
    LCD_PrintString("GAME OVER!");   
    
}

void main_play_ttc(){
    LCD_Start();					    // initialize lcd
    LCD_ClearDisplay();
    UART_Start();                       // initialize UART
    UART_PutChar(0x81); // init connection; set to 16x12 image 
    
    struct disp_grid_81 disp; 
    disp_grid_init(&disp,0x3F); // init our display grid matrix to white  
    disp_grid_transmit(&disp);
    
    struct tic_tac_toe lolz;
 	ttc_init(&lolz,4,3);    
    disp_grid_init_ttc(&disp,lolz.grid); // init the board
    disp_grid_draw_xia(&disp,26,16,0x30); // draw xia
    disp_grid_transmit(&disp);
    
    int x,y; uint8 Values;
    
    while (lolz.game_not_won == 0){
        Values = read_from_8255(Values);
        if (Values >= 48 && Values <= 63){ //integer value
            y = Values - 48; // convert from ASCII to int
            x = y % 4; //get row value
            y = y / 4; // 
        }
        if (ttc_get_grid(&lolz,x,y,Pin0_Read()) == 0){ // has not been accessed
            ttc_step(&disp,&lolz,x,y,Pin0_Read()); // step & print
            disp_grid_transmit(&disp);
            LCD_PrintString("HU");
        }
        
    }
    LCD_ClearDisplay();
    LCD_Position(0,0); //move to bot row
    LCD_PrintString("GAME OVER!");    
    
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