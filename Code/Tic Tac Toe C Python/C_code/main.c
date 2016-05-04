// Andrew Xia
// 6.115 Microcontrollers
// Final Project
// Apr 26 2016
// Main.c for my game


#include <stdio.h>
#include <math.h>
#include "tic_tac_toe_ai.h"


int main( int argc, char *argv[] ){

	printf("\nHELLO WORLD\n");

	if (argc >= 2){
		if (strcmp(argv[1],"2p") == 0){
			printf("\nPlaying 2p");	
			struct tic_tac_toe test;
			ttc_init(&test,4,3); //size, dimension. initialize the structure
 			ttc_play_game(&test);
		}
		else if (strcmp(argv[1],"ai") == 0){
			bool p1 = false;
			bool p2 = false;
			if (argc >= 4){
				if (strcmp(argv[2],"ai") == 0) p1 = true;
				if (strcmp(argv[3],"ai") == 0) p2 = true;
			}

			printf("\nPlaying AI");
			struct tic_tac_ai test; //init
			tta_init(&test,4,3,p1,p2);
			tta_play_game(&test);
			// tta_step(&test);
		}
		else if (strcmp(argv[1],"test") == 0){
			int bob[10] = {1,2,3,3,4,4,4,1,4,4};
			printf("\nMax Index is %i",max_array(bob,10));
		}
	}
	else{
		printf("\nPlease Specify 2p or ai");	
	}


	
	printf("\nPress any key to exit");    
	scanf("Hello");

    return 0;
} 