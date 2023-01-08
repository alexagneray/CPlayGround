#include <stdio.h>
#include <pthread.h>

/**
 * A inclure pour les descripteurs de fichiers.
 * @{
*/
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
/** @} */

// #include <CUnit/CUnit.h>

#include "client.h"
#include "server.h"
#include "file.h"

int main_test_client_server(int argc, char** argv)
{
    printf("Testing client - server using TCP/IP\n");
    pthread_t client_thread;
    pthread_t server_thread;


    pthread_create(&server_thread, NULL, server_thread_main, NULL);

    sleep(2);
    pthread_create(&client_thread, NULL, client_thread_main, NULL);
    



    pthread_join(client_thread, NULL);
    pthread_join(server_thread, NULL);

    return 0;
}

#define __TEST_CLIENT_SERVER main_test_client_server(argc,argv);

int main_test_descriptors(int argc, char** argv)
{
    HFILE hFile;
    EOC eoc;
    eoc = file_create("HelloWorld.conf.olf", SimpleListFile, &hFile);

    printf("%s\n",OUTCOMEGETLABEL(eoc));


    file_create("HelloWorld", CoupleListFile, &hFile);
    return 0;
}

#define __TEST_DESCRIPTORS main_test_descriptors(argc,argv);

int main(int argc, char** argv) {
    // __TEST_CLIENT_SERVER
    __TEST_DESCRIPTORS
    return 0;
}
