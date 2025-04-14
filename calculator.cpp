#include "calculator.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <cctype>

// this function should expect that `expression` has already been
// validated and thus throw no exceptions
double parse_number(const std::string &expression) {
    ParsedNumber result = extract_valid_number(expression);

    int sign = result.isNegative ? -1 : 1; // sign of number

    int main = (std::stoi(result.main) * sign); // Get main component

    int fractionalLength = result.fraction.length(); // Get fractional component length

    int fractional = (
        std::stoi(result.fraction) * // get the fractioanl content. some number like 0002, or 02, or 120 or such.
        sign * // multiply it by the sigm
        std::pow(10, fractionalLength - result.fraction.length() // take 10^(fractional_max_length - this_length) so that we can add the fraction and get meaningful result
    )); // get fractional 

    int total = 0;
    total += main * 10^(fractionalLength + 1); // Add the main component sum, taken to the power of the fractional length plus one so that add everything together
    total += fractional; // Add fractional component to sum

    double large_result = static_cast<double>(total);
    return large_result/(10^(fractionalLength));
}


ParsedNumber extract_valid_number(const std::string& number) {
    if (number.empty()) return PARSED_NUMBER_INVALID; // it's empty

    size_t i = 0; // Track where we are in the number
    bool isNegative = false; // Tracks if the number is negative
    
    // Ignore sign stuff
    if (number[i] == '+') {
        i++;
    } else if (number[i] == '-') {
        isNegative = true; // Register that our number is negative as per sign
        i++;
    }

    bool hasDigit = false; // We need to make sure we have a digit!
    
    // Check for integer part
    std::string main = "";
    while (i < number.size() && std::isdigit(number[i])) { // Iterate through integer/main part of number

        // Collect integer digits
        hasDigit = true;
        main += number[i];

        i++;
    }
    if (!hasDigit) {
        // std::cerr << "Couldn't find digit for integer component" << std::endl;
        return PARSED_NUMBER_INVALID; // Needs to have a digit by now
    }


    // Check for decimal point
    if (i == number.size()) return ParsedNumber {true, isNegative, main, "0"}; // Just an integer, with maybe a sign
    if (number[i] == '.') { // Floating point
        i++; // Skip the floating point

        // Check for fractional part
        bool hasFloating = false;

        std::string fraction = "";
        while (i < number.size()) { // Iterate through digits after floating point
            if (!std::isdigit(number[i])) {
        //         std::cerr << "Found non-digit in floating point component!" << std::endl;
                return PARSED_NUMBER_INVALID; // Found a non-digit? This shouldn't happen!
            }

            // Collect fraction digits
            hasFloating = true;
            fraction += number[i];

            i++;
        }

        if (!hasFloating || i != number.size()) {
        //     std::cerr << "Couldn't finalize floating point component" << std::endl;
            return PARSED_NUMBER_INVALID; // No fractional part but we have a floating point??
        }
        
        return ParsedNumber {true, isNegative, main, fraction};
    } else {
        // std::cerr << "Has extra characters beyond main integer component that are not part of floating point!" << std::endl;
        return PARSED_NUMBER_INVALID; // Bigger than just the first integer part, but doesn't have a floating point?
    }
}

std::string add_numbers(const std::string& operand1, const std::string& operand2) {
    // Extract parsed numbers from strings (mostly just splits up the strings and verifies they're correct).
    ParsedNumber parsed1 = extract_valid_number(operand1);
    ParsedNumber parsed2 = extract_valid_number(operand2);
    std::cout << parsed1.main << "." << parsed1.fraction << std::endl;

    // Verify that our values actually parsed successfully 
    if (!parsed1.isValid) {
        std::cerr << "\tLHS operand from sum did not parse correctly" << std::endl;
        return "";
    } else if (!parsed2.isValid) {
        std::cerr << "\tRHS operand from sum did not parse correctly" << std::endl;
        return "";
    }

    // Get signage of numbers
    int sign1 = parsed1.isNegative ? -1 : 1;
    int sign2 = parsed2.isNegative ? -1 : 1;

    int mainSum = (std::stoi(parsed1.main) * sign1) + (std::stoi(parsed2.main) * sign2); // Add main integer components, multiply the contents by the sign found.

    int fractionalMaxLength = std::max(parsed1.fraction.length(), parsed2.fraction.length()); // Calculate what the largest fractional component (in length) is of the two numbers.

    int fractional1 = (
        std::stoi(parsed1.fraction) * // get the fractioanl content. some number like 0002, or 02, or 120 or such.
        sign1 * // multiply it by the sigm
        std::pow(10, fractionalMaxLength - parsed1.fraction.length() // take 10^(fractional_max_length - this_length) so that we can add the fractions and get meaningful results
    )); // get fractional 1
    int fractional2 = (
        std::stoi(parsed2.fraction) * // get the fractioanl content. some number like 0002, or 02, or 120 or such.
        sign2 * // multiply it by the sigm
        std::pow(10, fractionalMaxLength - parsed2.fraction.length() // take 10^(fractional_max_length - this_length) so that we can add the fractions and get meaningful results
    )); // get fractional 1


    int total = 0;
    total += mainSum * std::pow(10, fractionalMaxLength); // Add the main component sum, taken to the power of the fractional length plus one so that add everything together
    total += fractional1 + fractional2; // Add fractional components together in a sum and add that to the total as well.

    // Total is now (likely) a much larger number than the double it is being met to represent. We have to turn it into a string and add the decimal point!

    std::string totalString = std::to_string(total); // Total, stringified.
    int decimalPointLocation = totalString.length() - fractionalMaxLength; // We have to move from the back of the string because the front could be any arbitrary size!
    
    totalString.insert(decimalPointLocation, "."); // Add decimal point at the location we found for it!

    return totalString;
}

