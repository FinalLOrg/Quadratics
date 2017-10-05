#pragma once
#include <string>
#include <ostream>
#include "Utilities.h"

template <typename Type>
struct Rational_t
{
    using NumberType = Type;
    Rational_t() = default;
    Rational_t(Type num, Type denom)
        :   num(num), denom(denom) 
    {
        Simplify();
    }
    Rational_t(Type num) : num(num) {}
    Rational_t(Rational_t&&) = default;
    Rational_t(const Rational_t&) = default;
    Rational_t(const std::string& str)
    {
        {
            size_t slashpos = str.find('/');
            if (slashpos == std::string::npos)
            {
                num << str;
            }
            else
            {
                num << std::string(str.cbegin(), str.cbegin() + slashpos);
                denom << std::string(str.cbegin() + slashpos + 1, str.cend());
            }
        }
        Simplify();
    }
    Rational_t& operator=(const Rational_t&) = default;
    Rational_t& operator=(Rational_t&&) = default;
    Type num = 0; // numerator
    Type denom = 1; // denominator

    // Reduces to simplest form of fraction
    void Simplify()
    {
        if (denom < 0)
        {
            denom = -denom;
            num = -num; // if num is negative, denom was negative too, so fraction has to be positive
                        // if num is positive, denom was negative so make num negative instead
        }
        Type gcd;
        if (num < 0)
            gcd = GCD(-num, denom);
        else
            gcd = GCD(num, denom);

        if (gcd != 1)
        {
            num /= gcd;
            denom /= gcd;
        }
    }
    static Rational_t Invert(const Rational_t& rat)
    {
        // TODO: throw if the new denom would be zero, throw own exception inheriting from std::runtime_error
        if (rat.num == 0)
            throw std::runtime_error("Inversion of 0 fraction is not possible!");
        return Rational_t(rat.denom, rat.num);
    }
    operator float() const
    {
        return static_cast<float>(num) / static_cast<float>(denom);
    }
    operator double() const
    {
        return static_cast<double>(num) / static_cast<double>(denom);
    }
    bool operator>=(int x) const
    {
        return (num >= 0 && denom > 0) || (num < 0 && denom < 0);
    }
    
    Rational_t& operator= (int i)
    {
        num = i;
        denom = 1;
        return *this;
    }
    Rational_t operator+(const Rational_t& other) const
    {
        if (denom == other.denom)
            return Rational_t(num + other.num, denom);
        else
        {
            auto lcm = LCM(denom, other.denom);
            auto num1 = num * lcm / denom;
            auto num2 = other.num * lcm / other.denom;
            return Rational_t(num1 + num2, lcm);
        }
    }
    Rational_t operator-(const Rational_t& other) const
    {
        if (denom == other.denom)
            return Rational_t(num - other.num, denom);
        else
        {
            auto lcm = LCM(denom, other.denom);
            auto num1 = num * lcm / denom;
            auto num2 = other.num * lcm / other.denom;
            return Rational_t(num1 - num2, lcm);
        }
    }
    Rational_t operator*(const Rational_t& other) const
    {
        return Rational_t(num*other.num, denom*other.denom);
    }
    Rational_t operator*(int x) const
    {
        return Rational_t(num*x, denom);
    }
    friend Rational_t operator*(int x, const Rational_t& rat)
    {
        return Rational_t(x*rat.num, rat.denom);
    }
    Rational_t operator/(const Rational_t& other) const
    {
        return *this * Invert(other);
    }
    Rational_t operator-() const
    {
        return Rational_t(-num, denom);
    }
    static Rational_t Sqrt(const Rational_t& rat)
    {
        return Rational_t(sqrtTempl(rat.num), sqrtTempl(rat.denom));
    }

    template <typename T>
    friend std::ostream& operator<<(std::ostream& stream, const Rational_t<T>& r)
    {
        std::string num, denom;
        r.num >> num;
        r.denom >> denom;
#ifdef DEBUG
        return stream << "(" << r.num << "/" << r.denom << ")";
#else
        return stream << (r.denom == 1 ?
            num : 
            num + std::string("/") + denom
        );
#endif
    }
};