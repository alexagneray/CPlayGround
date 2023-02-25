#include <clientlib/clientlib.h>
#include <string.h>

int main()
{
    ServerConnInfos Infos;
    strcpy(Infos.ip, "192.168.1.66");
    Infos.port = 8000;
    int n = cltlib_connect(&Infos);

    printf("%d\n", n);
    return 0;
}