/*
    Copyright 2015, Proteus Tech Co Ltd. http://www.kirit.com/Rask
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/

/*
    This is a translation of the inotify example in the Linux man
    page for inotify.
    http://man7.org/linux/man-pages/man7/inotify.7.html
*/


// f5 headers
#include <f5/fsnotify.hpp>
#include <f5/fsnotify/print.hpp>

// C++ headers
#include <cassert>
#include <climits>
#include <iostream>
#include <map>
#include <vector>

// Linux headers
#include <errno.h>
#include <poll.h>


namespace {
    struct callbacks {
        /// Just use char* for the directory entries
        typedef const char *directory_type;

        /// Look up file names from descriptors
        std::map<int, directory_type> descriptors;

        /// Callback when a watch has been added
        template<typename N>
        void watch_added(N &notifier, int fd, directory_type directory,
                int descriptor) {
            std::cout << fd << ": " << descriptor << ": " << directory
                << " -- watched" << std::endl;
            descriptors[descriptor] = directory;
        }

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
                                f5::print(std::cout, event, [this](int wd){ return descriptors[wd];});
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


int main(int argc, char *argv[]) {
    if ( argc < 2 ) {
        std::cerr << "Nothing to watch, giving up.\n"
            "Specify directories to watch as arguments" << std::endl;
    }
    f5::notifications<callbacks> inotify;
    for ( int directory= 1; directory != argc; ++directory ) {
        inotify.watch(argv[directory]);
    }
    std::cout << "Watching -- press RETURN to exit" << std::endl;
    inotify();
    return 0;
}
