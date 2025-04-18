#include "calculator.hpp"
#include <string>
#include <utility>

std::pair<std::string, std::string> parse_num(const std::string &expression) 
{ 
    std::string whole = "";
    std::string decimal = "";
    size_t decPos = expression.find(".");
    if (decPos != std::string::npos) 
    {
        for (size_t i = 0; i < decPos; i++)
        {
            whole += expression[i];
        }
        for (size_t i = decPos + 1; i < expression.size(); i++ )
        {
            decimal += expression[i];
        }
    }
    else
    {
        whole = expression;
        decimal = "0";
    }
    return {whole, decimal};
}

double parse_number(const std::string &expression)
{
    
    bool is_negative = false;
    size_t start_index = 0;

    if (expression[0] == '-') {
        is_negative = true;
        start_index = 1;
    } else if (expression[0] == '+') {
        start_index = 1; 
    }

    std::string whole_part = "";
    std::string decimal_part = "";
    size_t decimal_pos = expression.find('.');

    if (decimal_pos != std::string::npos) {
        whole_part = expression.substr(start_index, decimal_pos - start_index);
        decimal_part = expression.substr(decimal_pos + 1);
    } else {
        whole_part = expression.substr(start_index);
    }

    double result = 0.0;
    for (char c : whole_part) {
        result = result * 10 + (c - '0');
    }

    double decimal_value = 0.0;
    double place_value = 0.1;
    for (char c : decimal_part) {
        decimal_value += (c - '0') * place_value;
        place_value *= 0.1;
    }

    result += decimal_value;

    if (is_negative) {
        result = -result;
    }

    return result;
}
bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}
bool isValidDouble(const std::string &expression)
{
    bool signPresent = false;
    bool decimalPresent = false;
    bool digitPresent = false;

    for (size_t i = 0; i < expression.size(); i++)
    {
        char c = expression[i];
        if (c == '+' || c == '-')
        {
            if (i != 0 || signPresent) return false;
            signPresent = true;
        }
        else if (c == '.')
        {
            if (decimalPresent || i == 0 || i == expression.size() - 1) return false;
            decimalPresent = true;
        }
        else if (isDigit(c))
        {
            digitPresent = true;
        }
        else
        {
            return false;
        }
    }
    return digitPresent;
}
std::string add(const std::string a, const std::string b)
{
    bool negative_a = a[0] == '-';
    bool negative_b = b[0] == '-';

    std::string val_a = negative_a ? a.substr(1) : a;
    std::string val_b = negative_b ? b.substr(1) : b;

    if (negative_a && negative_b)
    {
        std::string result = add(val_a, val_b);
        return "-" + result;
    }
    else if (negative_a && !negative_b)
    {
        if (val_b == val_a || val_b < val_a)
        {
            return subtract(val_b, val_a);
        }
        else
        {
            return "-" + subtract(val_a, val_b);
        }
    }
    else if (!negative_a && negative_b)
    {
        if (val_a == val_b || val_a > val_b)
        {
            return subtract(val_a, val_b);
        }
        else
        {
            return "-" + subtract(val_b, val_a);
        }
    }
    std::pair<std::string, std::string> parsed_a = parse_num(a);
    std::pair<std::string, std::string> parsed_b = parse_num(b);

    std::string whole_a = parsed_a.first;
    std::string decimal_a = parsed_a.second;
    std::string whole_b = parsed_b.first;
    std::string decimal_b = parsed_b.second;

    while (decimal_a.size() < decimal_b.size()) decimal_a += '0';
    while (decimal_b.size() < decimal_a.size()) decimal_b += '0';

    std::string decimal_sum = "";
    int carry = 0;
    for (int i = decimal_a.size() - 1; i >= 0; i--)
    {
        int digit_sum = (decimal_a[i] - '0' + decimal_b[i] - '0') + carry;
        carry = digit_sum / 10;
        decimal_sum.insert(decimal_sum.begin(), (digit_sum % 10) + '0');
    }

    std::string whole_sum = "";
    int index_a = whole_a.size() - 1;
    int index_b = whole_b.size() - 1;
    while (index_a >= 0 || index_b >= 0 || carry > 0)
    {
        int digit_a = (index_a >= 0) ? (whole_a[index_a--] - '0') : 0;
        int digit_b = (index_b >= 0) ? (whole_b[index_b--] - '0') : 0;
        int digit_sum = digit_a + digit_b + carry;
        carry = digit_sum / 10;
        whole_sum.insert(whole_sum.begin(), (digit_sum % 10) + '0');
    }
    return whole_sum + "." + decimal_sum;
}

std::string subtract(const std::string a, const std::string b)
{
    bool negative_a = !a.empty() && a[0] == '-';
    bool negative_b = !b.empty() && b[0] == '-';

    if (negative_a && negative_b) {
        return subtract(b.substr(1), a.substr(1));
    } else if (negative_a && !negative_b) {
        return "-" + add(a.substr(1), b);
    } else if (!negative_a && negative_b) {
        return add(a, b.substr(1));
    }

    std::pair<std::string, std::string> parsed_a = parse_num(a);
    std::pair<std::string, std::string> parsed_b = parse_num(b);

    std::string whole_a = parsed_a.first;
    std::string decimal_a = parsed_a.second;
    std::string whole_b = parsed_b.first;
    std::string decimal_b = parsed_b.second;

    while (decimal_a.size() < decimal_b.size()) decimal_a += '0';
    while (decimal_b.size() < decimal_a.size()) decimal_b += '0';

    std::string decimal_result = "";
    int borrow = 0;
    for (int i = decimal_a.size() - 1; i >= 0; --i) {
        int digit_a = decimal_a[i] - '0';
        int digit_b = decimal_b[i] - '0';

        digit_a -= borrow;
        if (digit_a < digit_b) {
            digit_a += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        decimal_result.insert(decimal_result.begin(), (digit_a - digit_b) + '0');
    }

    std::string whole_result = "";
    int index_a = whole_a.size() - 1;
    int index_b = whole_b.size() - 1;
    while (index_a >= 0 || index_b >= 0 || borrow > 0) {
        int digit_a = (index_a >= 0) ? (whole_a[index_a--] - '0') : 0;
        int digit_b = (index_b >= 0) ? (whole_b[index_b--] - '0') : 0;

        digit_a -= borrow;
        if (digit_a < digit_b) {
            digit_a += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        whole_result.insert(whole_result.begin(), (digit_a - digit_b) + '0');
    }

    while (!whole_result.empty() && whole_result[0] == '0') {
        whole_result.erase(whole_result.begin());
    }

    if (whole_result.empty()) whole_result = "0"; 
    return whole_result + "." + decimal_result;
    
}

std::string multiply(const std::string a, const std::string b)
{
    std::string product = "0";
    std::pair<std::string, std::string> parsed_b = parse_num(b);
    std::string whole_b = parsed_b.first;
    std::string decimal_b = parsed_b.second;

    for (std::string i = "0"; i != whole_b; i = add(i, "1"))
    {
        product = add(product, a);
    }
    return product;
}
