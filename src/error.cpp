#include "error.h"
#include "position.h"
#include <string>
#include <sstream>

fqs::base_error::base_error(fqs::position _pos_start, fqs::position _pos_end, std::string _error_name, std::string _details)
                           : pos_start{_pos_start}, pos_end{_pos_end}, error_name{_error_name}, details{_details} {}

std::string fqs::base_error::to_string() {
    std::stringstream ss;
    ss << error_name << ": " << details << std::endl;
    ss << "File " << pos_start.fn << ", line " << pos_start.ln + 1;
}

fqs::illegal_char_error::illegal_char_error(fqs::position _pos_start, fqs::position _pos_end, std::string _details)
                                           : base_error(_pos_start, _pos_end, "Illegal Character", _details) {}
