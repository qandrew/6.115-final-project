// Andrew Xia
// 6.115 Microcontrollers
// Final Project
// Apr 26 2016
// Tic Tac Toe AI for my game

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tic_tac_toe.h"

typedef int bool;
#define true 1
#define false 0


struct ai{
	int grid_eval[64];
	int board[74]; //list of all diagonals
};


struct tic_tac_ai{
	struct tic_tac_toe game;
	struct ai ai_1;	//the ai module for player 1
	struct ai ai_2; //the ai module for player 2
};

void tta_init(struct tic_tac_ai* ai, int size, int dimension, 
	bool player_1, bool player_2){
	// the player 1 and player 2 bools determine whether we want AI or not
	ttc_init(&ai->game,size,dimension); // init inside tic tac toe struct
};