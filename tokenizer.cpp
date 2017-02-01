#include "tokenizer.h"
#include <cassert>
#include <iostream>


Tokenizer::Tokenizer(std::istream& input)
    : m_input(input)
{
}

std::string Tokenizer::next()
{
    int symbol = '\0';
    while (true)
    {
        symbol = m_input.get();
        if (!std::isspace(symbol))
            break;
    }

    if (symbol == EOF)
        return {};

    std::string token;
    if (std::isalpha(symbol) || symbol == '\'')
    {
        do
        {
            token.push_back(static_cast<char>(symbol));
            symbol = m_input.get();
        }
        while (std::isalpha(symbol) || symbol == '\'');
    }
    else if (std::isdigit(symbol))
    {
        do
        {
            token.push_back(static_cast<char>(symbol));
            symbol = m_input.get();
        }
        while (std::isdigit(symbol));
    }
    else if (std::ispunct(symbol))
    {
        do
        {
            token.push_back(static_cast<char>(symbol));
            symbol = m_input.get();
        }
        while (std::ispunct(symbol));
    }
    else
    {
        std::cerr << "Unexpected character: 0x" << std::hex << symbol << " (" << static_cast<char>(symbol) << ")" << std::endl;
        assert(false);
    }

    m_input.unget();
    return token;
}
