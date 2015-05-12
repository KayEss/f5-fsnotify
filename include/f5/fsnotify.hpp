/*
    Copyright 2015, Proteus Tech Co Ltd. http://www.kirit.com/Rask
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#pragma once


#include <sys/inotify.h>
#include <fost/file>


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
                close(fd);
            }

            /// Add a folder to watch
            void watch(const boost::filesystem::path &) {
            }
        };


    }


}

