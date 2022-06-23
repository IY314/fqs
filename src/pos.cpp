#include "pos.hpp"

namespace fqs
{
    void Pos::operator+=(char curr) noexcept
    {
        m_idx++;
        m_cnum++;

        if (curr == '\n')
        {
            m_lnum++;
            m_cnum = 0;
        }
    }
}  // namespace fqs
