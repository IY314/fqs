#include "util.h"
#include "position.h"
#include <string>
#include <sstream>
#include <algorithm>

bool fqs::is_char_in(const char *str, char ch) {
    return std::string(str).find(ch) != std::string::npos;
}

std::string fqs::str_with_arrows(std::string text, fqs::position pos_start, fqs::position pos_end) {
    std::stringstream ss;

    int idx_start = std::max<int>(text.substr(0, pos_start.idx).rfind('\n'), 0);

}
