#ifndef CLIENT_LIB_H
#define CLIENT_LIB_H

#define CLIENT_ERROR(Msg) ERROR("CLIENT", Msg)
#define CLIENT_SUCCESS(Msg) SUCCESS("CLIENT", Msg)
#define CLIENT_FSUCCESS(Msg,...) FSUCCESS("CLIENT", Msg, ##__VA_ARGS__);
#define CLIENT_FERROR(Msg,...) FERROR("CLIENT",Msg, ##__VA_ARGS__);

/**
 * @brief Infos for a connection to the server.
 * 
 */
typedef struct ServerConnInfos
{
    char ip[16]; /**< Server ipv4 'XXX.XXX.XXX.XXX' */
    int port; /**< Server listening port */

} ServerConnInfos;

extern void foo(void);

/**
 * @brief Initialize the TCP connection to the server.
 * 
 * @param ConnInfos 
 * @return int -1 if failure, the socket id otherwise.
 */
extern int cltlib_connect(const ServerConnInfos* ConnInfos);


#endif // CLIENT_LIB_H