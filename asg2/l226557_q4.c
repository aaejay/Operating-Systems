#include<stdlib.h>

#include<stdio.h>

#include <sys/types.h>

#include <unistd.h>





int main(void)

{


int fd[2];
int fd1[2];
pipe(fd);
pipe(fd1);

  if (pipe(fd) == -1 || pipe(fd1) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

pid_t p=fork();

if(p<0)

{

perror("fork failed");

exit(1);

}





else if(p==0)

{
close(fd[1]);
close(fd1[0]);

int array[10];
read(fd[0],&array,sizeof(array));
int sum=0;
for(int i=0;i<10;i++)
{
sum+=array[i];

}

write(fd1[1],&sum,sizeof(sum));

close(fd[0]);
close(fd1[1]);
}

else{

close(fd[0]);
close(fd1[1]);
int array[10]={0};
for(int i=0;i<10;i++)
{
array[i]=i+7;

}

write(fd[1],array,sizeof(array));
int sum;
read(fd1[0],&sum,sizeof(sum));

printf("Sum received from child: %d\n", sum);

close(fd[1]);
close(fd1[0]);

}



return 0;

}