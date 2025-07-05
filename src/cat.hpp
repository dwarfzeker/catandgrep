#ifndef _CAT_HPP_
#define _CAT_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
struct CatFlags {
    bool E = false; // show ends of lines 
    bool b = false; // number only not empty strings
    bool n = false; // number all strings
    bool s = false; // squeeze blanks
    bool T = false; // show tabs
    bool v = false; // show not printing symbols
    bool help = false; // show help
};

void processStream(istream& input, const CatFlags& flags);
void printHelp();

#endif