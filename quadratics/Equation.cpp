#include "Equation.h"
#include <iostream>
#include <algorithm>

Equation::Equation(const std::string& str)
{
    if (std::count(str.cbegin(), str.cend(), '=') != 1)
        throw std::runtime_error("Equation does not have 1 equals sign in constructor parameter string.");
    using sz_t = std::string::size_type;
    sz_t eqPos = str.find('=');
    Expression lhs(GetTermsFromString({ str.cbegin(), str.cbegin() + eqPos }));
    Expression rhs(GetTermsFromString({ str.cbegin() + eqPos + 1,str.cend() }));
    equation = lhs - rhs;
}

std::vector<Term> Equation::GetTermsFromString(const std::string& str)
{
    Termvec ret;
    using sz_t = std::string::size_type;
    sz_t start = 0, end;
    bool minus = false;
    while (start < str.size())
    {
        end = str.find_first_of("+-", start);
        if (end != std::string::npos)
        {
            std::string term_s;
            if (minus)
                term_s = std::string(str.cbegin() + start - 1, str.cbegin() + end);
            else
                term_s = std::string(str.cbegin() + start, str.cbegin() + end);
            if (!term_s.empty()) // check if term with same power exists
                AddTerm(ret, Term(term_s));
        }
        else if (end == std::string::npos && start != 0)
        {
            std::string term_s; // string representation of term
            if (minus)
                term_s = std::string(str.cbegin() + start - 1, str.cend());
            else
                term_s = std::string(str.cbegin() + start, str.cend());
            if (!term_s.empty())
                AddTerm(ret, Term(term_s));
            break;
        }
        else if (end == std::string::npos && start == 0)
        {
            AddTerm(ret, Term(str));
            break;
        }
        else
            break;
        minus = (str[end] == '-');
        start = end + 1;
    }
    
    return ret;
}

void Equation::AddTerm(Termvec& vec, Term&& term)
{
    auto iter = std::find_if(vec.begin(), vec.end(), [term](auto& item)
    {
        return term.power == item.power;
    });
    if (iter == vec.end())
    {
        vec.push_back(term);
    }
    else
    {
        *iter += term;
    }
}

std::ostream & operator<<(std::ostream & stream, const Equation & eq)
{
    stream << eq.equation << "=0";
    return stream;
}
