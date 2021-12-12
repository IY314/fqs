#include "position.h"
#include <string>

fqs::position::position(int _idx, int _ln, int _col, std::string _fn, std::string _ftxt)
                       : idx(_idx), ln(_ln), col(_col), fn(_fn), ftxt(_ftxt) {}

void fqs::position::advance(char current_char) {
    idx++;
    col++;

    if (current_char == '\n') {
        ln++;
        col = 0;
    }
}

void fqs::position::operator=(position pos) {
    idx = pos.idx;
    ln = pos.ln;
    col = pos.col;
    fn = pos.fn;
    ftxt = pos.ftxt;
}
