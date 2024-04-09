#include<stdlib.h>

#include<stdio.h>

#include <sys/types.h>

#include <unistd.h>

#include <sys/wait.h>



int main(void)

{
int Range_start=0;
int Range_end=97;
pid_t p=fork();



if(p<0)

{

perror("fork failed");

exit(1);

}



else if(p==0){

printf("Prime numbers in range %d to %d:\n", Range_start, Range_end);
 printf("%d ", 1); 
for(int i=Range_start;i<Range_end;i++)
{

    if (i <= 1)
        continue; 
    int is_prime = 1; // Assume the number is prime
    for (int j = 2; j * j <= i; j++) {
        if (i % j == 0) {
            is_prime = 0; // Not prime
            break; // No need to continue checking
        }
    }
    if (is_prime) {
        printf("%d ", i); // Print the prime number
    }

}




}


else
{


wait(NULL);


}



return 0;

}