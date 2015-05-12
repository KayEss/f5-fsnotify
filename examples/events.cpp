/*
    Copyright 2015, Proteus Tech Co Ltd. http://www.kirit.com/Rask
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/

/*
    This is a translation of the inotify example in the Linux man
    page for inotify.
*/


#include <f5/fsnotify.hpp>
#include <iostream>


namespace {
    struct callbacks {
        typedef char *directory_type;
    };
}


int main(int argc, char *argv[]) {
    if ( argc < 2 ) {
        std::cerr << "Nothing to watch, giving up.\n"
            "Specify directories to watch as arguments" << std::endl;
    }
    f5::fsnotify::notifications<callbacks> inotify;
    for ( int directory= 1; directory != argc; ++directory ) {
        inotify.watch(argv[directory]);
    }
    return 0;
}
