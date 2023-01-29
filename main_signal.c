#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define SIGRT_STOPPING SIGRTMIN
#define SIGRT_ANOTHER SIGRTMIN+1

void stop_process(int)
{
    printf("Killing process.");
    exit(0);
}

int main()
{
    int pid = fork();

    
    if(!pid) // child
    {
        signal(SIGRT_STOPPING, stop_process); // Gestion d'un signal
    }
    else // parent
    {
        sleep(3);
        kill(pid, SIGRT_STOPPING);
        exit(0);
    }

    while(1);
    return(0);
}