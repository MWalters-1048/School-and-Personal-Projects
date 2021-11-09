
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>



int main(void) {

	int num = 10;
	int lowest_index;
	int x;
	int counter = num/2;
	//int start_while_loop = 0;

	int wPartner[5] = {4, 3, 2, 0, 1};
	

	while (counter > 0) {

		int lowest  = 99999;
		for (int i = 0; i < num/2; i++) {
			if (wPartner[i] < lowest) {
				lowest = wPartner[i];
				lowest_index = i;
			}

		}

		x = lowest_index + (num/2);
		wPartner[lowest_index] = 99999;

		printf("(%d %d) ", lowest, x);

		counter--;

	}	
	
	
			
	
	return 0; 
}
