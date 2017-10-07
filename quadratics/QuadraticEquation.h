#pragma once
#include "Equation.h"

class QuadraticEquation : public Equation
{
public:
    QuadraticEquation(const std::string& str);
    // Factorizes the equation and prints the steps into out
    void Factor(std::ostream& out, bool printSteps = true);
private:
    using Rational = Term::CoeffType;
    std::string GetFactorFromRoot(const Rational& root);
    std::string GetStringFromComplexRoot(const Rational& real, const Rational& imag);
    std::string GetFactorFromComplexRoot(const Rational& real, const Rational& imag);
};