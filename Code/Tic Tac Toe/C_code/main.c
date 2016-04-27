// Andrew Xia
// 6.115 Microcontrollers
// Final Project
// Apr 26 2016
// Main.c for my game


#include <stdio.h>
#include "tic_tac_toe_ai.h"


int main( int argc, char *argv[] ){

	printf("\nHELLO WORLD\n");

	if (argc == 2){
		if (strcmp(argv[1],"2p") == 0){
			struct tic_tac_toe test;
			ttc_init(&test,4,3); //size, dimension. initialize the structure
 			ttc_play_game(&test);
		}
		else if (strcmp(argv[1],"ai") == 0){
			struct tic_tac_ai test;
			tta_init(&test,4,3,0,0);
			ttc_play_game(&test->game);	
		}
	}
	else{
		printf("\nPlease Specify 2p or ai");	
	}


	
	printf("\nPress any key to exit");    
	scanf("Hello");

    return 0;
} 