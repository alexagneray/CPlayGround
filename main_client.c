#include <stdio.h>
#include <pthread.h>


#include "client.h"
#include "server.h"

int main(int argc, char** argv) {
    pthread_t client_thread;


    pthread_create(&client_thread, NULL, client_thread_main, NULL);
    



    pthread_join(client_thread, NULL);

    return 0;
}