/*
 * By orbyfied (2023) 
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */

#include "arg.h"

#include <utility>

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

void StringReader::collect(std::function<bool(char)> pred, str_buf *buf) {
    char c;
    while ((c = curr()) != EOS && pred(c)) {
        if (buf != nullptr) {
            str_appendc(buf, c);
        }
    }
}

char* StringReader::collect_cstr(std::function<bool(char)> pred) {
    str_buf *buf = str_alloc_buf(10);
    this->collect(std::move(pred), buf);
    char *str = str_buf_tocstr(buf);
    delete buf;
    return str;
}

std::string StringReader::collect_str(std::function<bool(char)> pred) {
    str_buf *buf = str_alloc_buf(10);
    this->collect(std::move(pred), buf);
    std::string str = str_buf_tostr(buf);
    delete buf;
    return str;
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
    char c;
    while ((c = reader->curr()) != EOS) {
        // collect whitespace
        reader->collect(isblank, nullptr);

        // check for option
        if (c == '-') {
            // check for named
            if ((c = reader->next()) == '-') {
                reader->next();
                std::string name = reader->collect_cstr([&](char c) { return c != ' '; });
                // get option
                Option<void> *option = options[name];
                if (option == nullptr) {
                    dlog(P, "arg: unknown option read --%s", name.c_str());
                    return -ENOSUCHARG;
                }

                // check for explicit value
                if (reader->curr() == '=') {
                    reader->next();
                } else {
                    // check switch
                    if (option->sw) {
                        if (option->on_switch(this, reader) != 0) {
                            // todo: handle errors
                        }

                        continue;
                    } else {
                        // skip to value
                        reader->next();
                    }
                }

                // parse value and continue
                if (option->parse_from_str(this, reader) != 0) {
                    // todo: handle errors
                }
            } else /* single char */ {
                // while no space
                while ((c = reader->curr()) != ' ' && c != EOS) {
                    // get option
                    Option<void> *option = options_by_char[c];
                    if (option == nullptr) {
                        dlog(P, "arg: unknown option read -%c", c);
                        return -ENOSUCHARG;
                    }

                    // check switch
                    if (option->sw) {
                        if (option->on_switch(this, reader) != 0) {
                            // todo: handle errors
                        }
                    } else {
                        // next char
                        reader->next();
                        // collect value
                        if (option->parse_from_str_compact(this, reader) != 0) {
                            // todo: handle errors
                        }
                    }
                }
            }
        }
    }

    // return success
    return 0;
}

}