#ifndef build_code_h
#define build_code_h

#include "node.h"
#include "error.h"
#include <string>
#include <utility>
#include <optional>

namespace fqs {
    std::pair<std::optional<node>, std::optional<base_error>> run(std::string, std::string);
}

#endif
