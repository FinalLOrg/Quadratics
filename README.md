# Quadratics
Polynomial with rational coeffitient parser with ability to factor quadratic equations

# How to use
Equation object can take a polynomial as std::string, with rational coefficients and non-negative integral power with a variable x. 
Input should be formated as addition or subtraction of terms like `ax^p` where `a` is a rational coefficient in form of `r/s` or 
simply `r` if denominator is 1, and where `p` is a non-negative integer (powers of `0` and `1` are implicit and you can use `a` or `ax`).
Example inputs are "3x^2+13x+5-x^2+1/2x^2=4-2x^2+7x+3x^2-4x^2+2/2x^2+1/2x^2-x^2", "-x^2+6=-3x^2+7x", "x^2+4x+5=0"
### Limits for use with QuadraticEquation (e.g. creating QuadraticEquation objects and factoring them, which is **default behaviour** of this program)
* For this special case, input should be limited to terms with powers 0, 1 and 2 exclusively
* Limits of integral coefficients are limits of `int`
* Limits of rational coefficients are `int`/`int`
* Approximation of irrational square roots has rather large error

# Output
Default behaviour prints out the discriminant and each root and then the factors of equation. It's possible to pass a parameter to 
QuadraticEquation::Factor to limit the output to factors and roots only.

# License
Released under CC-0, please refer to [LICENSE](LICENSE.md).