#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
   int variable = 0;
   pid_t child_pid = fork();


   if(child_pid < 0){
       printf("Fork failed");
   }
   else if(child_pid==0){
       variable+=200042114;
       printf("Child process value: %d\n", variable);
   }
   else if(child_pid>0){
       variable+=114;
       wait(NULL);
       printf("Parent process value: %d\n", variable);
   }
}
