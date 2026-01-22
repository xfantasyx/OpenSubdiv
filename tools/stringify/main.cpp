//
//   Copyright 2013 Pixar
//
//   Licensed under the terms set forth in the LICENSE.txt file available at
//   https://opensubdiv.org/license.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


std::string stringify( std::string const & s ) {

    bool withinStringConstant = false;
    std::string result = "";
    

    for (int i = 0; i < (int)s.length() - 1; ++i) 
    {
        // escape double quotes
        if (s[i] == '"') 
        {
            result += '\\';
            withinStringConstant = !withinStringConstant;
        }

        if (s[i] == '\\' && i == (int)s.length() - 2) 
        {
            return result + "\"";
        }

        // escape backslash
        if (withinStringConstant && s[i] == '\\') 
        {
            result += '\\';
        }

        result += s[i];
    }


    return result + "\\n\"";

}

int main(int argc, char **argv) {

    if (argc != 3) {
        std::cerr << "Usage: stringify input-file output-file" << std::endl;
        return 1;
    }

    std::ifstream input;
    input.open(argv[1]);
    if (! input.is_open()) {
        std::cerr << "Can not read from: " << argv[1] << std::endl;
        return 1;
    }

    std::ofstream output;
    output.open(argv[2]);
    if (! output.is_open()) {
        std::cerr << "Can not write to: " << argv[2] << std::endl;
        return 1;
    }

    std::string line;

    while (! input.eof()) {
        std::getline(input, line);
        output << "\"" << stringify(line) << std::endl;
    }

    return 0;
}
