#pragma once

#include <string>

namespace fqs
{
    struct Pos
    {
        unsigned long m_idx, m_lnum, m_cnum;
        std::string m_fname, m_ftext;

        Pos(const Pos &other) noexcept = default;
        ~Pos() noexcept = default;

        Pos &operator=(const Pos &other) noexcept = default;

        constexpr void operator+=(char curr) noexcept
        {
            (*this)++;

            if (curr == '\n')
            {
                m_lnum++;
                m_cnum = 0;
            }
        }
        constexpr void operator++(int) noexcept
        {
            m_idx++;
            m_cnum++;
        }
    };
}  // namespace fqs
