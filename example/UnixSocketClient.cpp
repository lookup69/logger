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
        string address{"/tmp/."};
        char buf[1024] = {0};

	printf("argc:%d\n", argc);
        if(argc != 2) {
                printf("./UnixSocketClient {logger_pid|unixsocket path}\n");

                return 0;
        }
        
        socketPtr.reset(UnixSocket::CreateSocket(SOCK_STREAM));

        address += argv[1];
        address += ".logger";

        if(socketPtr->Connect(address) < 0) {
                printf("Can not connect to %s\n", address.c_str());
                exit(0);
        }

        while(socketPtr->Read(buf, sizeof(buf)) > 0) {
                printf("%s", buf);
                memset(buf, 0, sizeof(buf));
        }

        return 0;
}
