
#include "cat.hpp"

void processStream(istream& input, const CatFlags& flags) {
    string line;
    int lineNumber = 0;
    bool lastLineEmpty = false;
    
    while (true) {
        char c;
        line.clear();
    
        while (input.get(c) && c != '\n') {
            line += c;
        }
        
        if (line.empty() && input.eof()) break;
        
        bool isempty = line.empty();
        
        if (flags.s && isempty && lastLineEmpty) {
            continue;
        }
        lastLineEmpty = isempty;
        
        if (flags.b) {
            if (!isempty) cout << setw(6) << ++lineNumber << "\t";
        } else if (flags.n) {
            cout << setw(6) << ++lineNumber << "\t";
        }
        
        cout << line;
        
        if (flags.E && !(isempty && flags.s)) {
            cout << "$";
        }
        
        if (!input.eof()) {
            cout << "\n";
        }
        
        if (input.eof()) break;
    }
}

void printHelp(){
    cout << "cat: illegal option -- -" << endl;
    cout << "usage: cat [-belnstuv] [file ...]" << endl;
}
int main(int argc, char *argv[]){
    vector<string> files;
    CatFlags flags;
    for (int i = 1; i < argc; i++){
        string arg = argv[i];
        if (arg == "-E" || arg =="--show-ends") {
            flags.E = true;
        } else if (arg == "-b" || arg == "--number-nonblank") {
            flags.b = true;
        } else if (arg == "-n" || arg == "--number") {
            flags.n = true;
        } else if (arg == "-s" || arg == "--squeeze-blank") {
            flags.s = true;
        } else if (arg == "-t" || arg == "--show-tabs") {
            flags.T = true;
        } else if (arg == "-v" || arg == "--show-nonprinting") {
            flags.v = true;
        } else if (arg == "--help") {
            flags.help = true;
        } else if (arg[0] == '-') {
            cout << "cat: illegal option" << arg << endl;
            cout << "usage: cat [-belnstuv] [file ...]" << endl;
        } else {
            files.push_back(arg);
        }
    }
    if (flags.help) {
        printHelp();
        return 0;
    }
    if (files.empty()) {
        processStream(cin, flags);
    }
    for (const string& filename: files){
        if (filename == "-") {
            processStream(cin, flags);
        } else {
            ifstream file(filename);
            if (!file) {
                cerr << "cat:" << filename << ": no such file or directory\n";
                return 1;
            }
            processStream(file, flags);
            file.close();
        }
    }
    return 0;

}