#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <string>
#include <vector>
using namespace std;

class CommandLine {
  public: 
   CommandLine(string& command, vector<string> params);

   ~CommandLine(){};

    string getCommand();
    vector<string> getParams();
    string toString(); 

  private:
    string command;
    vector<string> params;
};

#endif