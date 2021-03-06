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
void main_test_disp(); // just test the databus

void main_test_display();

void main_flashing_tta();
void main_flashing_tta_psoc();


void main()
{	    
    //main_play_ttc() ; // take out inverter and connection to 7430, run keypad with cap
    //main_play_tta_ai(); // take out inverter, run keypad with cap
    //main_test_disp();
    //main_flashing_tta();
    main_flashing_tta_psoc();
    //main_test_display();

        
    //LCD_Start();					    // initialize lcd
    //LCD_ClearDisplay();
    //uint8 Values;
    for(;;){
        
        //Values = read_from_8255(Values); //read and print
    } //pause
}

void main_test_display(){
    UART_Start();                       // initialize UART
    UART_PutChar(0x81); // init connection; set to 16x12 image 
    
    struct disp_grid_81 disp; 
    disp_grid_init(&disp,0x3F); // init our display grid matrix to white  
    disp_grid_transmit(&disp);
    
    struct tic_tac_ai tta;
    tta_init(&tta,4,3,false,true); //first bool for player 1, second bool for player 2. true means is AI
    disp_grid_init_ttc(&disp, tta.game.grid);
    
    disp_grid_draw_tic(&disp,24,1,0x27); // draw tic
    disp_grid_draw_win(&disp,27,9,1); // draw tic
    disp_grid_draw_xia(&disp,26,16,0x30); // draw xia
    disp_grid_transmit(&disp);
}

void main_flashing_tta(){
    // this is the function compatible with the cap sensor input. does not use 8051; connect directly
    LCD_Start();					    // initialize lcd
    LCD_ClearDisplay();
    UART_Start();                       // initialize UART
    UART_PutChar(0x81); // init connection; set to 16x12 image 
    
    struct disp_grid_81 disp; 
    disp_grid_init(&disp,0x3F); // init our display grid matrix to white  
    disp_grid_transmit(&disp);
    
    struct tic_tac_ai tta;
    tta_init(&tta,4,3,false,true); //first bool for player 1, second bool for player 2. true means is AI
    disp_grid_init_ttc(&disp, tta.game.grid);
    disp_grid_draw_xia(&disp,26,16,0x30); // draw xia
    disp_grid_transmit(&disp);
    
    int x,y,z, count; uint8 Values; uint8 Values_prev;
    Values_prev = Pin0_Read();
    x = 0; y = 0; z = 0; //test value
    count = 0;
    
    uint8 red_flash; //the temporary location flasher
    uint8 other_val;
    other_val = disp_grid_ttc_getval(&disp,z*16 + y*4 + x); // get the nonred val
    red_flash = 0x30; //map to color red
    
    tta_step(&disp,&tta,x,y,z); //AI Increment also 
    
    while (tta.game.game_not_won == 0){
//        Values = read_from_8255(Values); //read and print
        
        LCD_ClearDisplay();
        
        LCD_Position(0,0); //move back to top row
        Values = Pin0_Read(); //next, read a new value
        LCD_PrintString("P0: ");
        LCD_PrintNumber(Values); //print value I am getting
        
        if (Values != Values_prev){
            Values_prev = Values; //we don't want nonconsect
            if (Values != 0){
                if (Values == 32){
                    tta_step(&disp,&tta,x,y,z); //increment a turn
                    tta_step(&disp,&tta,x,y,z); //AI Increment also 
                    other_val = disp_grid_ttc_getval(&disp,z*16 + y*4 + x); // get the nonred val
                }
                else{
                    disp_grid_ttc_place_value(&disp,z*16 + y*4 + x,other_val);
                    if (Values == 16 && y != 0){ // up
                    y--;
                    }
                    else if (Values == 8 && y != 3){ // down
                        y++;
                    }
                    else if (Values == 4 && x != 0){ // left
                        x--;
                    }
                    else if (Values == 2 && x != 3){ // right
                        x++;
                    }
                    else if (Values == 1){ // level shift
                        z++;
                        z = z % 4;
                    }
                    other_val = disp_grid_ttc_getval(&disp,z*16 + y*4 + x); // get the nonred val
                }
            }
        }
        
        if (count == 0){ //decide print
            count = 1;
            disp_grid_ttc_place_value(&disp,z*16 + y*4 + x,red_flash);
        }
        else{
            count = 0;
            disp_grid_ttc_place_value(&disp,z*16 + y*4 + x,other_val);
        }
        disp_grid_transmit(&disp);
    }
    LCD_ClearDisplay();
    LCD_PrintString("GAME OVER!");   
    
}


void main_flashing_tta_psoc(){
    // this is the function compatible with the cap sensor input. with 8051 interrupts
    LCD_Start();					    // initialize lcd
    LCD_ClearDisplay();
    UART_Start();                       // initialize UART
    UART_PutChar(0x81); // init connection; set to 16x12 image 
    
    struct disp_grid_81 disp; 
    disp_grid_init(&disp,0x3F); // init our display grid matrix to white  
    disp_grid_transmit(&disp);
    
    struct tic_tac_ai tta;
    tta_init(&tta,4,3,false,true); //first bool for player 1, second bool for player 2. true means is AI
    disp_grid_init_ttc(&disp, tta.game.grid);
    disp_grid_draw_tic(&disp,24,1,0x27); // draw tic
    disp_grid_draw_xia(&disp,26,16,0x30); // draw xia
    disp_grid_transmit(&disp);
    
    int x,y,z, count; uint8 Values; uint8 Values_prev;
    uint8 current;
    Values_prev = 0;
    x = 0; y = 0; z = 0; //test value
    count = 0;
    
    uint8 red_flash; //the temporary location flasher
    uint8 other_val;
    other_val = disp_grid_ttc_getval(&disp,z*16 + y*4 + x); // get the nonred val
    red_flash = 0x30; //map to color red
    
    
    while (tta.game.game_not_won == 0){
        LCD_ClearDisplay();
        LCD_Position(1,0); //move to bot row
        LCD_PrintString("LAST:"); //first, we print last value
        LCD_PutChar(Values_prev); //print ascii value
        LCD_PrintString(" HEX: ");
        LCD_PrintNumber(Values_prev); //print value I am getting
        
        current = Pin3_Read(); //next, read a new value
        LCD_Position(0,0); //move back to top row
        LCD_PrintString("CURR:");
        LCD_PutChar(current); //print ascii value
        LCD_PrintString(" HEX: ");
        LCD_PrintNumber(current); //print value I am getting
        waiter(3);
        
        if (current != 255) {
            Values = current; // update values as last non
            Values_prev = Values;
        }
        
        if (Values != 0){
            if (Values == 54){
                if (tta.game.grid[z*16 + y*4 + x] == 0){ // make sure we can place there
                    tta_step(&disp,&tta,x,y,z); //increment a turn
                    disp_grid_transmit(&disp);
                    tta_step(&disp,&tta,x,y,z); //AI Increment also 
                    other_val = disp_grid_ttc_getval(&disp,z*16 + y*4 + x); // get the nonred val
                }
            }
            else{
                disp_grid_ttc_place_value(&disp,z*16 + y*4 + x,other_val);
                if (Values == 53 && y != 0){ // up
                y--;
                }
                else if (Values == 52 && y != 3){ // down
                    y++;
                }
                else if (Values == 51 && x != 0){ // left
                    x--;
                }
                else if (Values == 50 && x != 3){ // right
                    x++;
                }
                else if (Values == 49){ // level shift
                    z++;
                    z = z % 4;
                }
                other_val = disp_grid_ttc_getval(&disp,z*16 + y*4 + x); // get the nonred val
            }
            Values = 0; // reset values;
            count = 0;
        }
        
        if (count == 0){ //decide print
            count = 1;
            disp_grid_ttc_place_value(&disp,z*16 + y*4 + x,red_flash);
            disp_grid_transmit(&disp);
        }
//        else{
//            count = 0;
//            disp_grid_ttc_place_value(&disp,z*16 + y*4 + x,other_val);
//            disp_grid_transmit(&disp);
//        }
        
    }
    LCD_ClearDisplay();
    LCD_PrintString("GAME OVER!");  
    disp_grid_draw_win(&disp,27,9,tta.game.player); // draw tic
    disp_grid_transmit(&disp);
    
}

void main_test_disp(){
    LCD_Start();					    // initialize lcd
    uint8 current;
    for (;;){
        LCD_ClearDisplay();
        
        LCD_Position(0,0); //move back to top row
        current = Pin0_Read(); //next, read a new value
        LCD_PrintString("P0: ");
        LCD_PrintNumber(current); //print value I am getting
        
        LCD_Position(1,0); //move to bot row
        current = Pin3_Read(); //next, read a new value
        LCD_PrintString("P3: ");
        LCD_PutChar(current); //print ascii value
        LCD_PrintString(" HEX: ");
        LCD_PrintNumber(current); //print value I am getting
        
        waiter(4);
    }
}

void main_play_tta_ai(){
    LCD_Start();					    // initialize lcd
    LCD_ClearDisplay();
    UART_Start();                       // initialize UART
    UART_PutChar(0x81); // init connection; set to 16x12 image 
    
    struct disp_grid_81 disp; 
    disp_grid_init(&disp,0x3F); // init our display grid matrix to white  
    disp_grid_transmit(&disp);
    
    int x,y,z; uint8 Values; 
    
    struct tic_tac_ai tta;
    tta_init(&tta,4,3,true,false); //first bool for player 1, second bool for player 2
    disp_grid_init_ttc(&disp, tta.game.grid);
    disp_grid_draw_xia(&disp,26,16,0x30); // draw xia
    disp_grid_transmit(&disp);
    
    while (tta.game.game_not_won == 0){
        Values = read_from_8255(Values); //read and print
        if (Values >= 0 && Values <= 63){ //integer value
            z = Values / 16;
            x = Values % 4; //get row value
            y = Values / 4 - z*4; // 
//            LCD_ClearDisplay();
//            LCD_PrintNumber(Values);
//            LCD_PrintString(" x");
//            LCD_PrintNumber(x);
//            LCD_PrintString(" y");
//            LCD_PrintNumber(y);
//            LCD_PrintString(" z");
//            LCD_PrintNumber(z);
        }
        tta_step(&disp,&tta,x,y,z); //increment a turn
        disp_grid_transmit(&disp);
    }
    LCD_ClearDisplay();
    LCD_PrintString("GAME OVER!");   
    disp_grid_draw_win(&disp,27,9,tta.game.player); // draw tic
    disp_grid_transmit(&disp);
    
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
    
    int x,y,z; int Values;
    
    while (lolz.game_not_won == 0){
        //Values = read_from_8255(Values);
        Values = Pin3_Read();
        if (Values >= 0 && Values <= 63){ //integer value
            z = Values / 16;
            x = Values % 4; //get row value
            y = Values / 4 - z*4; // 
            LCD_ClearDisplay();
            LCD_PrintNumber(Values);
            LCD_PrintString(" x");
            LCD_PrintNumber(x);
            LCD_PrintString(" y");
            LCD_PrintNumber(y);
            LCD_PrintString(" z");
            LCD_PrintNumber(z);
        }
        if (ttc_get_grid(&lolz,x,y,z) == 0){ // has not been accessed
            ttc_step(&disp,&lolz,x,y,z); // step & print
            disp_grid_transmit(&disp);
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

//PGA_Start()