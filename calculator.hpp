#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP

#include <string>

struct ParsedNumber {
    bool isValid; // if this is false, then all the result of the data doesnt even matter
    bool isNegative; // True if negative
    std::string main; // Main part of the number
    std::string fraction; // Part of the number beyond floating point
};

// Default invalid parsed number so we don't have to create a new one every time something screws up!
const ParsedNumber PARSED_NUMBER_INVALID = ParsedNumber{false, 0, "", ""};


// this function should expect that `expression` has already been
// validated and thus throw no exceptions
double parse_number(const std::string &expression);

// Helper functiosns
std::string add_numbers(const std::string& operand1, const std::string& operand2);
ParsedNumber extract_valid_number(const std::string &number);


#endif // __CALCULATOR_HPP
