#include "util.hh"

bool util::strcontains(const std::string& str, const char& ch) {
    return str.find(ch) != std::string::npos;
}

template <typename T>
bool util::veccontains(const std::vector<T>& vec, const T& elem) {
    return std::find(vec.begin(), vec.end(), elem) != vec.end();
}
