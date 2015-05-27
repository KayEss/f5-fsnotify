/*
    Copyright 2015, Proteus Tech Co Ltd. http://www.kirit.com/Rask
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#pragma once


#include <errno.h>
#include <poll.h>

#include <iostream>


namespace f5 {


    inline namespace fsnotify {


        /// Reader based on the ::poll system call
        struct poll {
            /// Callback to start listening for events
            template<typename N>
            void loop(N &notifier, int fd) {
                pollfd pfds[2];
                pfds[0] = {fd, POLLIN, 0};
                pfds[1] = {STDIN_FILENO, POLLIN, 0};
                while (true) {
                    int poll_num(::poll(pfds, 2, -1));
                    if ( poll_num == -1 ) {
                        if ( errno == EINTR )
                            continue;
                        perror("poll");
                        exit(2);
                    } else if ( poll_num > 0 ) {
                        if ( pfds[1].revents & POLLIN ) {
                            char buf;
                            while (::read(STDIN_FILENO, &buf, 1) > 0 && buf != '\n')
                                continue;
                            break;
                        }
                        pollfd &pfd = pfds[0];
                        if ( pfd.revents & POLLIN ) {
                            for ( auto item=1; true; ++item ) {
                                char buffer[10240]
                                    __attribute__ ((aligned(__alignof__(struct inotify_event))));
                                int len = ::read(fd, &buffer, sizeof(buffer));
                                if ( len == -1 && errno != EAGAIN ) {
                                    perror("reading event");
                                    exit(1);
                                } else if ( len <= 0 ) {
                                    break;
                                }
                                for ( char *pevent = buffer; pevent < buffer + len; ) {
                                    inotify_event &event = *reinterpret_cast<inotify_event*>(pevent);
                                    notifier(event);
                                    pevent += sizeof(inotify_event) + event.len;
                                }
                            }
                        }
                        if ( pfd.revents & POLLPRI ) {
                            std::cout << "POLLPRI" << std::endl;
                        }
                        if ( pfd.revents & POLLOUT ) {
                            std::cout << "POLLOUT" << std::endl;
                        }
                        if ( pfd.revents & POLLRDHUP ) {
                            std::cout << "POLLRDHUP" << std::endl;
                        }
                        if ( pfd.revents & POLLERR ) {
                            std::cout << "POLLERR" << std::endl;
                        }
                        if ( pfd.revents & POLLHUP ) {
                            std::cout << "POLLHUP" << std::endl;
                        }
                        if ( pfd.revents & POLLNVAL ) {
                            std::cout << "POLLNVAL" << std::endl;
                            pfd.fd = -1;
                        }
                    }
                }
            }
        };


    }


}

