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
#define max_threads 99
int thread_num;
int seconds;
volatile int ticket[max_threads + 1]; 
volatile int entering[max_threads + 1];
volatile int in_cs;
double start;  
typedef struct node{
   int tid;
   int enter_times;
}pthread_data;
int end(){
	if((clock() - start) / CLOCKS_PER_SEC >= seconds)
		return -1;
	return 1;
}
int findMax(int a, int b){
	if(a > b)
		return a;
	else
		return b;
}
void lock(int tid){
	entering[tid] = 1;
	int max = 0;
	int i, j;
	for(i = 1; i <= thread_num; ++ i)
	  max = findMax(max, ticket[i]);
    ticket[tid] = max + 1;
    entering[tid] = 0;
    for(j = 1; j <= thread_num; ++ j){
       while(entering[j]){
       }
       while((ticket[j] != 0) && (ticket[j] < ticket[tid] || (ticket[j] == ticket[tid] && j < tid))){       	
       } 
    }
}

void unlock(int tid){
	ticket[tid] = 0;
}
void *run(void *arg){
   pthread_data *t = (pthread_data *)arg;
   int tid = t -> tid;
   while(1){
   	lock(tid); 
    assert(in_cs == 0);
    in_cs ++;
    assert(in_cs == 1);
    in_cs ++;
    assert(in_cs == 2);
    in_cs ++;
    assert(in_cs == 3);
    in_cs = 0;
    t -> enter_times ++;
   	unlock(tid);
   	if(end() == -1)
      pthread_exit(NULL);
   }
}
int main(int argc, char const *argv[])
{ 
    if(argc != 3){
      fprintf(stderr, "The parameters' number should be 2: the first is the number of threads and the second is the run time needed\n");
      return EXIT_FAILURE;
    }
    thread_num = atoi(argv[1]);
    if(thread_num < 0 || thread_num > 99){
      fprintf(stderr, "illegal input! The number of threads should be between 0 and 99.\n");
      return EXIT_FAILURE;
    }
    seconds = atoi(argv[2]);
    if(seconds < 0){
      fprintf(stderr, "illegal input! The run time should be a non-negative number.\n");
      return EXIT_FAILURE;
    } 
    in_cs = 0;

    start = clock();
    int tid, i;
    pthread_t threads[thread_num + 1];
    pthread_data datas[thread_num + 1];
    for(i = 1; i <= thread_num; ++i){
    	datas[i].tid = i;
    	datas[i].enter_times = 0;
    	if((tid = pthread_create(&threads[i], NULL, run, &datas[i]))){
    		fprintf(stderr, "error: pthread_create, tid: %d\n", tid);
    		return EXIT_FAILURE;
    	}
    }
    for(i = 1; i <= thread_num; ++i){
       int id = pthread_join(threads[i], NULL);
       if(id){
        fprintf(stderr, "Fail to join the %dth thread\n", i);
        return EXIT_FAILURE;
       }
    }
    for(i = 1; i <= thread_num; ++i)
    	fprintf(stderr, "thread %d enters the critical sections for %d times\n", i, datas[i].enter_times);
    fprintf(stderr, "Time is over!\n");
	return EXIT_SUCCESS;
}