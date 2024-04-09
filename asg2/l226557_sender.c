#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<sys/wait.h>
#include<fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <operator> <operand1> <operand2>\n", argv[0]);
        
    }

    char arr[256];
    snprintf(arr, sizeof(arr), "%s %s %s", argv[1], argv[2], argv[3]);


int res,n;




res=mkfifo("chat_fifo",0777);
printf("named pipe created\n");
res=open("chat_fifo",O_WRONLY);

write(res,arr,strlen(arr)+1);
 printf("MESSAGE SENT: %s\n", arr);

close(res);
}