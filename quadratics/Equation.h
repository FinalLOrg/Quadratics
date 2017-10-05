#pragma once
#include <ostream>
#include <vector>

#include "Expression.h"
#include "Term.h"

class Equation
{
public:
    using Termvec = std::vector<Term>;
    Equation(const std::string& str);
    Equation() = delete;
    Equation(const Equation&) = default;
    Equation(Equation&&) = default;
    Equation& operator=(const Equation&) = default;
    Equation& operator=(Equation&&) = default;
    friend std::ostream& operator<<(std::ostream& stream, const Equation& eq);
protected:
    std::vector<Term> GetTermsFromString(const std::string& str);
    // Adds term to termvec if term with same power does not exist
    void AddTerm(Termvec& vec, Term&& term);
protected:
    Expression equation;
};