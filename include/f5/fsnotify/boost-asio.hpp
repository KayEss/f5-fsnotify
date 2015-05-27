/*
    Copyright 2015, Proteus Tech Co Ltd. http://www.kirit.com/Rask
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#pragma once


namespace f5 {


    inline namespace fsnotify {


        namespace boost_asio {


            /// Boost ASIO based reader
            struct reader {
                /// Callback that kicks off an ASIO task
                template<typename N>
                void loop(N &notifier, int fd) {
                };
            };


        }


    }


}

