#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP

#include <string>

// this function should expect that `expression` has already been
// validated and thus throw no exceptions
std::pair<std::string, std::string> parse_num(const std::string &expression);
double parse_number(const std::string &expression);
bool isValidDouble(const std::string &expression);
std::string add(const std::string a, const std::string b);
std::string subtract(const std::string a, const std::string b);
std::string multiply(const std::string a, const std::string b);
#endif // __CALCULATOR_HPP
