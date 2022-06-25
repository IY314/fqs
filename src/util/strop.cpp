#include "strop.hpp"

#include <iomanip>
#include <sstream>

namespace str
{
    std::string quote(const std::string &s) noexcept
    {
        std::ostringstream ret;
        ret << std::quoted(s);
        return ret.str();
    }

    std::string quote(const char &c) noexcept { return quote({1, c}); }
}  // namespace str
