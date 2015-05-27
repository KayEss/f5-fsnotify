/*
    Copyright 2015, Proteus Tech Co Ltd. http://www.kirit.com/Rask
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#pragma once


#include <boost/asio.hpp>


namespace f5 {


    inline namespace fsnotify {


        namespace boost_asio {


            /// Boost ASIO based reader
            class reader {
                /// The ASIO interface to the raw file descriptor
                boost::asio::posix::stream_descriptor fd;

            public:
                /// Construct the reader
                reader(boost::asio::io_service &s)
                : fd(s) {
                }

                /// Callback that kicks off an ASIO task
                template<typename N>
                void loop(N &notifier, int infd) {
                    fd.assign(infd);
                    auto handler = [&notifier]() {
                    };
                };
            };


        }


    }


}

