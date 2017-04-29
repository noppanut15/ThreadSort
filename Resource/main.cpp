// This is example code occuring RACE CONDITION. 
// programmer: supakit@it.kmitl.ac.th
// 2017 Mar 30 completed

#include <stdio.h> 
#include <thread>
#define NUM_THREADS 8
static int threadData[NUM_THREADS];
int g;

void func_mycounter(int id) { 
	int i;
	printf("\n thread[%d]‐‐start", id); 
	for (int i=0;i < 1e9;i++){
		g=g+1; 
	}
	printf("\n\t\t\t thread[%d]‐‐finish", id); 
}

int main(void) {

	std::thread threadId[NUM_THREADS]; 
	g = 0;
	printf("\n start g = %d", g);
	for (int i = 0; i < NUM_THREADS; i++) { 
		threadId[i] = std::thread(func_mycounter, i);
	}
	for (int i = 0; i < NUM_THREADS; i++){ 
		threadId[i].join();
	}
	printf("\n finish g = %d", g);
	return 0; 
}