#include "error.hpp"

#include <sstream>

#include "util/strop.hpp"

namespace fqs::err
{
    FqsError::FqsError(const Pos &start,
                       const Pos &end,
                       const std::string &name,
                       const std::string &info) noexcept
        : m_start(start),
          m_end(end),
          m_name(name),
          m_info(info)
    {
    }

    std::string FqsError::toString() const noexcept
    {
        std::ostringstream ret;

        ret << m_name << ": " << m_info << "\n  in file "
            << str::quote(m_start.fname) << ", line " << m_start.lnum + 1;

        return ret.str();
    }
}  // namespace fqs::err
