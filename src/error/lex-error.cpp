#include "lex-error.hpp"

#include "util/strop.hpp"

namespace fqs::err
{

    FqsIllegalCharError::FqsIllegalCharError(const Pos &pos,
                                             const char &ch) noexcept
        : FqsError(pos, pos, "Illegal character", str::quote(ch))
    {
        m_end++;
    }

    FqsUnclosedStringError::FqsUnclosedStringError(const Pos &start,
                                                   const Pos &end) noexcept
        : FqsError(start, end, "Unclosed literal", "Unclosed string")
    {
    }

    FqsInvalidEscapeError::FqsInvalidEscapeError(
        const Pos &start,
        const Pos &end,
        const std::string &esc) noexcept
        : FqsError(start, end, "Invalid escape literal", esc)
    {
    }
}  // namespace fqs::err
