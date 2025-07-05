#ifndef _GREP_HPP_
#define _GREP_HPP_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
using namespace std;
struct flags {
bool i = false; //ignore case
bool c = false; // count
bool v = false; // invert search
bool l = false; // show files with matches
bool n = false; // with line number
bool w = false; // word regex
bool x = false; // line regex
bool r = false; // recursive
bool h = false; // no filename
bool H = false; // with filename
bool b = false; // byte offset
bool help = false;
vector<string> patterns;
vector<string> files;

};

void printhelp();
bool matchAnyPattern(const string& line, const vector<regex> & patterns, bool invert);
void processGrep(istream& input, const flags& flags, const string& filename, int &TotalFilesWithMatches, vector<string>&matchingFiles);
#endif