#ifndef UTILITY_H
#define UTILITY_H

namespace dsa {

#define DO_NOTHING

enum SearchType {
    SEARCH_BIN  = 0,
    SEARCH_FIB  = 1,
};

enum SortType {
    SORT_BUBBLE = 0,
    SORT_SELECT = 1,
    SORT_MERGE  = 2,
    SORT_QUICK  = 3,
    SORT_HEAP   = 4
};

}

#include "_share/util.h"

#endif // UTILITY_H
