#ifndef FQS_POS_HH
#define FQS_POS_HH

#include <string>

namespace fqs::pos {
struct Pos {
    int idx, ln, col;
    std::string fn, ftxt;

    void advance();

    void advance(char currentChar);

    Pos copy() const;
};
}  // namespace fqs::pos

#endif /* FQS_POS_HH */
