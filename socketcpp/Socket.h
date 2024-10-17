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
        Socket()          = default;
        virtual ~Socket() = default;

public:
        virtual int  GetSocket() = 0;
        virtual void Close()     = 0;

        virtual int Bind([[maybe_unused]] int port)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual int Bind([[maybe_unused]] const std::string &address,
                         [[maybe_unused]] int                port = -1)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual int Listen([[maybe_unused]] int maxConnection = 1)
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

        virtual int Connect([[maybe_unused]] const std::string &address)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual int Connect([[maybe_unused]] const std::string &address,
                            [[maybe_unused]] int                port)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t Read([[maybe_unused]] void  *buf,
                             [[maybe_unused]] size_t len)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t Read([[maybe_unused]] std::string &txt)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t Write([[maybe_unused]] const void *buf,
                              [[maybe_unused]] size_t      len)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t Write([[maybe_unused]] const std::string &msg)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t Send([[maybe_unused]] const void *buf,
                             [[maybe_unused]] size_t      len,
                             [[maybe_unused]] int         flags = 0)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t Send([[maybe_unused]] const std::string &msg,
                             [[maybe_unused]] int                flags = 0)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t SendTo([[maybe_unused]] const void            *buf,
                               [[maybe_unused]] size_t                 len,
                               [[maybe_unused]] const struct sockaddr *destAddr,
                               [[maybe_unused]] socklen_t              addrlen,
                               [[maybe_unused]] int                    flags = 0)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t SendTo([[maybe_unused]] const std::string     &msg,
                               [[maybe_unused]] const struct sockaddr *destAddr,
                               [[maybe_unused]] socklen_t              addrlen,
                               [[maybe_unused]] int                    flags = 0)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t SendTo([[maybe_unused]] const std::string &msg,
                               [[maybe_unused]] const std::string &destAddr,
                               [[maybe_unused]] int                port  = 0,
                               [[maybe_unused]] int                flags = 0)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t Recv([[maybe_unused]] void  *buf,
                             [[maybe_unused]] size_t len,
                             [[maybe_unused]] int    flags = 0)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual ssize_t Recvfrom([[maybe_unused]] void            *buf,
                                 [[maybe_unused]] size_t           len,
                                 [[maybe_unused]] struct sockaddr *srcAddr = nullptr,
                                 [[maybe_unused]] socklen_t       *addrlen = nullptr,
                                 [[maybe_unused]] int              flags   = 0)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return -1;
        }

        virtual bool IsConnected(void)
        {
                printf("[%s][%s][%d] Not implement yet\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
                assert(false);

                return false;
        }
};
}  // namespace lkup69
