// Andrew Xia
// 6.115 Microcontrollers
// Final Project
// Apr 26 2016
// Crap code


#include <stdio.h>
#include "tic_tac_toe.h"


void main( int argc, char *argv[] ){

	if (argc == 2){
		printf("The argument supplied is %s\n", argv[1]);
	}
	struct tic_tac_toe test = {1,2};
    printf("\nHELLO WORLD\n");
	char str[10];
    printf("%i", test.x);
    printf("\n");


    // print substring
    char s[] = "someting";
    int start = 1;
    int len = 3;
    printf("%.*s\n",len,s+start);

    // debugging http://stackoverflow.com/questions/21671272/segmentation-fault-core-dump

} 