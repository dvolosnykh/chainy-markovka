#pragma once

#include <string>
#include <unordered_map>

class Tokenizer;


class TextModel
{
private:
    using WordsOccurrence = std::unordered_map<std::string, unsigned>;

    struct SubTable
    {
        unsigned totalCounter;
        WordsOccurrence followers;
    };

    using Table = std::unordered_map<std::string, SubTable>;

public:
    void buildFrom(Tokenizer &tokenizer);

    void generateTo(std::ostream &out, unsigned minLength) const;

    void print(std::ostream &out) const;

private:
    static std::string chooseWord(const SubTable& subtable);

private:
     Table m_table;
};
