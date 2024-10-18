/*
        2024-10-08
*/

#include <stdio.h>

#include <string>
#include <memory>

#include "socketcpp/UnixSocket.h"

using namespace std;
using namespace lkup69;

// g++ -o UnixSocketClient -I.. UnixSocketClient.cpp ../socketcpp/UnixSocket.cpp
int main(int argc, char *argv[])
{
        unique_ptr<UnixSocket> socketPtr;
        string                 address;
        char                   buf[1024] = { 0 };

        printf("argc:%d\n", argc);
        if (argc != 3) {
                printf("./UnixSocketClient {-pid logger_pid| -path unixsocket_path}\n");

                return 0;
        }

        socketPtr.reset(UnixSocket::CreateSocket(SOCK_STREAM));

        if (std::string{ "-pid" }.compare(argv[1]) == 0) {
                address += "/tmp/.";
                address += argv[2];
                address += ".logger";
        } else if (std::string{ "-path" }.compare(argv[1]) == 0) {
                address = argv[2];
        }

        printf("address:%s\n", address.c_str());
        if (socketPtr->Connect(address) < 0) {
                printf("Can not connect to %s\n", address.c_str());
                exit(0);
        }

        while (socketPtr->Read(buf, sizeof(buf)) > 0) {
                printf("%s", buf);
                memset(buf, 0, sizeof(buf));
        }

        return 0;
}
