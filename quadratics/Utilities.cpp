#include <string>
#include <numeric>

const int& operator >> (const int& value, std::string& string)
{
    string = std::to_string(value);
    return value;
}
int& operator >> (int& value, std::string& string)
{
    string = std::to_string(value);
    return value;
}
int& operator << (int& value, const std::string& string) noexcept
{
    value = std::stoi(string);
    return value;
}

const std::string& operator >> (const std::string& string, int& value) noexcept
{
    value = std::stoi(string);
    return string;
}
std::string& operator >> (std::string& string, int& value) noexcept
{
    value = std::stoi(string);
    return string;
}
std::string& operator << (std::string& string, const int& value)
{
    string = std::to_string(value);
    return string;
}