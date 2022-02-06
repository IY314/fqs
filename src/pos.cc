#include "pos.hh"

void fqs::pos::Pos::advance() {
    ++idx;
    ++col;
}

void fqs::pos::Pos::advance(char currentChar) {
    advance();

    if (currentChar == '\n') {
        ++ln;
        col = 0;
    }
}

fqs::pos::Pos fqs::pos::Pos::copy() const {
    return fqs::pos::Pos{idx, ln, col, fn, ftxt};
}
