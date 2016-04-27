// Andrew Xia
// 6.115 Microcontrollers
// Final Project
// Apr 26 2016
// Tic Tac Toe Structure for my game

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0

struct tic_tac_toe{
	int size;
	int dimension;
	// grid = {'A','B','A'}; // make this an array of length 64
	int player; // 1 is player A, -1 is player B
	int turn;
	bool game_not_won;
	// int grid_eval[]; //this keeps track of scores of all diagonals
	int grid[]; // a usually size 64 grid containing our board
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
	t->game_not_won = true;
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
	}
	printf("\n\n");
}

int ttc_step(struct tic_tac_toe* t,int x, int y, int z){
	// generic take input to allow for both terminal and psoc
	if (ttc_check_valid(t,x,y,z) == 1){
		ttc_set_grid(t,x,y,z,t->player);
		// ttc_get_grid(t,x,y,z);
		// printf("\nGot here"); 
		ttc_check_win(t);
		ttc_change_player(t);
		ttc_print_grid(t);
		return 1;
	}
	else{
		return 0; // did not work properly
	}
}

int ttc_play(struct tic_tac_toe* t){
	int *coords;
	coords = ttc_take_input(); //take input
	ttc_step(t,coords[0],coords[1],coords[2]); //play
}

int ttc_play_game(struct tic_tac_toe* t){
	while (t->game_not_won == true){
		ttc_play(t);
	}
	ttc_change_player(t);
	printf("Player %i has won", t->player);
	return 0;
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
				t->game_not_won = false;
				return 1; //there is a win
			}
		}
		for (x = 0; x < t->size; x++){ //horiz
			connected = 0;
			for (y = 0; y < t->size;y++){
				connected += ttc_get_grid(t,x,y,z);
			}
			if (connected == t->player*t->size){
				t->game_not_won = false;
				return 1; //there is a win
			}
		}
		for (x = 0; x < t->size; x++){ //vert, where z is y coord
			connected = 0;
			for (zp = 0; zp < t->size;zp++){
				connected += ttc_get_grid(t,x,z,zp);
			}
			if (connected == t->player*t->size){
				t->game_not_won = false;
				return 1; //there is a win
			}
		}
		connected = 0; //planar
		for (zp = 0; zp < t->size;zp++){ //double iterator
			connected += ttc_get_grid(t,z,zp,zp);
		}
		if (connected == t->player*t->size){
			t->game_not_won = false;
			return 1; //there is a win
		}
		connected = 0; //planar
		for (zp = 0; zp < t->size;zp++){ //double iterator
			connected += ttc_get_grid(t,z,3-zp,zp);
		}
		if (connected == t->player*t->size){
			t->game_not_won = false;
			return 1; //there is a win
		}
		connected = 0; //frontal
		for (zp = 0; zp < t->size;zp++){ //double iterator
			connected += ttc_get_grid(t,zp,z,zp);
		}
		if (connected == t->player*t->size){
			t->game_not_won = false;
			return 1; //there is a win
		}
		connected = 0; //frontal
		for (zp = 0; zp < t->size;zp++){ //double iterator
			connected += ttc_get_grid(t,3-z,z,zp);
		}
		if (connected == t->player*t->size){
			t->game_not_won = false;
			return 1; //there is a win
		}
		connected = 0; //sidal
		for (zp = 0; zp < t->size;zp++){ //double iterator
			connected += ttc_get_grid(t,zp,zp,z);
		}
		if (connected == t->player*t->size){
			t->game_not_won = false;
			return 1; //there is a win
		}
		connected = 0; //sidal
		for (zp = 0; zp < t->size;zp++){ //double iterator
			connected += ttc_get_grid(t,zp,3-zp,z);
		}
		if (connected == t->player*t->size){
			t->game_not_won = false;
			return 1; //there is a win
		}
	}
	connected = 0; //superdiag 1
	for (zp = 0; zp < t->size;zp++){ //triple iterator
		connected += ttc_get_grid(t,zp,zp,zp);
	}
	if (connected == t->player*t->size){
		t->game_not_won = false;
		return 1; //there is a win
	}
	connected = 0; //superdiag 2
	for (zp = 0; zp < t->size;zp++){ //triple iterator
		connected += ttc_get_grid(t,zp,3-zp,zp);
	}
	if (connected == t->player*t->size){
		t->game_not_won = false;
		return 1; //there is a win
	}
	connected = 0; //superdiag 3
	for (zp = 0; zp < t->size;zp++){ //triple iterator
		connected += ttc_get_grid(t,zp,zp,3-zp);
	}
	if (connected == t->player*t->size){
		t->game_not_won = false;
		return 1; //there is a win
	}
	connected = 0; //superdiag 4
	for (zp = 0; zp < t->size;zp++){ //triple iterator
		connected += ttc_get_grid(t,zp,3-zp,3-zp);
	}
	if (connected == t->player*t->size){
		t->game_not_won = false;
		return 1; //there is a win
	}
	return 0; //no win
}

void ttc_free(struct tic_tac_toe* t){
	free(t->grid);
	free(t);
}

// int main( int argc, char *argv[] ){

// 	struct tic_tac_toe test;
// 	ttc_init(&test,4,3); //size, dimension. initialize the structure

//     printf("\nHELLO WORLD\n");

//     ttc_play_game(&test);
//     // ttc_play(&test);
	
// 	printf("\nPress any key to exit");    
// 	scanf("Hello");

//     return 0;
// } 