#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>
static void swap(int* a, int* b){
	int tmp = *a;
        *a = *b;
	*b = tmp;
}
static void quickSort(int* tmp, int l, int r){
	
	if(l >= r) return;
	int guard = *(tmp + l);
	int left = l + 1, right = r;
    while(left <= right){
    	while(left <= right && *(tmp + left) <= guard)
    		left ++;
        while(left <= right && *(tmp + right) > guard)
        	right --;
        if(left > right) break;
        swap((tmp + left), (tmp + right));
        left ++;
        right --;
    }
    swap((tmp + l), (tmp + right));
    quickSort(tmp, l, right - 1);
    quickSort(tmp, right + 1, r);

}
unsigned long byte_sort(unsigned long arg){
  int byte[8];
  unsigned long cur = arg;
  for(int i = 0; i < 8; i ++){
  	byte[i] = (cur >> i * 8) & 0xff;
  }
  quickSort(byte, 0, 7);
  unsigned long ans = 0;
  for(int i = 7; i >=0; i --){
    ans = ans | (((unsigned long)byte[i]) << i * 8);
  }
  printf("%lx\n", ans);
  return ans;
}
unsigned long nibble_sort(unsigned long arg){
	int nibble[16];
	unsigned long cur = arg;
	for(int i = 0; i < 16; i ++){
		nibble[i] = (cur >> i * 4) & 0xf;
	}
	quickSort(nibble, 0, 15);
	unsigned long ans = 0;
	for(int i = 15; i >= 0; i --){
		ans = ans | (((unsigned long)nibble[i]) << i * 4);
	}
	printf("%lx\n", ans);
	return ans;
}
struct elt{
	char val;
	struct elt * link;
};
struct elt * name_list(void)
{
	/* data */
	char string[] = "Yupeng";
	char *p = string;
        struct elt * ans, * head;
	if(NULL == (head = (struct elt*)malloc(sizeof(struct elt)))){
		free(head);
    head = NULL;
		return NULL;
	}
	ans = head;
	while(*p != '\0'){
      ans -> link = (struct elt*)malloc(sizeof(struct elt));
      if(ans -> link == NULL){
      	free(ans -> link);
        ans -> link = NULL;
        while(head != NULL){
	        struct elt* tmp = head;
          head = head -> link;
          free(tmp);
          tmp = NULL;         
        }
      	return NULL;
      }
      ans -> link ->val = *p;
      ans -> link -> link = NULL;
      ans = ans -> link;
      p = p + 1;
	}
        struct elt* res = head -> link;
        free(head);
        head = NULL;
	      return res;
}
enum format_t{
	OCT = 66, BIN, HEX
};
void convert(enum format_t mode, unsigned long value){
	char number[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	unsigned long N = 0, format = 0;
	switch(mode){
		case HEX: {
      format = 16;
      N = 16;
			break;
		}
		case OCT:{
			format = 8;
			N = 22;
			break;
		}
		case BIN:{
			format = 2;
			N = 64;
			break;
		}
		default: break;
      } 
        char hex[66] = {0};
        hex[N] = '\n';
        unsigned long cur = N - 1;
        while(value != 0){
            hex[cur--] = number[value % format];
            value = value / format;
        }
        while(1){
             hex[cur]= '0';
             if(cur == 0) break;
             cur --;
        }
        for(unsigned long i = 0; i < N; i ++){
            putc(hex[i], stdout);
        }
}
void draw_me(void){
  int fp = 0;
  char c[] = 
"?I7$$$$7777$ZZOO88O8888DD8DD8DDDDDDD888DDD88DDDDDDDDDZ77????
I?+++==~~~~OZZZOOO88888D888888DDDDDDD888DDDDDDDDDDDDDDO7????
?IIIII777+7OOZZZZO8888D888D88DDDDDDD88888DDDDDDDDDDDDDD7I???
?+=++++??8OOOZZOOO88888888D8888DDDD8DDDDDDDDDDDDDDDDDDDO????
?=~====+$OOOOOOOO8OOOOOOOOOOOO8888D888DDDDDDDDDDDDDDDDDO????
?=~====7D8O8888OOO8OZZZZZOOZZZOOO88888DDDDDDDDDDDDDDDDDZ????
?=~~~=+8OZ888888OOOOZ$Z$$ZZ$ZZOOOO888DD888D8DDDDDDDDDDDO????
?~~~~~I8Z$88888OOZZO$777$$$$$$ZZOO888DD8888888DDDDDDDDD8????
?~:~~:=$8OO88OOZ$7$Z7I=?7I77$$$ZZZO888888888888DDDDDDDD8????
?=::::+?8$OOO8I$7=I7+~:??III77777$O88OOOOOOOOOO8DDDDD8D8????
?=::::=:$IOOO8?I$$$$7+=??II?IIIII7ZOOZOOOO888OO8DDDDDDD8????
?~,:::~:?7ZOOO?=?~=+I$ZOOZ7I??I7I7$ZOO888DD88888DDDDDDDO????
?~,,,::7I$$Z8OZ+=::~~=I$$ZZ$III7$ZOO88888OOOOOO8DDDDDDDZ????
?:.,,,,ZZOZOOZD=??I7ZOOOOZZZ?+?$ZOO8OOOOOOOOOOO8DDDDDDD7????
?:.,,,,?ZOO8O8=:,:++==777I??Z$=$O8OOOO88OZ88OZZ88DDDDDDI????
?,.,,,,:7ZO8O8,,,.:~~=+II==+$~,IZ8OOZ$$$ZZZOZZZ8DDDDDDOI?I??
?,......,ZZOO8:,.,,:==++=~~~..,I$ZZZZ777$$ZZZ$$ZDDDDD88Z????
?,.......~$ZOO=,,,,,~~~~~:,...,I$ZZZ$77$$$$ZZZZZDDDD8DZZ????
?,..........?I=,,,,,,,::::,,...+IZZZZ$$$$$$ZZZZ8DDD8Z77$I???
?,..........,~~,,,,,,::~~~....,=?$ZZZ$7777$ZZZZD8D7$Z7$$I???
?,..........:~:,,,,,::~==:,,,,~+I$$$O$$77$$ZZZZ8Z?IID77O????
?,..........,,,,,,,,::~~:,~++=I7$OZZZZ$$$$ZZ$Z$O77$$7OZZ????
?:.,,,,,,,,,::::,,,,:::,,...,:+I$ZZZZZ$$$$ZZZZ$O$$$$$$OO????
?,..........,:...,,,,,:,,,,,,:I~?$ZZZZ$$$$$$$ZZOZZZZZZZZ????
?,.......... .....,,,::~~:,:+++I7$$$ZZZZZZ$ZOZZ8ZZZZZZZO????
?,........ .......,::::=I?7$II$ZOOOOOZZZZ$ZZZOZOZZZZZZZZ????
?,......,.........,+,::::~=~::=IIZZOZZZ$Z88ZZZZOZZZZZZZ$????
?, ......,..,,.....?,,:~~~~+??I$ZZZZZ$$ZO88OZZZZZZZZZZZ7????
?, ..:.. ....:~....:,,:::~~=II7$$ZZZZ$ZOO8OZZZZZOZ$$ZZ$7????
?,....~:....,=?~,...I:,~==~~+?I$$ZZ$ZOOOOOO$$$$$O$$$$$77????
?,....,=~...,=I=:...II,:~+?+??7$Z$$ZZZZZZZ$7$777Z$7$77IZ????
?..,...=+~,..~I+=...,I~,,,~=II7777II?I7II7?I7?II7$I7II7I????
?,,:...~++=,,~7I+:,,.~=:,,:~+++??++=+?I?II+II+++I$?I??$+????";

  fp = syscall(SYS_open, "me.txt",O_CREAT | O_WRONLY | O_TRUNC,0755);
  if(fp == -1){
    syscall(SYS_unlink, "me.txt");
  }
  int num = 0;
  while(c[num] != '\0')
    num ++;
  int cur = syscall(SYS_write, fp, c, num);
  if(cur != num){
    syscall(SYS_close, fp);
    syscall(STS_unlink, fp);
  }
  syscall(SYS_close,fp);
}
int main(int argc, char const *argv[])
{
  unsigned long arg = 0x1;
	byte_sort(arg);
	nibble_sort(arg);
	struct elt * rec = name_list();
        while(rec != NULL){
          printf("%s", &rec->val);
          rec = rec -> link;
  }
  printf("\n");
	convert(66, 0x123);
  printf("\n");
	convert(67, 0x123);
  printf("\n");
	convert(68, 0x123);
  printf("\n");
  draw_me();
	return 0;
}
