#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<sys/wait.h>
#include<fcntl.h>


int main(){
int res,n;


char arr[]="bcdefAwe";

res=mkfifo("chat_fifo",0777);
printf("named pipe created\n");
res=open("chat_fifo",O_WRONLY);

write(res,arr,strlen(arr)+1);
 printf("MESSAGE SENT: %s\n", arr);

close(res);
}