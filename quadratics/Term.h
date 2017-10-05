#pragma once
#include "Rational.h"

template <typename Type>
struct Term_t
{
    friend struct Expression;
    using CoeffType = Rational_t <Type>;
    using PowerType = int;
    CoeffType coeff = 0;
    PowerType power = 0;
    Term_t() = default;
    Term_t(const std::string& str)
    {     
        size_t xpos = str.find('x');
        if (xpos != std::string::npos)
        {
            // coeff is [0,xpos) except for "-x" or just "x"
            if (xpos == 1 && str[0] == '-')
                coeff = Rational_t<Type>(-1);
            else if (xpos == 0 && str[0] == 'x')
                coeff = 1;
            else
                coeff = Rational_t<Type>(std::string(str.cbegin(), str.cbegin() + xpos));
            // check power
            size_t hatpos = str.find('^', xpos);
            if (hatpos != std::string::npos)
            {
                // power is [hatpos+1,end)
                power = std::stoi(std::string(str.cbegin() + hatpos + 1, str.end()));
            }
            else
                // found x, no power notation
                power = 1;
        }
        else
        {
            coeff = Rational_t<Type>(std::string(str.cbegin(), str.cend()));
        }
    }
    Term_t(const CoeffType& coeff, int power)
        : coeff(coeff), power(power)
    {}

    Term_t& operator-=(const Term_t& other)
    {
        if (power != other.power)
            throw std::runtime_error("Cant use operator -= on two terms with different power");
        coeff = coeff - other.coeff;
        return *this;
    }
    Term_t& operator+=(const Term_t& other)
    {
        if (power != other.power)
            throw std::runtime_error("Cant use operator += on two terms with different power");
        coeff = coeff + other.coeff;
        return *this;
    }

    template <typename T>
    friend std::ostream& operator<<(std::ostream& stream, const Term_t<T>& t)
    {
#ifdef DEBUG
        return stream << "Coeff: \"" << t.coeff << "\" power: \"" << t.power << "\";";
#else
        return stream << t.coeff << ( t.power == 0 ? "" : (std::string("x^") + std::to_string(t.power)) );
#endif
    }
};

using Term = Term_t<int>;
/*
Expression operator+(const Term& rhs) const
{
if (power == rhs.power)
{
return Expression({ Term_t(coeff + rhs.coeff, power) });
}
else
{
return Expression({ *this, rhs });
}
}
*/