#include "Utils.hpp"

std::string Alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

std::string Utils::RandomString(int length) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, Alphabet.size() - 1);

    std::string random_str;

    for (int i = 0; i < length; ++i)
        random_str.push_back(Alphabet[distribution(generator)]);

    return random_str;
}