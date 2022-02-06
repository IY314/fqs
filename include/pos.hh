#pragma once

#include <string>

namespace fqs::pos {
struct Pos {
    int idx, ln, col;
    std::string fn, ftxt;

    Pos(int idx, int ln, int col, const std::string& fn,
        const std::string& ftxt);
    Pos(const Pos& pos);
    Pos() = default;

    Pos& operator=(const Pos& rhs);

    void advance();
    void advance(char currentChar);
};
}  // namespace fqs::pos
