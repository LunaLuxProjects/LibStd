#pragma once
#include <lstd/DataType.h>
#include <lstd/String.h>
#include <lstd/StringView.h>
namespace lstd
{
struct Lexer
{
  private:
    enum State
    {
        LETTER_MODE,
        OP_MODE,
        NUMBER_MODE,
        WHITESPACE_MODE,
    } current_state = State::LETTER_MODE;

    lstd::string_view source;
    uint64 source_size;
    uint64 index = 0;
    bool did_state_change = false;

    inline bool _break(const char &next_c) noexcept
    {
        switch (current_state)
        {
        case State::LETTER_MODE: {
            handleState(next_c);
            if (did_state_change)
                return true;
            return false;
        }
        case State::OP_MODE: {
            handleState(next_c);
            return true;
        }
        case State::NUMBER_MODE: {
            handleState(next_c);
            if (did_state_change)
                return true;
            return false;
        }
        case State::WHITESPACE_MODE: {
            handleState(next_c);
            return true;
        }
        default:
            return false;
        }
    }

    inline bool isOp(const char &c) noexcept
    {
        switch (c)
        {
        case '@':
        case '=':
        case '$':
        case '!':
        case '&':
        case '~':
        case '(':
        case ')':
        case '{':
        case '}':
        case '[':
        case ']':
        case ';':
        case ':':
        case ',':
        case '>':
        case '<':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
        case '_':
        case '|':
        case '\\':
        case '\'':
        case '\"':
        case '#':
        case '.': {
            current_state = State::OP_MODE;
            did_state_change = true;
            return true;
        }
        default:
            return false;
        }
    }

    inline bool isWhitespace(const char &c) noexcept
    {
        switch (c)
        {
        case ' ':
        case '\n':
        case '\r':
        case '\t': {
            current_state = State::WHITESPACE_MODE;
            did_state_change = true;
            return true;
        }
        default:
            return false;
        }
    }

    void handleState(const char &c) noexcept
    {
        did_state_change = false;
        switch (current_state)
        {
        case State::LETTER_MODE: {
            if (isOp(c))
                return;
            if (isWhitespace(c))
                return;
            if (isdigit(c))
            {
                current_state = State::NUMBER_MODE;
                did_state_change = true;
                return;
            }
            return;
        }
        case State::OP_MODE: {
            if (isWhitespace(c))
                return;
            if (isalpha(c))
            {
                current_state = State::LETTER_MODE;
                did_state_change = true;
                return;
            }
            if (isdigit(c))
            {
                current_state = State::NUMBER_MODE;
                did_state_change = true;
                return;
            }
            return;
        }
        case State::NUMBER_MODE: {
            if (isWhitespace(c))
                return;
            if (isOp(c))
                return;
            if (isalpha(c))
            {
                current_state = State::LETTER_MODE;
                did_state_change = true;
                return;
            }
            return;
        }
        case State::WHITESPACE_MODE: {
            if (isOp(c))
                return;
            if (isdigit(c))
            {
                current_state = State::NUMBER_MODE;
                did_state_change = true;
                return;
            }
            if (isalpha(c))
            {
                current_state = State::LETTER_MODE;
                did_state_change = true;
                return;
            }
        }
        }
    }

  public:
    struct Lex
    {
        data_size start = 0;
        data_size end = 0;
    };
    explicit Lexer(lstd::string_view source_in)
        : source(source_in)
    {
        source_size = source.size();
    };
    inline bool eof() const noexcept
    {
        return index < source_size;
    }
    const Lex getLexWord()
    {
        Lex lex;
        lex.start = index;
        [[unlikely]] if (index == 0)(void) _break(source[0]);

        while (index < source_size)
        {
            if (_break(source[min((source_size - 1), (index++) + 1)]))
                break;
        }
        lex.end = index;
        return lex;
    }

    const lstd::string_view getSubString(const data_size start, const data_size end) noexcept
    {
        return source.substr(start, max(end - start, 1));
    }

    const lstd::string getSubRealString(const data_size start, const data_size end) noexcept
    {
        lstd::string result;
        data_size true_size = max(end - start, 1) + start;
        for (data_size i = start; i < true_size; i++)
            result += source[i];
        return result;
    }
};
}; // namespace lstd