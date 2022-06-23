#pragma once

#include <string>
#include <vector>

#include "tok.hpp"
#include "util/result.hpp"

namespace fqs::tok
{
    Result<std::vector<Tok>, int /* placeholder type */> tokenize(
        const std::string &fname,
        const std::string &ftext);
}
