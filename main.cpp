#include "textmodel.h"
#include "tokenizer.h"
#include <fstream>
#include <iostream>


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " filename min_length" << std::endl;
        return EXIT_FAILURE;
    }

    const char *const filename = argv[1];
    std::ifstream fin(filename);
    if (!fin.good())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return EXIT_FAILURE;
    }

    unsigned minLength = 0;
    try {
        const std::string minLengthStr = argv[2];
        std::size_t pos;
        const unsigned long value = std::stoul(minLengthStr, &pos);

        if (pos < minLengthStr.length())
            throw std::invalid_argument(minLengthStr);
        else if (value > std::numeric_limits<unsigned>::max())
            throw std::out_of_range(minLengthStr);

        minLength = static_cast<unsigned>(value);
    } catch (const std::invalid_argument &) {
        std::cerr << "Bad min_length value. Positive integer value is expected." << std::endl;
        return EXIT_FAILURE;
    } catch (const std::out_of_range &) {
        std::cerr << "min_length value is out of range." << std::endl;
        return EXIT_FAILURE;
    }

    Tokenizer tokenizer(fin);

    TextModel model;
    model.buildFrom(tokenizer);
#ifdef PRINT_TABLE
    model.print(std::cout);
#endif
    model.generateTo(std::cout, minLength);

    return EXIT_SUCCESS;
}
