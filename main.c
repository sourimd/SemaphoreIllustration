#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>

#define SIZE 2

sem_t semVar;

void * threadFunction( void * threadNo){
	int * i = (int *)threadNo;
	
	sem_wait( &semVar );
	printf( "Thread %d working\n", *i);
	sleep(1);
	sem_post( &semVar );
	
	pthread_exit(NULL);
}

int main(){
	sem_init( &semVar, 0, SIZE);
	void * exit_status[5];

	pthread_t threadID[5];

	int i;
	for(i=0;i<5;i++){
		pthread_create( &threadID[i], NULL, threadFunction, &threadID[i] );
	}

	for( i=0;i<5;i++){
		pthread_join( threadID[i], &exit_status[i] ); 
	}

	sem_destroy( &semVar );
}