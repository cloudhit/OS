#define _GNU_SOURCE
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <pthread.h>
#include <time.h>
#include <assert.h>
volatile int x = 0;
pthread_mutex_t l;

void *thread_func(){
   pthread_mutex_lock(&l);
   x ++;
   pthread_mutex_unlock(&l);
   return 0;
}
void printx(void){
	pthread_mutex_lock(&l);
	printf("%d\n", x);
	pthread_mutex_unlock(&l);
}
int main(void)
{
	int i;
	for(i = 0; i < 50; i ++){
		x = 0;
	pthread_t t1, t2;
	pthread_mutex_init(&l, NULL);
	
	pthread_create(&t1, NULL, &thread_func, NULL);
	pthread_create(&t2, NULL, &thread_func, NULL);
	printx();
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
    }
	return 0;
}