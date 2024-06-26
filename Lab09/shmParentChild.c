#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    // ftok to generate unique key
    //key_t key = ftok("shmfile",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(IPC_PRIVATE,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    int *str = (int*) shmat(shmid,NULL,0);
    pid_t p = fork();

    if (p < 0)
    {
        printf("fork Failed" );
        return 1;
    }

    // Parent process
    else if (p > 0)
    {
        int fixed_int[10] = {0,1,2,3,4,5,6,7,8,9};
        int i;

        printf("Inside parent:");
        for(i=0; i<10; i++)
        {
            str[i]=fixed_int[i];
            printf("%d ",str[i]);
        }
        printf("\n");
        printf("Data written in memory: \n");


        wait(NULL);
        printf("Inside parent:");
        for(i=0;i<10;i++)
        {
            printf("%d ",str[i]);
        }
        printf("\n");


        //detach from shared memory
        shmdt(str);
    }

    // child process
    else
    {

        int i;

        printf("Data read from memory: \n");
        printf("Inside child:");
        for(i=0; i<10; i++)
        {
            printf("%d ",str[i]);
            if(str[i]%2==0)
                str[i]+=5;
            else if(str[i]%2==1)
                str[i]+=100;
        }
        printf("\n");

        //detach from shared memory
        shmdt(str);

        // destroy the shared memory
        shmctl(shmid,IPC_RMID,NULL);

        exit(0);
    }
}
