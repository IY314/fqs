#pragma once

#include <string>

namespace fqs
{
    struct Pos
    {
        unsigned long m_idx, m_lnum, m_cnum;
        std::string m_fname, m_fcontents;

        Pos(const Pos &other) noexcept = default;
        ~Pos() noexcept = default;

        Pos &operator=(const Pos &other) noexcept = default;

        void operator+=(char curr) noexcept;
    };
}  // namespace fqs
