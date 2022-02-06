#include "util.hh"

bool util::strcontains(const std::initializer_list<std::string>& strs,
                       char ch) {
    for (const std::string& str : strs) {
        if (util::strcontains(str, ch)) return true;
    }
    return false;
}

bool util::strcontains(const std::string& str, char ch) {
    return str.find(ch) != std::string::npos;
}

template <typename T>
bool util::veccontains(const std::vector<T>& vec, const T& elem) {
    return std::find(vec.begin(), vec.end(), elem) != vec.end();
}
