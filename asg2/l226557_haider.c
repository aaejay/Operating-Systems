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
char arr[256];



res=open("chat_fifo",O_RDONLY);


n=read(res,arr,sizeof(arr));
 close(res);
for (int i = 0; i < strlen(arr); i++) {
        if (arr[i] >= 'A' && arr[i] <= 'Z') {
            arr[i] += 'a' - 'A';
        } else if (arr[i] >= 'a' && arr[i] <= 'z') {
            arr[i] -= 'a' - 'A';
        }
    }
printf("Message: %s\n", arr);

}