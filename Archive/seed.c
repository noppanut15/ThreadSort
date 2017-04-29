#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define AMOUNTS 10
#define BOUND 1000
int main(){
	srand(time(NULL));   // should only be called once
	int r;
	int i;
	for(i = 0; i < AMOUNTS; i++){
		r = rand() % BOUND;      // returns a pseudo-random integer between 0 and RAND_MAX
		printf("%d\n", r);
	}
	return 0;
}