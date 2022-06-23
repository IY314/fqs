#include "tok.hpp"

namespace fqs::tok
{
    Tok::Tok(Type type,
             const std::string &value,
             const Pos &start,
             const Pos &end) noexcept
        : m_type(type),
          m_value(value),
          m_start(start),
          m_end(end)
    {
    }

    Tok::Tok(Type type, const Pos &pos) noexcept
        : m_type(type),
          m_value(""),
          m_start(pos),
          m_end(pos)
    {
        m_end++;
    }

    Tok::Tok(Type type, const std::string &value, const Pos &pos) noexcept
        : m_type(type),
          m_value(value),
          m_start(pos),
          m_end(pos)
    {
        m_end++;
    }
}  // namespace fqs::tok
