#ifndef util_h
#define util_h

#include "position.h"
#include <string>

namespace fqs {
    bool is_char_in(const char *, char);

    std::string str_with_arrows(std::string, position, position);

    std::string replace_str(std::string, const std::string &, const std::string &);
}

#endif
