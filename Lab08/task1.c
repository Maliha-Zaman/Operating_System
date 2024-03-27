#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num_processes = 8;
    
    for (int i = 0; i < num_processes; ++i) {
        pid_t pid = fork();
        
        if (pid < 0) {
            printf("Fork failed.\n");
            return 1;
        } else if (pid == 0) {
            
            printf("Child Process ID: %d, Parent Process ID: %d\n", getpid(), getppid());
            return 0;
        }
    }
    
    
    return 0;
}

