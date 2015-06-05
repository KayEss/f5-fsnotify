/*
    Copyright 2015, Felspar Co Ltd. http://www.kirit.com/f5
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#pragma once


#include <sys/inotify.h>
#include <ostream>


namespace f5 {


    inline namespace fsnotify {


            /// Print information about the event to the requested stream
            template<typename F> inline
            std::ostream &print(std::ostream &out, const inotify_event &event, F name) {
                if ( event.mask & IN_IGNORED )
                    out << "IN_IGNORED ";
                if ( event.mask & IN_CREATE )
                    out << "IN_CREATE ";
                if ( event.mask & IN_OPEN )
                    out << "IN_OPEN ";
                if ( event.mask & IN_MODIFY )
                    out << "IN_MODIFY ";
                if ( event.mask & IN_CLOSE_NOWRITE )
                    out << "IN_CLOSE_NOWRITE ";
                if ( event.mask & IN_CLOSE_WRITE )
                    out << "IN_CLOSE_WRITE ";
                if ( event.mask & IN_DELETE )
                    out << "IN_DELETE ";
                if ( event.mask & IN_DELETE_SELF )
                    out << "IN_DELETE_SELF ";
                if ( event.mask & IN_MOVE_SELF )
                    out << "IN_MOVE_SELF ";
                if ( event.mask & IN_MOVED_FROM )
                    out << "IN_MOVED_FROM ";
                if ( event.mask & IN_MOVED_TO )
                    out << "IN_MOVED_TO ";
                if ( event.mask & IN_UNMOUNT )
                    out << "IN_UNMOUNT ";
                out  << name(event.wd) << "/";
                if ( event.len )
                    out << event.name;
                if ( event.mask & (IN_MOVE_SELF | IN_MOVED_FROM | IN_MOVED_TO) )
                    out << " " << event.cookie;
                if ( event.mask & IN_ISDIR )
                    out << " [directory]" << std::endl;
                else
                    out << " [file]" << std::endl;
                return out;
            }


    }


}
