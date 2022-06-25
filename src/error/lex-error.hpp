#pragma once

#include "error.hpp"

namespace fqs::err
{
    class FqsIllegalCharError : public FqsError
    {
    public:
        FqsIllegalCharError(const Pos &pos, const char &ch) noexcept;
    };

    class FqsUnclosedStringError : public FqsError
    {
    public:
        FqsUnclosedStringError(const Pos &start, const Pos &end) noexcept;
    };

    class FqsInvalidEscapeError : public FqsError
    {
    public:
        FqsInvalidEscapeError(const Pos &start,
                              const Pos &end,
                              const std::string &esc) noexcept;
    };
}  // namespace fqs::err
