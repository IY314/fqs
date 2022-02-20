#include "pos.hh"

fqs::pos::Pos::Pos(int idx, int ln, int col, const std::string& fn,
                   const std::string& ftxt)
    : fn(fn), ftxt(ftxt) {
    this->idx = idx;
    this->ln = ln;
    this->col = col;
}

fqs::pos::Pos::Pos(const fqs::pos::Pos& pos) : fn(pos.fn), ftxt(pos.ftxt) {
    idx = pos.idx;
    ln = pos.ln;
    col = pos.col;
}

fqs::pos::Pos& fqs::pos::Pos::operator=(const fqs::pos::Pos& rhs) {
    idx = rhs.idx;
    ln = rhs.ln;
    col = rhs.col;
    fn = rhs.fn;
    ftxt = rhs.ftxt;
    return *this;
}

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
