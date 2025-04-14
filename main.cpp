#include <fstream>
#include <iostream>
#include "calculator.hpp"


const std::string number_to_add = "-123.456";

int main(int argc, char *argv[]) {
    std::ifstream file;
    std::string filename;
    
    std::cout << "Enter the filename: "; // ask user for file name
    std::cin >> filename;

    file.open(filename); // try to open file, may not be open
    
    if (!file.is_open()) { // couldnt open file for some reason? is it the right file? does it exist? who cares let the user find out!
        std::cerr << "Failed to open file: " << filename << std::endl; // tell our user we couldnt do jack
        return 1; // cancel program
    }
    
    std::string number; // number buffer
    while (std::getline(file, number)) { // start reading the program line by line
        // Try to add number to number_to_add;
        std::cout << "Tring to add (" << number_to_add << ") with (" << number << ")..." << std::endl;  // Output result of addition!
        std::string number_result = add_numbers(number_to_add, number);

        if (number_result.empty()) { // Couldn't get a result
            std::cerr << "\tFailed to add numbers! Moving on to next line" << std::endl << std::endl; // Tell our user we failed then move on.
            continue;
        }

        std::cout << "\t(" << number_to_add << ") + (" << number << ") = " << number_result << std::endl << std::endl;  // Output result of addition!
    }

}
