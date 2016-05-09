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

#ifndef DEVICE_H
#define DEVICE_H
#include <project.h>

#endif



struct disp_grid_81{ //for 32x24 grid
    uint8 matrix[32][24];
    //uint8 damn
};
void disp_grid_init(struct disp_grid_81* disp, uint8 color);
void disp_grid_draw_square(struct disp_grid_81* disp, int x_start, int y_start, int x_width, int y_height, uint8 color);
void disp_grid_draw_xia(struct disp_grid_81* disp, int x_start, int y_start, uint8 color);
void disp_grid_draw_hu(struct disp_grid_81* disp);
void disp_grid_ttc_place(struct disp_grid_81* disp, int i, int value);
void disp_grid_init_ttc(struct disp_grid_81* disp, int grid[64]);
void disp_grid_transmit (struct disp_grid_81 * disp);
void waiter( int seconds );

void disp_grid_ttc_place_value(struct disp_grid_81* disp, int i, uint8 value);
uint8 disp_grid_ttc_getval(struct disp_grid_81* disp, int i);


/* [] END OF FILE */
