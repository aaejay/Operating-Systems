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
char operator;
int op1,op2;


res=open("chat_fifo",O_RDONLY);


n=read(res,arr,sizeof(arr));
 close(res);
  sscanf(arr, "%c %d %d", &operator, &op1, &op2);
  
  int result;
if(operator=='+')
{
result=op1+op2;

}
else if(operator=='-')
{
result=op1-op2;

}
else if(operator=='/')
{
 if (op2 != 0) {
                result = op1 / op2;
            } else {
                printf("Error: Division by zero\n");

}
}
else if(operator=='*')
{
result=op1*op2;

}
else
 printf("Invalid operator\n");





printf("Result: %d\n", result);

}