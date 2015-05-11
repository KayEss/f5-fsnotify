/*
    Copyright 2015, Proteus Tech Co Ltd. http://www.kirit.com/Rask
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#pragma once


#include <sys/inotify.h>


namespace f5 {


    inline namespace fsnotify {


        class notifications {
            int fd;
        public:
            notifications()
            : fd(inotify_init1(IN_NONBLOCK)) {
            }
            ~notifications() {
                close(fd);
            }
        };


    }


}

