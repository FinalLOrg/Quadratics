#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "QuadraticEquation.h"

int main(int argc, char* argv[])
{
    bool quit = false;
#ifndef DEBUG
    while (true)
    {
        std::string input;
        std::cout << "Enter a quadratic equation or type exit to quit: ";
        std::getline(std::cin, input);
        std::cout << "Entered \"" << input << "\"" << std::endl;
        if (input == std::string("exit"))
            break;
        else if (std::count(input.cbegin(), input.cend(), '=') != 1)
        {
            // TODO: More bad input detection
            std::cout << "Bad input!" << std::endl;
            continue;
        }

    // TODO: try-catch the equation creeation
    QuadraticEquation equation(input);
#else
    {
        // example
        // 5x2 + 6x + 1 = 0
        QuadraticEquation equation({ "3x^2+13x+5-x^2+1/2x^2=4-2x^2+7x+3x^2-4x^2+2/2x^2+1/2x^2-x^2" });
        QuadraticEquation eq2({ "-x^2+6=-3x^2+7x" });
        QuadraticEquation eq3({ "x^2+4x+5=0" });
        std::cout << "Was given an equation: \"" << eq2 << "\"" << std::endl;
        eq2.Factor(std::cout);
        std::cout << "Was given an equation: \"" << eq3 << "\"" << std::endl;
        eq3.Factor(std::cout);
#endif
        std::cout << "Was given an equation: \"" << equation << "\"" << std::endl;
        equation.Factor(std::cout);
    }
    return 0;
}