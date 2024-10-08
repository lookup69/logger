#include "UnixSocket.h"

#include <fcntl.h>

using namespace lkup69;

UnixSocket::UnixSocket(int socket)
        : m_socket(socket)
{
}

UnixSocket::~UnixSocket()
{
        Close();
}

// static member function
UnixSocket *UnixSocket::CreateSocket(int type, bool bNonBlocking)
{
        int sd;

        // close socket when any of the exec-family functions succeed.
        type = type | SOCK_CLOEXEC;

        if(bNonBlocking)
                type = type | SOCK_NONBLOCK;

        if ((sd = socket(AF_UNIX, type, 0)) == -1)
                return nullptr;


        return new (std::nothrow) UnixSocket{ sd };
}

int UnixSocket::GetSocket()
{
        return m_socket;
}

void UnixSocket::Close()
{
        if (m_socket != -1)
                close(m_socket);
        m_socket = -1;
}

// port would no used. compatiable with socket interface only
int UnixSocket::Bind(const std::string &address,int port)
{
        struct sockaddr_un unaddr = { 0 };
        size_t             len;

        assert(address.size() > 0);

        unaddr.sun_family = AF_UNIX;

        // Abstract Socket Namespace
        len = (address.size() > (sizeof(unaddr.sun_path) - 2)) ? (sizeof(unaddr.sun_path) - 2) : address.size();
        memcpy(unaddr.sun_path, address.c_str(), len);
        unlink(unaddr.sun_path);

        if (bind(m_socket, (struct sockaddr *)&unaddr, sizeof(struct sockaddr_un)) < 0)
                return -1;

        return 0;
}

int UnixSocket::Listen(int maxConnection)
{
        return listen(m_socket, maxConnection);
}

UnixSocket *UnixSocket::Accept()
{
        int sd;

        if ((sd = accept(m_socket, nullptr, 0)) == -1) 
                return nullptr;

        return new (std::nothrow) UnixSocket{ sd };
}

int UnixSocket::Connect(const std::string &address)
{
        struct sockaddr_un unaddr = { 0 };
        size_t             len;

        assert(address.size() > 0);

        unaddr.sun_family = AF_UNIX;
        len               = (address.size() > (sizeof(unaddr.sun_path) - 2)) ? (sizeof(unaddr.sun_path) - 2) : address.size();
        memcpy(unaddr.sun_path, address.c_str(), len);

        if (connect(m_socket, (struct sockaddr *)&unaddr, sizeof(struct sockaddr_un)) == -1)
                return -1;

        return 0;
}

ssize_t UnixSocket::Read(void *buf, size_t len)
{
        assert(buf);

        return read(m_socket, buf, len);
}

ssize_t UnixSocket::Write(const void *buf, size_t len)
{
        assert(buf);

        return write(m_socket, buf, len);
}

ssize_t UnixSocket::Write(const std::string &msg)
{
        size_t len = msg.size();

        if (len == 0)
                return -1;

        return write(m_socket, msg.c_str(), len);
}


