#include "QuadraticEquation.h"
#include <algorithm>
#include <sstream>
#include <iomanip>

QuadraticEquation::QuadraticEquation(const std::string& str)
    :   Equation(str)
{
    // check if power of all terms is <= 2
    auto term = std::find_if(equation.terms.cbegin(), equation.terms.cend(), [](auto& t) {
        return t.power != 0 && t.power != 1 && t.power != 2;
    });
    if (term != equation.terms.cend())
        throw std::runtime_error(std::string{ "Not allowed power in quadratic equation. Was given a power: " }+std::string{std::to_string(term->power)});
    term = std::find_if(equation.terms.cbegin(), equation.terms.cend(), [](auto& t) {
        return t.power == 2;
    });
    if (term == equation.terms.cend())
        throw std::runtime_error(std::string{ "Quadratic equation is missing its quadratic term!" });
}

void QuadraticEquation::Factor(std::ostream& out, bool printSteps)
{
    // identify absolute, linear and quadratic term
    // calculate discriminant
    // get roots
    // get the factorized expression
    
    Rational absolute, linear, quadratic;
    {
        // start and end of equation expression
        auto start = equation.terms.cbegin(), end = equation.terms.cend();
        auto absoluteIter = find_if(start, end, [](auto& t) {
            return t.power == 0;
        });
        auto linearIter = find_if(start, end, [](auto& t) {
            return t.power == 1;
        });
        auto quadraIter = find_if(start, end, [](auto& t) {
            return t.power == 2;
        });


        if (absoluteIter != end)
            absolute = absoluteIter->coeff;
        if (linearIter != end)
            linear = linearIter->coeff;
        if (quadraIter != end)
            quadratic = quadraIter->coeff;
    }

    Rational discriminant = linear*linear - (4 * quadratic*absolute);
    if (printSteps)
        out << "Discriminant is D=b*b-4ac=" << linear << "*" << linear << "-4*" << 
            quadratic << "*" << absolute << "=" << discriminant << std::endl;

    if (discriminant >= 0)
    {
        // 2 real roots
        Rational root1, root2;
        root1 = (Rational::Sqrt(discriminant)-linear) / (2*quadratic);
        root2 = (-Rational::Sqrt(discriminant)-linear) / (2*quadratic);
        if (printSteps)
        {
            out << "root1=(-b+sqrt(D))/2a=(" << -linear << "+" << "sqrt(" << discriminant << "))/(2*" << 
                quadratic << ")=" << root1 << std::endl;
            out << "root2=(-b-sqrt(D))/2a=(" << -linear << "-" << "sqrt(" << discriminant << "))/(2*" << 
                quadratic << ")=" << root2 << std::endl;
            out << "Given quadratic equation factorized:"<< std::endl;
        }
        out << GetFactorFromRoot(root1) << GetFactorFromRoot(root2) << "=0" << std::endl;
        out << std::fixed << std::setprecision(1) << static_cast<float>(root1) << ", " <<
            static_cast<float>(root2) << std::endl;
    }
    else
    {
        // 2 complex roots
        discriminant = -discriminant;
        Rational rootreal, // real part of root is same
            root1imag, root2imag, 
            discriminantSqrt = Rational::Sqrt(discriminant), // sqrt(D) 
            commonDenominator = (2 * quadratic); // 2a
        rootreal = -linear / commonDenominator;
        root1imag = discriminantSqrt / commonDenominator;
        root2imag = -discriminantSqrt / commonDenominator;
        if (printSteps)
        {
            out << "rootreal - real part of root identical for both roots," << std::endl;
            out << "root1imag, root2imag - complex conjugates that form imaginary parts of roots" << std::endl;
            out << "rootreal=-b/2a=" << -linear << "/(2*" << quadratic << ")" 
                << "=" << rootreal << std::endl;
            out << "root1imag=sqrt(D)/2a" << discriminantSqrt << "/(2*" << quadratic << ")" 
                << "=" << root1imag << std::endl;
            out << "root2imag=-sqrt(D)/2a" << -discriminantSqrt << "/(2*" << quadratic << ")" 
                << "=" << root2imag << std::endl;
        }

        out << GetFactorFromComplexRoot(rootreal, root1imag)
            << GetFactorFromComplexRoot(rootreal, root2imag) << "=0" << std::endl;
        out << GetStringFromComplexRoot(rootreal, root1imag) << ", " 
            << GetStringFromComplexRoot(rootreal, root2imag) << std::endl;
    }
}
// returns (x-root), e.g. (2x-5) for root=5/2
std::string QuadraticEquation::GetFactorFromRoot(const Rational& root)
{
    std::stringstream out;
    out << "(";
    if (root.denom != 1)
        out << root.denom;
    out << "x";
    if (root.num < 0)
        out << "+" << -root.num;
    else
        out << "-" << root.num;
    out << ")";
    return out.str();
}
// real - real component of root, imag complex
// returns (real)+(imag)i, e.g. "2+3i" from real=2/1 and imag=3/1
std::string QuadraticEquation::GetStringFromComplexRoot(const Rational& real, const Rational& imag)
{
    std::stringstream out;
    out << std::fixed << std::setprecision(1) <<
        static_cast<float>(real) << 
        (imag >= 0 ? "+" : "-") << 
        (imag >= 0 ? static_cast<float>(imag) : static_cast<float>(-imag))
        << "i";
    return out.str();
}
// real - real component of root, imag complex
// returns (x-(real)-(imag)i), e.g. "(x-2-3i)" from real=2/1 and imag=3/1
std::string QuadraticEquation::GetFactorFromComplexRoot(const Rational& real, const Rational& imag)
{
    std::stringstream out;
    out << std::fixed << std::setprecision(1) << "(x";
    if (real.num < 0)
        out << "+" << -real.num;
    else
        out << "-" << real.num;
    if (imag.num < 0)
        out << "+" << -imag.num;
    else
        out << "-" << imag.num;
    out << "i)";
    return out.str();
}