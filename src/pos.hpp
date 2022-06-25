#pragma once

#include <string>

namespace fqs
{
    struct Pos
    {
        unsigned long idx, lnum, cnum;
        std::string fname, ftext;

        Pos(const Pos &other) noexcept = default;
        ~Pos() noexcept = default;

        Pos &operator=(const Pos &other) noexcept = default;

        constexpr void operator+=(char curr) noexcept
        {
            (*this)++;

            if (curr == '\n')
            {
                lnum++;
                cnum = 0;
            }
        }

        constexpr void operator++(int) noexcept
        {
            idx++;
            cnum++;
        }
    };
}  // namespace fqs
