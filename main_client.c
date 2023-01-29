#include <stdio.h>
#include <pthread.h>


#include "client.h"
#include "server/server.h"

int main(int argc, char** argv) {

    const int client_count = 10;
    pthread_t client_thread[client_count];
    pthread_t server_thread;


    
    pthread_create(&server_thread, NULL, server_thread_main, NULL);
    
    sleep(1);
    for(int i=0; i<client_count;++i)
    {
        pthread_create(client_thread + i, NULL, client_thread_main, NULL);
    }
    


    sleep(50);
    for(int i=0; i<client_count;++i)
    {
        pthread_join(client_thread[i], NULL);
    }
    
    pthread_join(server_thread, NULL);

    return 0;
}