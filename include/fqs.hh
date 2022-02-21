#pragma once

#include <variant>
#include <vector>

#include "errors.hh"
#include "token.hh"

#define FQS_VERSION "0.1.0"

namespace fqs {
typedef std::variant<std::vector<token::Token>, err::FQSError> RunResult;
}
