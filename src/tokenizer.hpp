#pragma once

#include <string>
#include <vector>

#include "error/error.hpp"
#include "tok.hpp"
#include "util/result.hpp"

namespace fqs::tok
{
    Result<std::vector<Tok>, err::FqsError> tokenize(const std::string &fname,
                                                     const std::string &ftext);
}
