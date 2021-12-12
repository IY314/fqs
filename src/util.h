#ifndef util_h
#define util_h

#include "position.h"
#include "token.h"
#include <string>
#include <vector>

namespace fqs {
    bool is_char_in(const char *, char);

    template<typename T> bool is_elem_in(std::vector<T>, T);

    std::string str_with_arrows(std::string, position, position);

    std::string replace_str(std::string, const std::string &, const std::string &);
}

#endif
