/*
 * By orbyfied (2023) 
 * License can be found at https://github.com/orbyfiedis/badchessengine
 */


#ifndef BADCHESSENGINE_ARG_H
#define BADCHESSENGINE_ARG_H

#include "util.h"

#include <unordered_map>
#include <utility>
#include <vector>
#include <string>
#include <functional>

namespace arg {

// end of string
#define EOS '\0'

/// @brief Utility class for parsing strings.
class StringReader {
public:
    StringReader(std::string_view);

    // the string
    std::string_view str;
    // the length of the string
    // this will be -1 for null terminated strings
    int len;
    // the current index
    unsigned int idx;

    // get the character at the
    // given index
    [[nodiscard]] inline char at(unsigned int idx) const;

    // get the current character
    [[nodiscard]] inline char curr() const;

    // advance to the next position(s)
    inline char next();

    inline char next(int amt);

    // go back to the previous position(s)
    inline char prev();

    inline char prev(int amt);

    // peek at the current and surrounding positions
    [[nodiscard]] inline char peek(int off) const;

    // collects a string into a buffer
    // until the condition isn't met anymore
    void collect(std::function<bool(char)> pred,
                 str_buf *buf);
    char* collect_cstr(std::function<bool(char)> pred);
    std::string collect_str(std::function<bool(char)> pred);
};

/* Errno */
#define EARGNOTYPE 1
#define ENOSUCHARG 2

// arg parser functions
class Parser;

/// @brief Describes a registered option.
template<typename T>
struct Option {

    Option(
            std::string name,
            T *out,
            char ch,
            bool sw
            ) : name(std::move(name)), out(out), ch(ch), sw(sw) { }

    // the name of this option
    std::string name;
    // the value output pointer
    T *out = nullptr;
    // the character
    char ch = 0;
    // switch flag
    bool sw = false;

    /// @brief Parses a full value from the string.
    virtual int parse_from_str(Parser *parser, StringReader *reader) {
        return -EARGNOTYPE;
    }

    /// @brief Parses a full value from the string.
    /// @brief Unlike parse_from_str, this is only called when parsing a value from a single character flag.
    virtual int parse_from_str_compact(Parser *parser, StringReader *reader) {
        return parse_from_str(parser, reader);
    }

    /// @brief Sets the switch values.
    virtual int on_switch(Parser *parser, StringReader *reader) {
        return -EARGNOTYPE;
    }

};

#define IARGP(T) template<> int Option<T>::parse_from_str(arg::Parser *parser, arg::StringReader *reader)
#define IARGS(T) template<> int Option<T>::on_switch(arg::Parser *parser, arg::StringReader *reader)

// allocate a new pointer
// warning: this is not freed up automatically
#define ALLOC_PTR(t) (t*)malloc(sizeof(t))

class Parser {
private:
    // the registered arg options
    std::unordered_map<std::string, Option<void>*> options;
    std::unordered_map<char, Option<void>*> options_by_char;
public:
    Parser();

    /// @brief Register an option.
    template<typename T>
    void add_option(Option<T> option) {
        Option<void>* ptr = &UCAST(option, Option<void>);
        options[option.name] = ptr;
        if (option.ch != 0)
            options_by_char[option.ch] = ptr;
    }

    /// @brief Add a simple option.
    template <typename T>
    T* with_option(
            std::string name,
            char ch
    ) {
        T* ptr = ALLOC_PTR(T);
        add_option(Option<T>(
                           name,
                           ptr,
                           ch,
                           false));
        return ptr;
    }

    /// @brief Add a switch option.
    template <typename T>
    T* with_switch_option(
            std::string name,
            char ch
    ) {
        T* ptr = ALLOC_PTR(T);
        add_option(Option<T>(
                name,
                ptr,
                ch,
                true));
        return ptr;
    }

    /// @brief Parses the given string.
    int parse(StringReader *reader);
    int parse(std::string_view str) {
        auto reader = new StringReader(str);
        int r = parse(reader);
        delete reader;
        return r;
    }
};

}

#endif //BADCHESSENGINE_ARG_H
