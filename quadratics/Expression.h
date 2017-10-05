#pragma once
#include <vector>
#include <ostream>
#include "Term.h"

struct Expression
{
    using Termvec = std::vector<Term>;
    Expression() = default;
    Expression(const Termvec& terms);
    Expression(Termvec&& terms);
    Expression(const Expression&) = default;
    Expression(Expression&&) = default;
    Expression& operator=(const Expression&) = default;
    Expression& operator=(Expression&&) = default;
    // returns number of terms in expression
    size_t Size();
    // Returns the term if the expression contains exactly one term
    Term GetTerm(Termvec::size_type index = 0);
    friend Expression operator+(const Term& left, const Term& right);
    friend Expression operator-(const Term& left, const Term& right);
    Expression operator-(const Expression& other);
    Expression& operator-=(const Term& other);
    friend std::ostream& operator<<(std::ostream& stream, const Expression& expr);

    Termvec terms;
};