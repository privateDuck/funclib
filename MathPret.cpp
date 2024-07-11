// MathPret.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "tokenizer.hpp"
#include "parser.hpp"
#include "printer.hpp"

int main()
{
    funclib::Tokenizer tok("sin(-12) + 3(2)^2");
    auto toks = tok.GetTokens();
    funclib::Parser parser;
    
    auto ptkn = parser.ParseExpression(toks);
    for (const auto& t : toks) {
        std::cout << t << '\n';
    }
    std::cout << '\n';
    for (const auto& t : ptkn) {
        std::cout << t << '\n';
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
