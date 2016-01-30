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
volatile int inCircle;
volatile int total;
int thread_num;
int seconds;
double start;
static inline int atomic_xadd (volatile int *ptr)
{
  register int val __asm__("eax") = 1;
  asm volatile ("lock xaddl %0,%1"
  : "+r" (val)
  : "m" (*ptr)
  : "memory"
  );  
  return val;
}
int end(){
	if((clock() - start) / CLOCKS_PER_SEC >= seconds)
		return -1;
	return 1;
}
void *run(){
    srand(time(0));
    while(1){
      int x = rand() % 2000 - 1000;
      int y = rand() % 2000 - 1000;
      int distances = x * x + y * y;
      if(distances <= 1000 * 1000)
      	atomic_xadd(&inCircle);
      atomic_xadd(&total);
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

  inCircle = 0;
	total = 0;
	pthread_t threads[thread_num + 1];
	int cr;
	start = clock();
  int i;
	for(i = 1; i <= thread_num; ++i)
		if((cr = pthread_create(&threads[i], NULL, run, NULL))){
			fprintf(stderr, "error: pthread_create, tid: %d\n", cr);
           return EXIT_FAILURE;
	    }
    for(i = 1; i <= thread_num; ++i){
       int id = pthread_join(threads[i], NULL);
       if(id){
        fprintf(stderr, "Fail to join the %dth thread\n", i);
        return EXIT_FAILURE;
       }
    }     
    fprintf(stderr, "the approximation value is %f and the running number is %d\n", 4.0 * inCircle / total, total);
	return 0;
}