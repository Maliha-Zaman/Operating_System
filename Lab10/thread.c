// C program to show thread functions

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int x = 5;
void* func(void* arg)
{
    // detach the current thread from the calling thread
    //pthread_detach(pthread_self());

    printf("Inside the thread\n");
    x += 100;
    printf("x = %d\n",x);
    // exit the current thread
    pthread_exit(NULL);
}

void * printInt()
{
    x -= 10;
    printf("x = %d\n",x);
    pthread_exit(NULL);
}

void fun()
{
    pthread_t ptid, ptid1;

    // Creating a new thread
    pthread_create(&ptid, NULL, func, NULL);
    pthread_create(&ptid1, NULL, printInt, NULL);
    printf("This line may be printed before thread terminates\n");

    // The following line terminates the thread manually
    //pthread_cancel(ptid);

    // Compare the two threads created
    if(pthread_equal(ptid, pthread_self()))
        printf("Threads are equal\n");
    else
        printf("Threads are not equal\n");

    // Waiting for the created thread to terminate
    pthread_join(ptid, NULL);
    pthread_join(ptid1, NULL);

    printf("x = %d\n",x);

    printf("This line will be printed after thread ends\n");

    pthread_exit(NULL);
}

// Driver code
int main()
{
    fun();
    return 0;
}
