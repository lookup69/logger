/*
*/

#pragma once

#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <string>
namespace lkup69
{
// all interface should be reimplement else it will assert
class Socket
{
        Socket(const Socket &)            = delete;
        Socket &operator=(const Socket &) = delete;

public:
        Socket()      = default;
        virtual ~Socket() = default;

public:
        virtual int  GetSocket() = 0;
        virtual void Close()         = 0;

        virtual int Bind(int port)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual int Bind(const std::string &address, int port = -1)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual int Listen(int maxConnection = 1)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual Socket *Accept()
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return nullptr;
        }

        virtual int Connect(const std::string &address)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual int Connect(const std::string &address, int port)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t Read(void *buf, size_t len)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t Write(const void *buf, size_t len)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t Write(const std::string &msg)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t Send(const void *buf, size_t len, int flags = 0)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t Send(const std::string &msg, int flags = 0)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t SendTo(const void            *buf,
                               size_t                 len,
                               const struct sockaddr *destAddr,
                               socklen_t              addrlen,
                               int                    flags = 0)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t SendTo(const std::string     &msg,
                               const struct sockaddr *destAddr,
                               socklen_t              addrlen,
                               int                    flags = 0)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t Recv(void *buf, size_t len, int flags = 0)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t Recvfrom(void            *buf,
                                 size_t           len,
                                 struct sockaddr *srcAddr = nullptr,
                                 socklen_t       *addrlen = nullptr,
                                 int              flags   = 0)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }
};
}  // namespace lkup69
