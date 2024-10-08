#pragma once

#include "Socket.h"

#include <unistd.h>
#include <sys/un.h>

#include <string>

namespace lkup69 {
class UnixSocket : public Socket
{
private:
        explicit UnixSocket(int socket);
public:
        ~UnixSocket() override;

public:
        // type: SOCK_STREAM | SOCK_DGRAM
        static UnixSocket *CreateSocket(int type, bool bNonBlocking = false);

public:
        int GetSocket() override;
        void Close() override; 

        // port would no used. compatiable with socket interface only
        int Bind(const std::string &address, int port = -1) override;
        int Connect(const std::string &address) override;
        int Listen(int maxConnection) override;
        UnixSocket *Accept() override;

        ssize_t Read(void *buf, size_t len) override;
        ssize_t Write(const void *buf, size_t len) override;
        ssize_t Write(const std::string &msg) override;

protected:
        int                 m_socket = -1;
};
}