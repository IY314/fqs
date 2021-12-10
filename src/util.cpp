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
    int idx_end = text.find('\n', idx_start + 1);
    if (idx_end == std::string::npos) {
        idx_end = text.size();
    }

    int line_count = pos_end.ln - pos_start.ln + 1;

    for (int i = 0; i < line_count; i++) {
        std::string line = text.substr(idx_start, idx_end - idx_start);
        int col_start = i == 0 ? pos_start.col : 0;
        int col_end = i == line_count - 1 ? pos_end.col : line.size() - 1;

        ss << line << '\n';
        ss << std::string(col_start, ' ') << std::string(col_end - col_start, '^');

        idx_start = idx_end;
        idx_end = text.find('\n', idx_start + 1);
        if (idx_end == std::string::npos) {
            idx_end = text.size();
        }
    }

    return fqs::replace_str(ss.str(), std::string("\t"), std::string(""));
}

std::string fqs::replace_str(std::string subject, const std::string &search, const std::string &replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}
