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

        if (bNonBlocking)
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
int UnixSocket::Bind(const std::string   &address,
                     [[maybe_unused]] int port)
{
        struct sockaddr_un unaddr {
                .sun_family = AF_UNIX,
                .sun_path
                {
                        0
                }
        };
        size_t len;

        assert(address.size() > 0);

        // Abstract Socket Namespace
        len = (address.size() > (sizeof(unaddr.sun_path) - 2)) ? (sizeof(unaddr.sun_path) - 2) : address.size();
        if (port == ABSTRACT_ADDR) {
                memcpy(&unaddr.sun_path[1], address.c_str(), len);
        } else {
                unlink(address.c_str());
                memcpy(unaddr.sun_path, address.c_str(), len);
        }

        return bind(m_socket, (struct sockaddr *)&unaddr, sizeof(struct sockaddr_un));
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

int UnixSocket::Connect(const std::string &address, int port)
{
        struct sockaddr_un unaddr {
                .sun_family = 0,
                .sun_path
                {
                        0
                }
        };
        size_t len;

        assert(address.size() > 0);

        unaddr.sun_family = AF_UNIX;
        len               = (address.size() > (sizeof(unaddr.sun_path) - 2)) ? (sizeof(unaddr.sun_path) - 2) : address.size();

        if (port == ABSTRACT_ADDR)
                memcpy(&unaddr.sun_path[1], address.c_str(), len);
        else
                memcpy(unaddr.sun_path, address.c_str(), len);

        return connect(m_socket, (struct sockaddr *)&unaddr, sizeof(struct sockaddr_un));
}

ssize_t UnixSocket::Read(void *buf, size_t len)
{
        assert(buf);

        return read(m_socket, buf, len);
}

ssize_t UnixSocket::Read(std::string &msg)
{
        int ret;

        msg.clear();
        while(1) {
                char buf[4096] = {0};

                
                ret = read(m_socket, buf, sizeof(buf) - 1);
                if(ret <= 0)
                        break;

                msg.append(buf);
        }

        return ret;
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

