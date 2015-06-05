/*
    Copyright 2015, Felspar Co Ltd. http://www.kirit.com/f5
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#pragma once


#include <fost/push_back>


namespace f5 {


    inline namespace fsnotify {


        inline namespace fost {


            /// Describe the event mask in JSON format
            fostlib::json mask_json(const inotify_event &event) {
                fostlib::json mask;
                if ( event.mask & IN_IGNORED )
                    fostlib::push_back(mask, "IN_IGNORED");
                if ( event.mask & IN_CREATE )
                    fostlib::push_back(mask, "IN_CREATE");
                if ( event.mask & IN_OPEN )
                    fostlib::push_back(mask, "IN_OPEN");
                if ( event.mask & IN_MODIFY )
                    fostlib::push_back(mask, "IN_MODIFY");
                if ( event.mask & IN_CLOSE_NOWRITE )
                    fostlib::push_back(mask, "IN_CLOSE_NOWRITE");
                if ( event.mask & IN_CLOSE_WRITE )
                    fostlib::push_back(mask, "IN_CLOSE_WRITE");
                if ( event.mask & IN_DELETE )
                    fostlib::push_back(mask, "IN_DELETE");
                if ( event.mask & IN_DELETE_SELF )
                    fostlib::push_back(mask, "IN_DELETE_SELF");
                if ( event.mask & IN_MOVE_SELF )
                    fostlib::push_back(mask, "IN_MOVE_SELF");
                if ( event.mask & IN_MOVED_FROM )
                    fostlib::push_back(mask, "IN_MOVED_FROM");
                if ( event.mask & IN_MOVED_TO )
                    fostlib::push_back(mask, "IN_MOVED_TO");
                if ( event.mask & IN_UNMOUNT )
                    fostlib::push_back(mask, "IN_UNMOUNT");
                return mask;
            }


        }


    }


}

