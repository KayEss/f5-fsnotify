/*
    Copyright 2015, Proteus Tech Co Ltd. http://www.kirit.com/Rask
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#include <fost/main>
#include <f5/fsnotify.hpp>

#include <thread>
#include <boost/asio.hpp>


namespace {
}


FSL_MAIN("fsnotify-events", "fsnotify event display")
        (fostlib::ostream &out, fostlib::arguments &args) {
    std::thread io_service([]() {
    });
    io_service.join();
    return 0;
}
