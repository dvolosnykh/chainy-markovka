#include "textmodel.h"
#include "tokenizer.h"
#include <cassert>
#include <random>


void TextModel::buildFrom(Tokenizer& tokenizer)
{
    m_table.clear();

    std::string prev = ".";
    while (true)
    {
        std::string token = tokenizer.next();
        if (token.empty())
            break;

        SubTable &subtable = m_table[prev];
        ++subtable.totalCounter;
        ++subtable.followers[token];

        prev = std::move(token);
    }
}

void TextModel::generateTo(std::ostream& out, unsigned minLength) const
{
    unsigned length = 0;
    std::string prev = ".";
    while (true)
    {
        const auto item = m_table.find(prev);
        assert(item != m_table.end());

        std::string token = chooseNextToken(item->second);
        assert(!token.empty());

        out << token << ' ';
        ++length;

        if (length >= minLength && token == ".")
            break;

        prev = std::move(token);
    }
    out << std::endl;
}

void TextModel::print(std::ostream& out) const
{
    for (const auto &item : m_table)
    {
        const SubTable &subtable = item.second;
        out << item.first << ": " << subtable.totalCounter << std::endl;
        for (const auto &subitem : subtable.followers)
            out << "  " << subitem.first << ": " << subitem.second << std::endl;
    }
    out << std::endl;
}

std::string TextModel::chooseNextToken(const SubTable& subtable)
{
    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());
    std::uniform_int_distribution<unsigned> uniform_dist(1, subtable.totalCounter);
    const unsigned randomChoice = uniform_dist(randomGenerator);

    unsigned choiceComplement = subtable.totalCounter - randomChoice;
    for (const auto &subitem : subtable.followers)
    {
        if (choiceComplement < subitem.second)
            return subitem.first;

        choiceComplement -= subitem.second;
    }

    return {};
}
