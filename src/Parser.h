#ifndef PARSING_H
#define PARSING_H

#include <campusCompass.h>
#include <regex>
class Parser {
public:
    bool parseCSV(const string &edges_filepath, const string &classes_filepath, CampusCompass& compass);
    bool parseCommand(const string &command, bool isTest);
};


#endif
