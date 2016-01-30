#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
  pid_t pid;
  pid = fork();
  if(pid < 0){
    fprintf(stderr,"Fork Failed");
    return 1;
  }
  else if(pid == 0){
    int i = 0;
    if(argc != 2){
     printf("error:you should input a positive integer");
     return 0; 
    }
    char *tmp = argv[1];
    int cur = 0;
    while(*(tmp+cur) != '\0'){
     if(*(tmp+cur) == '-'){
      i = -1;
      break;
     }
     i = i*10 + (int)(*(tmp + cur) - '0');
     cur++;
    }
    if(i <= 0){
     printf("error:please input a positve integer");
    }else{
    while(i != 1){
     printf("%d, ", i);
     if(i % 2 == 0)
       i = i/2;
     else
       i = 3*i + 1;
    }
    printf("1\n");
 }
  }else{
   wait(NULL);
   printf("Child Complete");
  }
 return 0;
}
