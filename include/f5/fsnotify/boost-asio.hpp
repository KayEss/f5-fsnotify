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
                /// The read buffer
                boost::asio::streambuf buffer;

            public:
                /// Construct the reader
                reader(boost::asio::io_service &s)
                : fd(s), buffer(1024 * 10) {
                }

                /// Callback that kicks off an ASIO task
                template<typename N>
                void loop(N &notifier, int infd) {
                    fd.assign(infd);
                    async_read(notifier);
                };

            protected:
                template<typename N>
                void async_read(N &notifier) {
                    boost::asio::async_read(fd, buffer,
                        boost::asio::transfer_at_least(sizeof(inotify_event)),
                        [this, &notifier](auto e, auto b) {
                            this->handle(notifier, e, b);
                            this->async_read(notifier);
                        });
                }
                template<typename N>
                void handle(N &notifier, const boost::system::error_code &error, std::size_t bytes) {
                    while ( buffer.size() >= sizeof(inotify_event) ) {
                        union {
                            inotify_event event;
                            char buffer[sizeof(inotify_event) + NAME_MAX + 1];
                        } block;
                        char *inp = reinterpret_cast<char *>(&block.event);
                        buffer.sgetn(inp, sizeof(block.event));
                        buffer.sgetn(inp + sizeof(block.event), block.event.len);
                        notifier(block.event);
                    }
                }
            };


        }


    }


}

