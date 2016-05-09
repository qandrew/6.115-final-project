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

void ttc_init(struct tic_tac_toe* t, int size, int dimension){
	t->size = size;
	t->dimension = dimension;
	if (dimension == 3){
		int i;
		int num = size*size*size;
		for (i = 0; i < num;i++){
			t->grid[i] = 0;
		}
	}
	t->player = 1; // default to player 1
	t->game_not_won = 0;
	t->turn = 1;
};

int ttc_set_grid(struct tic_tac_toe* t, int x, int y, int z, int value){
	int loc = z*16 + y*4 + x;
	t->grid[loc] = value;
	// printf("\nSet Value %i %i %i %i",x,y,z,value); 
	return 1; // return 1 to show completed properly
}

int ttc_get_grid(struct tic_tac_toe* t, int x, int y, int z){
	int loc = z*16 + y*4 + x;
	int ret = t->grid[loc];
	// printf("\nGet Value %i %i %i %i",x,y,z,ret); 
	return ret;
}

int ttc_check_valid(struct tic_tac_toe* t, int x, int y, int z){
	int loc = z*16 + y*4 + x;
	if (x < 0 || y < 0 || z < 0){
		printf("\nOut of bounds %i %i %i",x,y,z); 
		return 0;
	}
	else if (x >= t->size || y >= t->size || z >= t->size){
		printf("\nOut of bounds %i %i %i",x,y,z); 
		return 0;
	}
	else if (t->grid[loc] != 0){ // already occupied position
		printf("\nPosition already occupied %i %i %i",x,y,z); 
		return 0;
	}
	else{
		return 1; //free position
	}

}

void ttc_change_player(struct tic_tac_toe* t){
	if (t->player == 1){
		t->player = -1;
	}
	else if (t-> player == -1){
		t->player = 1;
	}
	t->turn++;
}

int * ttc_take_input(){ 
	// take a user input, return x y z array pointer
	printf("\nEnter a position: ");
	char str2[3];
	scanf("%s", str2);
	static int ret[3];
	ret[0] = str2[0]-48; //without atoi, we get ascii value
	ret[1] = str2[1]-48; //or can do ascii conversion
	ret[2] = str2[2]-48; // int temp = atoi(str2);
	// free(str2);
	printf("Entered %i %i %i",ret[0],ret[1],ret[2]);
	return ret;
}

void ttc_print_grid(struct tic_tac_toe* t){
	// this function prints the board
	int i;
	for (i = 0; i < 64; i++){
		if (i % 4 == 0){
			printf("\n");
		}
		if (i % 16 == 0){
			printf("\n");
		}
		printf("%i ",t->grid[i]);
		if (t->grid[i] != -1){
			printf(" ");
		}
	}
	printf("\nAfter turn %i player %i\n",t->turn,t->player);
}


int ttc_check_win(struct tic_tac_toe* t){
	printf("\nPlayer %i",t->player);
	int x,y,z,zp;
	int connected;
	for (z = 0; z < t->size; z++){
		for (y = 0; y < t->size; y++){ // flat
			connected = 0;
			for (x = 0; x < t->size;x++){
				connected += ttc_get_grid(t,x,y,z);
			}
			if (connected == t->player*t->size){
				t->game_not_won = t->player; //when win, set to player id
				return 1; //there is a win
			}
		}
		for (x = 0; x < t->size; x++){ //horiz
			connected = 0;
			for (y = 0; y < t->size;y++){
				connected += ttc_get_grid(t,x,y,z);
			}
			if (connected == t->player*t->size){
				t->game_not_won = t->player; //when win, set to player id
				return 1; //there is a win
			}
		}
		for (x = 0; x < t->size; x++){ //vert, where z is y coord
			connected = 0;
			for (zp = 0; zp < t->size;zp++){
				connected += ttc_get_grid(t,x,z,zp);
			}
			if (connected == t->player*t->size){
				t->game_not_won = t->player; //when win, set to player id
				return 1; //there is a win
			}
		}
		connected = 0; //planar
		for (zp = 0; zp < t->size;zp++){ //double iterator
			connected += ttc_get_grid(t,z,zp,zp);
		}
		if (connected == t->player*t->size){
			t->game_not_won = t->player; //when win, set to player id
			return 1; //there is a win
		}
		connected = 0; //planar
		for (zp = 0; zp < t->size;zp++){ //double iterator
			connected += ttc_get_grid(t,z,3-zp,zp);
		}
		if (connected == t->player*t->size){
			t->game_not_won = t->player; //when win, set to player id
			return 1; //there is a win
		}
		connected = 0; //frontal
		for (zp = 0; zp < t->size;zp++){ //double iterator
			connected += ttc_get_grid(t,zp,z,zp);
		}
		if (connected == t->player*t->size){
			t->game_not_won = t->player; //when win, set to player id
			return 1; //there is a win
		}
		connected = 0; //frontal
		for (zp = 0; zp < t->size;zp++){ //double iterator
			connected += ttc_get_grid(t,3-z,z,zp);
		}
		if (connected == t->player*t->size){
			t->game_not_won = t->player; //when win, set to player id
			return 1; //there is a win
		}
		connected = 0; //sidal
		for (zp = 0; zp < t->size;zp++){ //double iterator
			connected += ttc_get_grid(t,zp,zp,z);
		}
		if (connected == t->player*t->size){
			t->game_not_won = t->player; //when win, set to player id
			return 1; //there is a win
		}
		connected = 0; //sidal
		for (zp = 0; zp < t->size;zp++){ //double iterator
			connected += ttc_get_grid(t,zp,3-zp,z);
		}
		if (connected == t->player*t->size){
			t->game_not_won = t->player; //when win, set to player id
			return 1; //there is a win
		}
	}
	connected = 0; //superdiag 1
	for (zp = 0; zp < t->size;zp++){ //triple iterator
		connected += ttc_get_grid(t,zp,zp,zp);
	}
	if (connected == t->player*t->size){
		t->game_not_won = t->player; //when win, set to player id
		return 1; //there is a win
	}
	connected = 0; //superdiag 2
	for (zp = 0; zp < t->size;zp++){ //triple iterator
		connected += ttc_get_grid(t,zp,3-zp,zp);
	}
	if (connected == t->player*t->size){
		t->game_not_won = t->player; //when win, set to player id
		return 1; //there is a win
	}
	connected = 0; //superdiag 3
	for (zp = 0; zp < t->size;zp++){ //triple iterator
		connected += ttc_get_grid(t,zp,zp,3-zp);
	}
	if (connected == t->player*t->size){
		t->game_not_won = t->player; //when win, set to player id
		return 1; //there is a win
	}
	connected = 0; //superdiag 4
	for (zp = 0; zp < t->size;zp++){ //triple iterator
		connected += ttc_get_grid(t,zp,3-zp,3-zp);
	}
	if (connected == t->player*t->size){
		t->game_not_won = t->player; //when win, set to player id
		return 1; //there is a win
	}
	return 0; //no win
}


int ttc_step(struct disp_grid_81* disp, struct tic_tac_toe* t,int x, int y, int z){
	// generic take input to allow for both terminal and psoc
	if (ttc_check_valid(t,x,y,z) == 1){
		ttc_set_grid(t,x,y,z,t->player);
		// ttc_get_grid(t,x,y,z);
		// printf("\nGot here"); 
		ttc_check_win(t);
		ttc_change_player(t);
		//ttc_print_grid(t); // on terminal
        disp_grid_ttc_place(disp,z*16+y*4+x, ttc_get_grid(t,x,y,z)); // for PSoC
		return 1;
	}
	else{
		return 0; // did not work properly
	}
}

int ttc_play_game(struct tic_tac_toe* t){
	while (t->game_not_won == 0){
		//ttc_play(t);
        // IMPLEMENT FOR PSOC
	}
	printf("Player %i has won", t->game_not_won);
	return 0;
}

void ttc_free(struct tic_tac_toe* t){
	free(t->grid);
	free(t);
}


///////////////////////// AI CODE ////////////////

int max_array(int array[], size_t size){
	// returns maximum index of array
	// if there are multiple, then randomly select and return max index
	size_t i;
	int max = 0;
	int *all_index = malloc(size*sizeof(int));
	int num_index = 1;

	for (i = 0; i < size; i++){
		if (max < array[i]){
			max = array[i];

			memset(all_index,0,num_index); //clear array
			all_index[0] = i;
			num_index=1;

		}
		else if (max == array[i]){
			all_index[num_index] = i;
			num_index++;
		}
	}
	if (num_index == 1){
		num_index = all_index[0];
	}
	else{
		srand(PinNoise_Read()+PinNoise_Read()*num_index); // set a random seed
		max = rand() % num_index; // choose a random index
		num_index = all_index[max];
	}
	free(all_index); // free
	return num_index;
};


struct ai{ //structure for the AI bot
	int player_id;
	int grid_eval[64]; //probably should malloc this shit
	int diags[76]; //list of all diagonals
};

struct tic_tac_ai{ //structure for the overall object
	int is_ai[2];
	struct ai ai_1;	//the ai module for player 1, with id 1
	struct ai ai_2; //the ai module for player 2, with id -1
	struct tic_tac_toe game;
};

void ai_reset(struct ai* ai){
	memset(ai->grid_eval,0,sizeof ai->grid_eval); //clear array
	memset(ai->diags,0,sizeof ai->diags); //clear array	
}

void ai_init(struct ai* ai, int player_id, int size, int dimension){
	ai->player_id = player_id;
	ai_reset(ai);
}

void tta_init(struct tic_tac_ai* ai, int size, int dimension, 
	bool player_1, bool player_2){
	// the player 1 and player 2 bools determine whether we want AI or not
	ttc_init(&ai->game,size,dimension); // init inside tic tac toe struct
	if (player_1 == true){
		//printf("\nInit player %i as AI", 1);
		ai_init(&ai->ai_1,1,size,dimension);
		ai->is_ai[0] = 1;
	}
	else {
		//printf("\nInit player %i not as AI", 1);
		ai->is_ai[0] = 0;
	}
	if (player_2 == true){
		//printf("\nInit player %i as AI", -1);
		ai_init(&ai->ai_2,-1,size,dimension);
		ai->is_ai[1] = 1;
	}
	else {
		//printf("\nInit player %i not as AI", -1);
		ai->is_ai[1] = 0;
	}
}

int ai_evaluate_board(struct tic_tac_toe* t, struct ai* ai){
	// this method lets ai evaluate the board
	ai_reset(ai);
	int x,y,z,zp;
	int connected;
	int empty_places[4]; //keep track of all empty places
	int num_filled;
	// int diag_loc;
	for (z = 0; z < t->size; z++){
		for (y = 0; y < t->size; y++){ // flat
			connected = 0;
			num_filled = 0;
			memset(empty_places,0,sizeof empty_places); //clear array
			for (x = 0; x < t->size;x++){
				connected += ai->player_id*ttc_get_grid(t,x,y,z);
				if (ttc_get_grid(t,x,y,z) == 0){ //empty spot
					empty_places[num_filled] = z*16 + y*4 + x; // store loc
					num_filled++; //increment
				}
			}
			// printf("\n Flats at %i %i %i with score %i filled %i",x,y,z,connected,num_filled);
			if (connected == t->size){
				t->game_not_won = t->player; //when win, set to player id
				return 1; //there is a win
			}
			if (abs(connected) == 4 - num_filled){
				// ABA0 connected = 1, but num_filled = 1, so bad
				// A000 connected = 1, but num_filled = 3, so good
				ai_define_score(ai,connected,empty_places);
			}
		}
		for (x = 0; x < t->size; x++){ // horiz
			connected = 0;
			num_filled = 0;
			memset(empty_places,0,sizeof empty_places); //clear array
			for (y = 0; y < t->size;y++){
				connected += ai->player_id*ttc_get_grid(t,x,y,z);
				if (ttc_get_grid(t,x,y,z) == 0){  //empty spot
					empty_places[num_filled] = z*16 + y*4 + x; // store loc
					num_filled++; //increment
				}
			}
			if (connected == t->size){
				t->game_not_won = t->player; //when win, set to player id
				return 1; //there is a win
			}
			if (abs(connected) == 4 - num_filled)
				ai_define_score(ai,connected,empty_places);
		}
		for (x = 0; x < t->size; x++){ // vert, where z is y coord, zp is z coord
			connected = 0;
			num_filled = 0;
			memset(empty_places,0,sizeof empty_places); //clear array
			for (zp = 0; zp < t->size;zp++){
				connected += ai->player_id*ttc_get_grid(t,x,z,zp);
				if (ttc_get_grid(t,x,z,zp) == 0){  //empty spot
					empty_places[num_filled] = zp*16 + z*4 + x; // store loc
					num_filled++; //increment
				}
			}
			if (connected == t->size){
				t->game_not_won = t->player; //when win, set to player id
				return 1; //there is a win
			}
			if (abs(connected) == 4 - num_filled)
				ai_define_score(ai,connected,empty_places);
		}

		// planar
		connected = 0;
		num_filled = 0;
		memset(empty_places,0,sizeof empty_places); //clear array
		for (zp = 0; zp < t->size;zp++){
			connected += ai->player_id*ttc_get_grid(t,zp,zp,z);
			if (ttc_get_grid(t,zp,zp,z) == 0){  //empty spot
				empty_places[num_filled] = z*16 + zp*4 + zp; // store loc
				num_filled++; //increment
			}
		}
		if (connected == t->size){
			t->game_not_won = t->player; //when win, set to player id
			return 1; //there is a win
		}
		if (abs(connected) == 4 - num_filled)
			ai_define_score(ai,connected,empty_places);
		// planar
		connected = 0;
		num_filled = 0;
		memset(empty_places,0,sizeof empty_places); //clear array
		for (zp = 0; zp < t->size;zp++){
			connected += ai->player_id*ttc_get_grid(t,zp,3-zp,z);
			if (ttc_get_grid(t,zp,3-zp,z) == 0){  //empty spot
				empty_places[num_filled] = z*16 + (3-zp)*4 + zp; // store loc
				num_filled++; //increment
			}
		}
		if (connected == t->size){
			t->game_not_won = t->player; //when win, set to player id
			return 1; //there is a win
		}
		if (abs(connected) == 4 - num_filled)
			ai_define_score(ai,connected,empty_places);

		// frontal
		connected = 0;
		num_filled = 0;
		memset(empty_places,0,sizeof empty_places); //clear array
		for (zp = 0; zp < t->size;zp++){
			connected += ai->player_id*ttc_get_grid(t,z,zp,zp);
			if (ttc_get_grid(t,z,zp,zp) == 0){  //empty spot
				empty_places[num_filled] = z + zp*4 + zp*16; // store loc
				num_filled++; //increment
			}
		}
		if (connected == t->size){
			t->game_not_won = t->player; //when win, set to player id
			return 1; //there is a win
		}
		if (abs(connected) == 4 - num_filled)
			ai_define_score(ai,connected,empty_places);
		// frontal
		connected = 0;
		num_filled = 0;
		memset(empty_places,0,sizeof empty_places); //clear array
		for (zp = 0; zp < t->size;zp++){
			connected += ai->player_id*ttc_get_grid(t,z,3-zp,zp);
			if (ttc_get_grid(t,z,3-zp,zp) == 0){  //empty spot
				empty_places[num_filled] = z + (3-zp)*4 + zp*16; // store loc
				num_filled++; //increment
			}
		}
		if (connected == t->size){
			t->game_not_won = t->player; //when win, set to player id
			return 1; //there is a win
		}
		if (abs(connected) == 4 - num_filled)
			ai_define_score(ai,connected,empty_places);

		// sidal
		connected = 0;
		num_filled = 0;
		memset(empty_places,0,sizeof empty_places); //clear array
		for (zp = 0; zp < t->size;zp++){
			connected += ai->player_id*ttc_get_grid(t,zp,z,zp);
			if (ttc_get_grid(t,zp,z,zp) == 0){  //empty spot
				empty_places[num_filled] = zp + z*4 + zp*16; // store loc
				num_filled++; //increment
			}
		}
		if (connected == t->size){
			t->game_not_won = t->player; //when win, set to player id
			return 1; //there is a win
		}
		if (abs(connected) == 4 - num_filled)
			ai_define_score(ai,connected,empty_places);
		// sidal
		connected = 0;
		num_filled = 0;
		memset(empty_places,0,sizeof empty_places); //clear array
		for (zp = 0; zp < t->size;zp++){
			connected += ai->player_id*ttc_get_grid(t,3-zp,z,zp);
			if (ttc_get_grid(t,3-zp,z,zp) == 0){  //empty spot
				empty_places[num_filled] = 3-zp + z*4 + zp*16; // store loc
				num_filled++; //increment
			}
		}
		if (connected == t->size){
			t->game_not_won = t->player; //when win, set to player id
			return 1; //there is a win
		}
		if (abs(connected) == 4 - num_filled)
			ai_define_score(ai,connected,empty_places);
	}
	// superdiags
	connected = 0;
	num_filled = 0;
	memset(empty_places,0,sizeof empty_places); //clear array
	for (zp = 0; zp < t->size;zp++){
		connected += ai->player_id*ttc_get_grid(t,zp,zp,zp);
		if (ttc_get_grid(t,zp,zp,zp) == 0){  //empty spot
			empty_places[num_filled] = zp + zp*4 + zp*16; // store loc
			num_filled++; //increment
		}
	}
	if (connected == t->size){
		t->game_not_won = t->player; //when win, set to player id
		return 1; //there is a win
	}
	if (abs(connected) == 4 - num_filled)
		ai_define_score(ai,connected,empty_places);

	connected = 0;
	num_filled = 0;
	memset(empty_places,0,sizeof empty_places); //clear array
	for (zp = 0; zp < t->size;zp++){
		connected += ai->player_id*ttc_get_grid(t,3-zp,zp,zp);
		if (ttc_get_grid(t,3-zp,zp,zp) == 0){  //empty spot
			empty_places[num_filled] = 3-zp + zp*4 + zp*16; // store loc
			num_filled++; //increment
		}
	}
	if (connected == t->size){
		t->game_not_won = t->player; //when win, set to player id
		return 1; //there is a win
	}
	if (abs(connected) == 4 - num_filled)
		ai_define_score(ai,connected,empty_places);

	connected = 0;
	num_filled = 0;
	memset(empty_places,0,sizeof empty_places); //clear array
	for (zp = 0; zp < t->size;zp++){
		connected += ai->player_id*ttc_get_grid(t,3-zp,3-zp,zp);
		if (ttc_get_grid(t,3-zp,3-zp,zp) == 0){  //empty spot
			empty_places[num_filled] = 3-zp + (3-zp)*4 + zp*16; // store loc
			num_filled++; //increment
		}
	}
	if (connected == t->size){
		t->game_not_won = t->player; //when win, set to player id
		return 1; //there is a win
	}
	if (abs(connected) == 4 - num_filled)
		ai_define_score(ai,connected,empty_places);

	connected = 0;
	num_filled = 0;
	memset(empty_places,0,sizeof empty_places); //clear array
	for (zp = 0; zp < t->size;zp++){
		connected += ai->player_id*ttc_get_grid(t,zp,3-zp,zp);
		if (ttc_get_grid(t,zp,3-zp,zp) == 0){  //empty spot
			empty_places[num_filled] = zp + (3-zp)*4 + zp*16; // store loc
			num_filled++; //increment
		}
	}
	if (connected == t->size){
		t->game_not_won = t->player; //when win, set to player id
		return 1; //there is a win
	}
	if (abs(connected) == 4 - num_filled)
		ai_define_score(ai,connected,empty_places);

	return 0;
}

int ai_define_score(struct ai* ai,int connected,int empty_places[4]){
	//this method defines the score of the AI, place at opt value
	if (connected == 3){ //connect our 3 in a row
		ai->grid_eval[empty_places[0]] += 100000; // a very high value
	}
	else if (connected == -3){ //block opponent's 3 in a row
		ai->grid_eval[empty_places[0]] += 5000; // a very high value
	}
	else if (abs(connected) == 2){ //block or connect 2 in a row
		ai->grid_eval[empty_places[0]] += 200;
		ai->grid_eval[empty_places[1]] += 200;
	}
	else if (connected == 1){ //connect a 1 in a row
		ai->grid_eval[empty_places[0]] += 50;
		ai->grid_eval[empty_places[1]] += 50;
		ai->grid_eval[empty_places[2]] += 50;
	}
	else if (connected == 0){ //start a 1 in a row
		ai->grid_eval[empty_places[0]] += 30;
		ai->grid_eval[empty_places[1]] += 30;
		ai->grid_eval[empty_places[2]] += 30;
		ai->grid_eval[empty_places[3]] += 30;
	}
	else if (connected == -1){ //block a 1 in a row
		ai->grid_eval[empty_places[0]] += 20;
		ai->grid_eval[empty_places[1]] += 20;
		ai->grid_eval[empty_places[2]] += 20;
	}
	return 1; // done
}

void ai_print_grid_eval(struct ai* ai){
	// this function prints the eval board of the AI
    // used on terminal, not psoc
	int i;
	for (i = 0; i < 64; i++){
		if (i % 4 == 0){
			printf("\n");
		}
		if (i % 16 == 0){
			printf("\n");
		}
		printf("%i ",ai->grid_eval[i]);
	}
	printf("\nPlayer %i grid eval\n",ai->player_id);
}

void ai_play_best_move(struct tic_tac_toe* t, struct ai* ai, struct disp_grid_81* disp){
	int loc = max_array(ai->grid_eval,64);
	t->grid[loc] = ai->player_id; // place move at maximum value
    disp_grid_ttc_place(disp,loc, ai->player_id); // for PSoC
}

void tta_ai_algorithm(struct disp_grid_81* disp,struct tic_tac_ai* tta, int player){
	//knowing that the player is an AI, we run AI algoirthm
	if (player == 1){
		ai_evaluate_board(&tta->game,&tta->ai_1);
		ai_play_best_move(&tta->game,&tta->ai_1,disp);
        ai_evaluate_board(&tta->game,&tta->ai_1);
		//ai_print_grid_eval(&tta->ai_1);
	}
	else if (player == -1){
		ai_evaluate_board(&tta->game,&tta->ai_2);	
		ai_play_best_move(&tta->game,&tta->ai_2,disp);
        ai_evaluate_board(&tta->game,&tta->ai_2);	
		//ai_print_grid_eval(&tta->ai_2);
	}
}

void tta_step(struct disp_grid_81* disp,struct tic_tac_ai* tta, int x, int y, int z){
	//this function is a game step
	//printf("\nCurrently player %i turn %i", tta->game.player, tta->game.turn);
    //x,y,z not used if on AI
	if (tta->game.player == 1 && tta->is_ai[0] == 1){
		tta_ai_algorithm(disp,tta,1);
		ttc_change_player(&tta->game); // change player
		//ttc_print_grid(&tta->game); //print board
	}
	else if (tta->game.player == -1 && tta->is_ai[1] == 1){
		tta_ai_algorithm(disp,tta,-1);
		ttc_change_player(&tta->game); // change player
		//ttc_print_grid(&tta->game); //print board
	}
	else{
		ttc_step(disp,&tta->game,x,y,z); // human player goes
	}
}

//int tta_play_game(struct disp_grid_81* disp,struct tic_tac_ai* tta){
//	while (tta->game.game_not_won == 0){
//		tta_step(disp,tta);
//	}
//	//printf("Player %i has won", tta->game.game_not_won);
//	return 0;
//}

/* [] END OF FILE */
