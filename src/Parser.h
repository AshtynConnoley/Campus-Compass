#ifndef PARSING_H
#define PARSING_H

#include "Graph.h"
#include <regex>
#include <string>
struct Parser {
public:
    bool parseCSV(const string &edgeFile, const string &classFile, Graph& compass);
    int parseCommand(const string &command, Graph& compass, bool isTest);
    bool IDCheck(string ID);
    bool nameCheck(string& name);
    bool classCheck(string className);
};


#endif
