#include "grep.hpp"

void printhelp(){
    cout << "usage: grep [-abcdDEFGHhIiJLlMmnOopqRSsUVvwXxZz] [-A num] [-B num] [-C[num]]" << endl;
    cout << "\t[-e pattern] [-f file] [--binary-files=value] [--color=when]" << endl;
    cout << "\t[--context[=num]] [--directories=action] [--label] [--line-buffered]" << endl;
    cout << "\t[--null] [pattern] [file ...]" << endl;
}
bool matchAnyPattern(const string& line, const vector<regex> & patterns, bool invert){
    bool matched = false;
    for (const auto& pattern : patterns) {
        if (regex_search(line, pattern)) {
            matched = true;
            break;
        }
    }
    return invert ? !matched : matched;

}
void processGrep(istream& input, const flags& flags, const string& filename, int &TotalFilesWithMatches, vector<string>&matchingFiles){
    string line;
    int linenum = 0;
    int matchcount = 0;
    size_t byteOffset = 0;
    bool fileHasMatches = false;
    vector<regex> compiledPatterns;
    regex_constants::syntax_option_type regexFlags = regex::basic;
    regex somepattern;
    for (const string& pattern : flags.patterns){
        string finalPattern = pattern;
        if (flags.w && !flags.x) {
            finalPattern = "\\b" + finalPattern + "\\b";
            } else if (flags.x && !flags.w) {
            finalPattern = "^" + finalPattern + "$";
            } else if (flags.w && flags.x) {
               finalPattern = "^" + finalPattern + "$"; 
            }
            regex_constants::syntax_option_type regexFlags = regex::ECMAScript;
            if (flags.i) regexFlags |= regex::icase;

        try {
            compiledPatterns.emplace_back(finalPattern, regexFlags);
        }catch (const regex_error & err) {
            cerr << "invalid expression" << err.what() << endl;
            exit(1);
        }

    }
    while (getline(input, line)) {
        linenum++;
        bool match = matchAnyPattern(line, compiledPatterns, flags.v);
        if (match) {
            fileHasMatches = true;
             matchcount++;
             if (flags.c || flags.l) continue;
             if ((flags.files.size() > 1 || flags.r || flags.H) && !flags.h) {
                cout << filename << ":";
             }
             if (flags.n) {
                cout << linenum << ":";
             } 
             if (flags.b) {
                cout << byteOffset << ":";
             }
             if (!flags.c && !flags.l){
                cout << line << endl;
             }
             
        }
        byteOffset += line.size() + 1;
    }
    if (flags.n) {
        if ((flags.files.size() > 1 || flags.h) && !flags.h) {
            cout << filename << ":";

        }
    } else if (flags.l && matchcount > 0 && !flags.c) {
        cout << filename << endl;
    }
    if (fileHasMatches) {
        TotalFilesWithMatches++;
        matchingFiles.push_back(filename);
    }
    if (flags.c && !flags.l) {
        if ((flags.files.size() > 1 || flags.H)) {
            cout << filename << ":";
        }
        cout << matchcount << endl;
        return;
    }

}

int main(int argc, char* argv[]){
    int totalFilesWithMatches = 0;
    vector<string> matchingFiles;
    flags flags;
    bool patternexpected = false;
    for (int i = 1; i < argc; i++){
        string arg = argv[i];
        if (arg == "--help") {
            printhelp();
            exit(0);
        }
        if (patternexpected) {
            flags.patterns.push_back(arg);
            patternexpected = false;
            continue;
        }
        if (arg == "-e" || arg == "--regexp") {
            patternexpected = true;

        } else if (arg == "-i" || arg == "--ignore-case") {
            flags.i = true;
        } else if (arg == "-v" || arg == "--invert-match") {
            flags.v = true;
        } else if (arg == "-c" || arg == "--count") {
            flags.c = true;
        } else if (arg == "-l" || arg == "--files-with-matches") {
            flags.l = true;
        } else if (arg == "-n" || arg == "--line-number") {
            flags.n = true;
        } else if (arg == "-w" || arg == "--word-regexp") {
            flags.w = true;
        } else if (arg == "-x" || arg == "--line-regexp") {
            flags.x = true;
        } else if (arg == "-r" || arg == "--recursive") {
            flags.r = true;
        } else if (arg == "-h" || arg == "--no-filename") {
            flags.h = true;
        } else if (arg == "-H" || arg == "--with-filename"){
            flags.H = true;
        } else if (arg == "-b" || arg == "--byte-offset") {
            flags.b = true;
        } else if (arg == "--help") {
            flags.help = true;
        } else if (arg[0] == '-') {
            cerr << "invalid option" << arg << endl;
            return 1;
        } else {
            if (flags.patterns.empty()) {
                flags.patterns.push_back(arg);
            } else flags.files.push_back(arg);
        }
    } 
    if (patternexpected && !flags.help) {
        cerr << "option reqired an argument";
        return 1;
    }
    if (flags.patterns.empty() && !flags.help) {
        cerr << "reqires a pattern";
    }
    if (flags.files.empty() && !flags.help) {
        processGrep(cin, flags, "(standard input)", totalFilesWithMatches, matchingFiles);
        return 0;
    }
    if (!flags.help){
        for (const string & filename : flags.files) {
            if (filename == "-") {
                processGrep(cin, flags, "(standard input)", totalFilesWithMatches, matchingFiles);
            } else {
                ifstream file(filename);
                if (!file) {
                    cerr << "grep: " << filename << ": no such file or directory\n";
                    continue;
                }
                processGrep(file, flags, filename, totalFilesWithMatches, matchingFiles);
                file.close();
            }
        }
    }
    if (flags.l && flags.c) {
        cout << totalFilesWithMatches << endl;
        for (const auto& file : matchingFiles) {
            cout << file << endl;
        }
    }
    return 0;
}