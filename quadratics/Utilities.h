#pragma once
#include <numeric>

template <typename T> constexpr T GCD(T a, T b)
{
    return a == 0 ? b : GCD(b%a, a);
}
template <typename T> constexpr T LCM(T a, T b)
{
    return a*b / GCD(a, b);
}
// T has to overload T& T::Sqrt() function
template <typename T> inline T sqrtTempl(const T& num)
{
    return num.Sqrt();
}
template <> inline int sqrtTempl(const int& num)
{
    return std::sqrt(num);
}

// For constructing Rational_t with arbitrary type Type 

const int& operator>>(const int& value, std::string& string);
int& operator>>(int& value, std::string& string);
int& operator<<(int& value, const std::string& string);

const std::string& operator>>(const std::string& string, int& value);
std::string& operator>>(std::string& string, int& value);
std::string& operator<<(std::string& string, const int& value);

/*    TESTS    */
/*
template <> inline float sqrtTempl(const float& num)
{
    return std::sqrt(num);
}
template <> inline double sqrtTempl(const double& num)
{
    return std::sqrt(num);
}
template <> inline std::string IntegralToString(const double& val)
{
    return std::to_string(val);
}
template <> inline std::string IntegralToString(const float& val)
{
    return std::to_string(val);
}
template <> inline void StrToIntegral(const std::string& str, double& val)
{
    val = std::stod(str);
}
template <> inline void StrToIntegral(const std::string& str, float& val)
{
    val = std::stof(str);
}
template <> constexpr double GCD(double a, double b)
{
    return (a >= -0.0001 && a <= 0.0001) ? b : GCD(fmod(b, a), a);
}
template <> constexpr float GCD(float a, float b)
{
    return (a >= -0.0001f && a <= 0.0001f) ? b : GCD(fmod(b, a), a);
}
// T has to have T(std::string) constructor
template <typename T> inline void StrToIntegral(const std::string& str, T& val)
{
    val = T(str);
}
template <> inline void StrToIntegral(const std::string& str, int& val)
{
    val = std::stoi(str);
}
// T has to overload T::ToString() function
template <typename T> inline std::string IntegralToString(const T& val)
{
    return val.ToString();
}
template <> inline std::string IntegralToString(const int& val)
{
    return std::to_string(val);
}
*/