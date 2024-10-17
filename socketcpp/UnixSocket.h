#pragma once

#include "Socket.h"

#include <unistd.h>
#include <sys/un.h>

#include <string>

namespace lkup69
{
class UnixSocket : public Socket
{
public:
        const static int NORMAL_ADDR   = 0;
        const static int ABSTRACT_ADDR = 1;

private:
        explicit UnixSocket(int socket);

public:
        ~UnixSocket() override;

public:
        // type: SOCK_STREAM | SOCK_DGRAM
        static UnixSocket *CreateSocket(int type = SOCK_STREAM, bool bNonBlocking = false);

public:
        int  GetSocket() override;
        void Close() override;

        // port is definded socket namespace
        int         Bind(const std::string &address, int port = NORMAL_ADDR) override;
        int         Connect(const std::string &address, int port = NORMAL_ADDR) override;
        int         Listen(int maxConnection = 1) override;
        UnixSocket *Accept() override;
        ssize_t     Read(void *buf, size_t len) override;
        ssize_t     Read(std::string &msg) override;
        ssize_t     Write(const void *buf, size_t len) override;
        ssize_t     Write(const std::string &msg) override;

protected:
        int m_socket = -1;
};
}  // namespace lkup69
