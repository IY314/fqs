#ifndef error_h
#define error_h

#include "position.h"
#include <string>

namespace fqs {
    class base_error {
        public:
        std::string to_string();

        protected:
        base_error(position, position, std::string, std::string);

        position pos_start, pos_end;
        std::string error_name, details;
    };

    class illegal_char_error : public base_error {
        public:
        illegal_char_error(position, position, std::string);
    };
}

#endif
