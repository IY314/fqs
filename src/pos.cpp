#include "pos.hpp"

namespace fqs
{
    void Pos::operator+=(char curr) noexcept
    {
        (*this)++;

        if (curr == '\n')
        {
            m_lnum++;
            m_cnum = 0;
        }
    }

    void Pos::operator++(int) noexcept
    {
        m_idx++;
        m_cnum++;
    }
}  // namespace fqs
