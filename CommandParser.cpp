#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "CommandParser.h"
using namespace std;

CommandLine* CommandParser::fetchCommand(){
    string str;
    getline(cin, str);
    if (str.empty()) {
        return nullptr;
    }

    vector<string> line = seperate(str, ' ');
    vector<string> parameters(line.begin() + 1, line.end());

    return new CommandLine(line[0], parameters);
}

vector<string> CommandParser::seperate(const string& str2, char chars){
    vector<string> elements;
    stringstream iss(str2);
    string str3;
    while (getline(iss, str3, chars)) {
        if (!str3.empty()) {
            elements.push_back(str3);
        }
    }
    return elements;
}