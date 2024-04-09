#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
  

int main()
{
 
 char* parse[100];
 
 
 printf("\n\n\n\t*KT's SHELL*");
 printf("\n");
 
 
 while(1)
 {
    char cur_dir[1024];
    getcwd(cur_dir, sizeof(cur_dir));
    printf("\nDirectory: %s", cur_dir);
    
    char* input;
    input = readline("\n>>> ");
    if (strlen(input) == 0) 
    {
    	printf("Not valid input");
    	break;

    } 
    else
     {
        for (int i = 0; i < 100; i++)
         {
        	parse[i] = strsep(&input, " ");
  
        	if (parse[i] == NULL)
            		break;
        	if (strlen(parse[i]) == 0)
            		i--;
    	}
    
        
       
       
 	 if (strcmp(parse[0],"exit") == 0) 
 	 {
 	    
 	    printf("\nYou Exited!\n");
 	    exit(0);
 	   
         }
         
         else if (strcmp(parse[0],"cd") == 0) 
 	 {
 	    chdir(parse[1]);
            
         }
         
         else
         {
            pid_t retVal=fork();
 	 	if (retVal == -1) 
 	 	{
        		printf("\nFailed");
        	} 
        	else if (retVal == 0) 
        	{
        		if (execvp(parse[0], parse) < 0)
        		{ 
            			printf("\nCommand Failed");
            		}	
        	
        		exit(0);
        	} 
        	
     		else if(retVal>0)
     		{
        		wait(NULL);
        		
        	}
         }
     }
 
   	
}
exit(0);
return 0;
}