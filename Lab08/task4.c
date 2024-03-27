#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char *argv[])
{
    pid_t pid1;
    pid1=fork();
    if(pid1<0){
        printf("Fork Failed");
    }
    else if(pid1==0)
    {
        printf("Hi, I am Child Process\n");
    }
    else
    {
        wait(NULL);
        printf("Completion of child Process\n");
        execlp("/bin/ls","ls","-la",NULL);
    }
    return 0;
}

