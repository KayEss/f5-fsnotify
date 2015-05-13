/*
    Copyright 2015, Proteus Tech Co Ltd. http://www.kirit.com/Rask
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#pragma once


#include <sys/inotify.h>
#include <unistd.h>


namespace f5 {


    inline namespace fsnotify {


        /// Set up a set of notifications on folders
        template<typename C>
        class notifications {
            /// Instantiate an instance of the callbacks
            C cb;
            /// inotofy file descriptor
            int fd;
        public:
            /// Start inotify support
            notifications()
            : fd(inotify_init1(IN_NONBLOCK)) {
            }
            /// Close the file descriptors
            ~notifications() {
                ::close(fd);
            }

            /// Make non-copyable
            notifications(const notifications &) = delete;
            /// Make non-assignable
            notifications &operator=(const notifications &) = delete;

            /// Add a folder to watch
            void watch(const typename C::directory_type &directory) {
                int wd = inotify_add_watch(fd, directory, IN_OPEN | IN_CLOSE | IN_CREATE);
                cb.watch_added(*this, fd, directory, wd);
            }

            /// Enter the watch loop
            auto operator () () {
                return cb.loop(*this, fd);
            }
        };


    }


}

