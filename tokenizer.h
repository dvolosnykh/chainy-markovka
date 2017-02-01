#pragma once

#include <istream>


class Tokenizer
{
public:
    explicit Tokenizer(std::istream &input);

    std::string next();

private:
    std::istream &m_input;
};
