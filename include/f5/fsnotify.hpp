/*
    Copyright 2015, Proteus Tech Co Ltd. http://www.kirit.com/Rask
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#pragma once


#include <sys/inotify.h>
#include <unistd.h>

#include <utility>


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
            /// Start inotify support, passing args on to callback
            template<typename... A>
            notifications(A&&... a)
            : cb(std::forward<A>(a)...), fd(inotify_init1(IN_NONBLOCK)) {
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
            void watch(const char *directory) {
                int wd = inotify_add_watch(fd, directory, IN_OPEN | IN_CLOSE | IN_CREATE | IN_MODIFY| IN_DELETE | IN_DELETE_SELF | IN_MOVE | IN_MOVE_SELF);
                if ( wd < 0 ) {
                    cb.watch_error(*this, directory);
                } else {
                    cb.watch_added(*this, fd, directory, wd);
                }
            }

            /// Add a folder to watch using lambdas to capture the result
            template<typename S, typename F>
            void watch(const char *directory, S success, F failure) {
                int wd = inotify_add_watch(fd, directory, IN_OPEN | IN_CLOSE | IN_CREATE | IN_MODIFY| IN_DELETE | IN_DELETE_SELF | IN_MOVE | IN_MOVE_SELF);
                if ( wd < 0 ) {
                    failure();
                } else {
                    success(wd);
                }
            }

            /// Enter the watch loop
            auto operator () () {
                return cb.loop(*this, fd);
            }

            /// The work that you want to do with each event
            auto operator () (const inotify_event &event) {
                return cb.process(event);
            }
        };


    }


}
