#include "Expression.h"
#include <algorithm>

Expression::Expression(Termvec&& terms)
    : terms(terms)
{

}

size_t Expression::Size()
{
    return terms.size();
}

Term Expression::GetTerm(Termvec::size_type index)
{
    return terms[index];
}

Expression Expression::operator-(const Expression& other)
{
    // for each term of other, subtract from this copy
    Expression ret(*this);
    for (auto& term : other.terms)
        ret -= term;
    return ret;
}

Expression& Expression::operator-=(const Term& other)
{
    // search for term with same power and merge, or add the term to expression
    auto mergable = std::find_if(terms.begin(), terms.end(), [other](auto& term)
    {
        return term.power == other.power;
    });
    if (mergable != terms.end())
        *mergable -= other;
    else
    {
        // add to expression with negative sign
        Term cpy = other;
        cpy.coeff.num *= -1;
        terms.push_back(std::move(cpy));
    }
    return *this;
}

Expression::Expression(const Termvec& terms)
    :   terms(terms)
{}

Expression operator+(const Term & left, const Term & right)
{
    if (left.power == right.power)
    {
        // merge
        return Expression({ Term(left.coeff + right.coeff, left.power) });
    }
    else
    {
        return Expression({ left, right });
    }
}

Expression operator-(const Term & left, const Term & right)
{
    if (left.power == right.power)
    {
        // merge
        return Expression({ Term(left.coeff - right.coeff, left.power) });
    }
    else
    {
        return Expression({ left, right });
    }
}

std::ostream & operator<<(std::ostream& stream, const Expression & expr)
{
    for (auto i = expr.terms.begin(), end = expr.terms.end(); i != end; i++)
    {
        stream << *i;
        if (std::distance(i, end) >= 2)
            stream << "+";
    }
    return stream;
}
