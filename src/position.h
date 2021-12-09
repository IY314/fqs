#ifndef position_h
#define position_h

#include <string>

namespace fqs {
    class position {
        public:
        int idx, ln, col;
        std::string fn, ftxt;

        position(int, int, int, std::string, std::string);
        position() = default;
        void advance(char = '\0');
        void operator=(position);
    };
}

#endif
