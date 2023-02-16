#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include "CommandLine.h"
using namespace std;

class CommandParser {
  public: 
    CommandLine* fetchCommand();

  private:
    vector<string> seperate(const string& str, char chars);
};

#endif