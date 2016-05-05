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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef int bool;
#define true 1
#define false 0

#ifndef DEVICE_H
#define DEVICE_H
#include <project.h>

#endif

int max_array(int array[], size_t size); //helper function

//////////////// TIC TAC TOE MODULE /////////////////

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

void ttc_init(struct tic_tac_toe* t, int size, int dimension);
int ttc_set_grid(struct tic_tac_toe* t, int x, int y, int z, int value);
int ttc_get_grid(struct tic_tac_toe* t, int x, int y, int z);
int ttc_check_valid(struct tic_tac_toe* t, int x, int y, int z);
void ttc_change_player(struct tic_tac_toe* t);
int * ttc_take_input();
void ttc_print_grid(struct tic_tac_toe* t);
int ttc_check_win(struct tic_tac_toe* t);
int ttc_step(struct disp_grid_81* disp, struct tic_tac_toe* t,int x, int y, int z);
int ttc_play_game(struct tic_tac_toe* t);
void ttc_free(struct tic_tac_toe* t);


///////////////////////// AI MODULE ////////////////

struct ai{ //structure for the AI bot
	int player_id;
	int grid_eval[64]; //probably should malloc this shit
	int diags[76]; //list of all diagonals
};

void ai_reset(struct ai* ai);
void ai_init(struct ai* ai, int player_id, int size, int dimension);
int ai_evaluate_board(struct tic_tac_toe* t, struct ai* ai);
int ai_define_score(struct ai* ai,int connected,int empty_places[4]);
void ai_print_grid_eval(struct ai* ai);
void ai_play_best_move(struct tic_tac_toe* t, struct ai* ai, struct disp_grid_81* disp);


///////////////////////// TIC TAC AI SUPERMODULE ////////////////


struct tic_tac_ai{ //structure for the overall object
	int is_ai[2];
	struct ai ai_1;	//the ai module for player 1, with id 1
	struct ai ai_2; //the ai module for player 2, with id -1
	struct tic_tac_toe game;
};

void tta_init(struct tic_tac_ai* ai, int size, int dimension, bool player_1, bool player_2);
void tta_ai_algorithm(struct disp_grid_81* disp,struct tic_tac_ai* tta, int player);
void tta_step(struct disp_grid_81* disp,struct tic_tac_ai* tta, int x, int y, int z);

/* [] END OF FILE */
