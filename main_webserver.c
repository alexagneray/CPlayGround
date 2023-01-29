#include "webserver.h"

int main()
{
    server_start();
    server_listen();
    server_loop();
    return 0;
}