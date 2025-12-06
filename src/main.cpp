#include <iostream>

#include "CampusCompass.h"
#include "Parser.h"

using namespace std;

int main() {
    // initialize your main project object
    CampusCompass compass;
    Parser parser;

    // ingest CSV data
    parser.parseCSV("../data/edges.csv", "../data/classes.csv", compass);

    // the below is example code for parsing commandline input
    int no_of_lines;
    string command;
    cin >> no_of_lines;
    cin.ignore(); // ignore newline that first cin left over
    for (int i = 0; i < no_of_lines; i++) {
        getline(cin, command);
        // parse your commands however you see fit
        int validity = parser.parseCommand(command, compass, false);
        if (validity == 0) {
            cout << "unsuccessful" << endl;
        }
        else if (validity == 1) {
            cout << "successful" << endl;
        }
    }
}
