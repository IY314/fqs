#include <sstream>

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

template bool util::veccontains(const std::vector<std::string>& vec,
                                const std::string& elem);

std::string util::strreplace(std::string str, const std::string& search,
                             const std::string& replace) {
    size_t pos = 0;
    while ((pos = str.find(search, pos)) != std::string::npos) {
        str.replace(pos, search.size(), replace);
        pos += replace.size();
    }
    return str;
}

std::string util::stringWithArrows(const std::string& text,
                                   const fqs::pos::Pos& start,
                                   const fqs::pos::Pos& end) {
    std::ostringstream result;

    int idxStart = std::max<int>(text.substr(0, start.idx).rfind('\n'), 0);
    int idxEnd = text.find('\n', idxStart + 1);
    if ((std::string::size_type)idxEnd == std::string::npos)
        idxEnd = text.size();

    int lineCount = end.ln - start.ln + 1;

    for (int i = 0; i < lineCount; i++) {
        std::string line = text.substr(idxStart, idxEnd - idxStart);
        int colStart = i == 0 ? start.col : 0;
        int colEnd = i == lineCount - 1 ? end.col : line.size() - 1;

        result << line << '\n';
        result << std::string(colStart, ' ')
               << std::string(colEnd - colStart, '^');

        idxStart = idxEnd;
        idxEnd = text.find('\n', idxStart + 1);
        if ((std::string::size_type)idxEnd == std::string::npos) {
            idxEnd = text.size();
        }
    }

    return util::strreplace(result.str(), "\t", "");
}
