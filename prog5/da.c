#include<stdio.h>
#include"List.h"
#include"graph.h"
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

/* TODO: implement the deferred acceptance/Gale-Shapley algorithm
- Note that we want to find the M-optimal set of stable matches
- You can write your own helper functions	
*/


int num;

//helper function
// returns true if woman 'w' prefers man 'm1' over man 'w'
bool wPrefersM1OverM(int **prefer, int w, int m, int m1) {
	for (int i = 0; i < num/2; i++) {
		if (prefer[w][i] == m1) {
			return true;
		}
		
		if (prefer[w][i] == m) {
			return false;
		}
	}
}




//using the algorithim linked in the lab document
void stable_matching(int **prefer) {
	//used to store partner of women
	int wPartner[num/2];
	//used to store freedom of men
	bool mFree[num/2];


	//if wPartner[i] == -1, then she is free
	memset(wPartner, -1, sizeof(wPartner));
	//if mFree[i] == false. then he is free 
	memset(mFree, false, sizeof(mFree));
	int freeCount = num/2;

	//while there are free men
	while (freeCount > 0) {
		int m;
		for (m = 0; m < num/2; m++) {
			if (mFree[m] == false) {
				break;
			}
		}


		//go through all women according to m's preferences
		for (int i = 0; i < num/2 && mFree[m] == false; i++) {
			int w = prefer[m][i];

			if (wPartner[w - num/2] == -1) {
				wPartner[w - num/2] = m;
				mFree[m] = true;
				freeCount--;
			} else {
				int m1 = wPartner[w - num/2];
				
				if (wPrefersM1OverM(prefer, w, m, m1) == false) {
					wPartner[w - num/2] = m;
					mFree[m] = true;
					mFree[m1] = false; 
				}
			}
		}


	}

	//making the correct order and printing matches
	int counter = num/2;
	int x;
	int lowest_index;
	
	while (counter > 0) {
		int lowest = 99999;
		for (int i = 0; i < num/2; i++) {
			if (wPartner[i] < lowest) {
				lowest = wPartner[i];
				lowest_index = i;
			}
		}

		x = lowest_index + (num/2);
		wPartner[lowest_index] = 99999;

		printf("(%d, %d) ", lowest, x);
	
		counter--;

	}

	printf("\n");
	

	
	return;
}


/* TODO: implement the main() function
Here, you would read in the input (from stdin) and execute deferred acceptance algorithm
and print out the set of M-optimal stable matches.
*/
int main(void) {

	//num is length of row
	
	//scanning in num	
	fscanf(stdin, "%d", &num);
	
	//allocating memory for the matrix 
	int** prefer = (int**)malloc(num * sizeof(int*));
	for (int i = 0; i < num; i++) {
		prefer[i] = (int*)malloc(num/2 * sizeof(int));
	}
	
	//scanning in matrix 
	int cue;
	int i = 0;
	int j = 0;
	while (fscanf(stdin, "%d", &cue) != EOF) {
		prefer[i][j] = cue;
		if (j < ((num/2) - 1)) {
			j++;
		} else {
			j = 0;
			i++;
		}
	}

	
	stable_matching(prefer);
	

	return 0;
}




















