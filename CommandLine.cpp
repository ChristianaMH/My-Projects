#include <vector>
#include <string>
#include <sstream>
#include "CommandLine.h" 

using namespace std;

// CHANGE UP

CommandLine::CommandLine(string& command, vector<string> params) {
  this->command = command;
  this->params = params;
}

string CommandLine::getCommand() {
  return command;
}

vector<string> CommandLine::getParams() {
  return params;
}

string CommandLine::toString() {
  stringstream stringBuffer;
  stringBuffer << "Command: " << command << "\n";
  for (int i = 0; i < params.size(); i++) {
    stringBuffer << "params[" << i << "] = " << params[i] << "\n";
  }

  return stringBuffer.str();
}