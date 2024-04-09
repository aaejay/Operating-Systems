#include<stdlib.h>

#include<stdio.h>

#include <sys/types.h>

#include <unistd.h>





int main(void)

{

pid_t p=fork();



if(p<0)

{

perror("fork failed");

exit(1);

}





else if(p==0)

{

printf("The child PID = %d \n",getpid());

}

else{





printf("The PID = %d \n",p);



}



return 0;

}