#include "webserver.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

static int gs_nWebServer = -1;

void server_start()
{
    struct addrinfo req;
    req.ai_family = AF_INET;
    req.ai_flags = AI_NUMERICHOST | AI_PASSIVE;
    req.ai_socktype = SOCK_STREAM;
    req.ai_protocol = 0;

    struct addrinfo* res = NULL;
    int ret = -2;


    gs_nWebServer = socket(AF_INET, SOCK_STREAM, 0);

    if(gs_nWebServer < 0)
    {
        int nErr = errno;
        fprintf(stderr, "socket() : an error occured -> %s\n", gai_strerror(nErr));
    }
    else
    {
        printf("socket() : success\n");
    }

    ret = getaddrinfo(NULL,"8080",&req, &res);

    if(ret  < 0)
    {
        fprintf(stderr, "getaddrinfo() : an error occured -> %s\n", gai_strerror(ret));
    }
    else
    {
        printf("getaddrinfo() : success\n");
    }

    

    ret = bind(gs_nWebServer, res->ai_addr, res->ai_addrlen);

    if(ret < 0)
    {
        fprintf(stderr, "bind() : an error occured -> %s\n", gai_strerror(ret));
    }
    else
    {
        printf("bind() : success\n");
    }
}

void server_listen()
{
    int res = -1;
    
    res = listen(gs_nWebServer, 10);

    if(res < -1)
    {
        printf("listen() : an error occured -> %s\n", gai_strerror(res));
    }

    else 
    {
        printf("The server is now listening ...\n");
    }    
}

void server_loop()
{
    int nClient = -1;

    printf("Entering server loop !\n");
    printf("Waiting for new connections ...\n");

    struct sockaddr ClientAddr;
    socklen_t ClientAddrLen;

    nClient = accept(gs_nWebServer, &ClientAddr, &ClientAddrLen);

    if(nClient >= 0)
    {
        printf("A new client is connected !\n");

        close(nClient);
    }

}