/*
 * By orbyfied (2023) 
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */

#include "arg.h"

namespace arg {

// default arg parsers //
IARGP(bool) { *out = false; /* todo */ return 0; }
IARGS(bool) { *out = true; return 0; }

/*
 * StringReader
 */

StringReader::StringReader(std::string_view s) {
    str = s;
    len = s.size();
    idx = 0;
}

inline char StringReader::at(unsigned int idx) const {
    if (idx < 0 || idx >= len)
        return EOS;
    return str.at(idx);
}

// get the current character
inline char StringReader::curr() const {
    return at(idx);
}

// advance to the next position(s)
inline char StringReader::next() {
    return at(++idx);
}

inline char StringReader::next(int amt) {
    idx += amt;
    return at(idx);
}

// go back to the previous position(s)
inline char StringReader::prev() {
    return at(--idx);
}

inline char StringReader::prev(int amt) {
    idx -= amt;
    return at(idx);
}

// peek at the current and surrounding positions
inline char StringReader::peek(int off) const {
    return at(idx + off);
}

/*
 * Parser
 */

Parser::Parser() {
    options = std::unordered_map<std::string, Option<void>*>();
    options_by_char = std::unordered_map<char, Option<void>*>();
}

/// @brief Parses the given string.
int Parser::parse(StringReader *reader) {

}

}