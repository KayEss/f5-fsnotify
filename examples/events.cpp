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
#include <f5/fsnotify/poll.hpp>
#include <f5/fsnotify/print.hpp>

// C++ headers
#include <cassert>
#include <climits>
#include <map>
#include <vector>


namespace {
    struct callbacks : public f5::poll {
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

        /// Called if there is an error adding a watch
        template<typename N>
        void watch_error(N &notifier, directory_type) {
            perror("setting watch");
            exit(3);
        }

        void process(const inotify_event &event) {
            f5::print(std::cout, event, [this](int wd){ return descriptors[wd];});
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
