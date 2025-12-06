
#include "Parser.h"


bool Parser::parseCSV(const string &edgeFile, const string &classFile, CampusCompass& compass) {
    string line;
    ifstream file = ifstream(edgeFile, ifstream::in);
    if (!file.is_open()) {
        cout << "Error opening file " << edgeFile << endl;
        return false;
    }
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        getline(ss, cell, ',');
        int vertex1 = stoi(cell);
        getline(ss, cell, ',');
        int vertex2 = stoi(cell);
        getline(ss, cell, ',');
        if (compass.locations.find(vertex1) == compass.locations.end()) {
            compass.locations.insert({vertex1, cell});
        }
        getline(ss, cell, ',');
        if (compass.locations.find(vertex2) == compass.locations.end()) {
            compass.locations.insert({vertex2, cell});
        }
        getline(ss, cell, ',');
        int distance = stoi(cell);
        compass.edges.push_back({vertex1, vertex2, distance, 1}); // Last int signals if the road is available
    }
    file.close();


    file = ifstream(classFile, ifstream::in);
    if (!file.is_open()) {
        cout << "Error opening file " << edgeFile << endl;
        return false;
    }
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        string code;
        getline(ss, code, ',');
        getline(ss, cell, ',');
        compass.classList[code] = stoi(cell);
        getline(ss, cell, ',');
        // int time1 = stoi(cell);
        getline(ss, cell, ',');
        // int time2 = stoi(cell);

    }
    file.close();

    return true;
}

int Parser::parseCommand(const string &command, CampusCompass& compass, bool isTest) {
    // This function returns true, false, -1 if success/fail has already been dealt with, or an int for removeClass
    stringstream ss(command);
    string word;
    ss >> word;

    if (word == "insert") {
        string name;
        ss >> name;
        bool isValid = nameCheck(name);
        if (!isValid) {
            return false;
        }

        ss >> word;
        isValid = IDCheck(word);
        if (!isValid) {
            return false;
        }
        int ID = stoi(word);

        ss >> word;
        if (compass.locations.find(stoi(word)) == compass.locations.end()) {
            return false;
        }
        string locationID = word;

        int numClasses;
        ss >> numClasses;
        if (numClasses > 6 || numClasses < 1) {
            return false;
        }

        vector<string> classes;
        int counter = 0;
        while (ss >> word) {
            isValid = classCheck(word);
            if (!isValid) {
                return false;
            }
            classes.push_back(word);
            counter++;
        }
        if (counter != numClasses) {
            return false;
        }

        if (!isTest) {
            isValid = compass.insert(name, ID, locationID, classes);
            return isValid;
        }

        return true;
    }

    else if (word == "remove") {
        ss >> word;
        bool isValid = IDCheck(word);
        if (!isValid) {
            return false;
        }
        if (!isTest) {
            isValid = compass.remove(stoi(word));
            return isValid;
        }
        return true;
    }

    else if (word == "dropClass") {
        ss >> word;
        bool isValid = IDCheck(word);
        if (!isValid) {
            return false;
        }
        int ID = stoi(word);

        ss >> word;
        isValid = classCheck(word);
        if (!isValid) {
            return false;
        }

        if (!isTest) {
            isValid = compass.dropClass(ID, word);
            return isValid;
        }
        return true;
    }

    else if (word == "replaceClass") {
        ss >> word;
        bool isValid = IDCheck(word);
        if (!isValid) {
            return false;
        }
        int ID = stoi(word);

        ss >> word;
        isValid = classCheck(word);
        if (!isValid) {
            return false;
        }
        string class1 = word;

        ss >> word;
        isValid = classCheck(word);
        if (!isValid) {
            return false;
        }

        if (!isTest) {
            isValid = compass.replaceClass(ID, class1, word);
            return isValid;
        }

        return true;
    }

    else if (word == "removeClass") {
        ss >> word;
        bool isValid = classCheck(word);
        if (!isValid) {
            return false;
        }
        if (!isTest) {
            int result;
            result = compass.removeClass(word);
            return result;
        }
        return true;
    }

    else if (word == "toggleEdgeClosure") {
        int numEdges;
        ss >> numEdges;
        int counter = 0;
        while (ss >> word) {
            string vertex1 = word;
            ss >> word;
            bool isValid = compass.toggleEdgeClosure(vertex1, word);
            if (!isValid) {
                return false;
            }
            counter += 1;
        }
        if (counter != numEdges) {
            return false;
        }
        return true;
    }

    else if (word == "checkEdgeStatus") {
        string vertex1;
        ss >> vertex1;
        ss >> word;
        int result = compass.checkEdgeStatus(vertex1, word);
        if (result == 1) {
            cout << "open" << endl;
        }
        else if (result == 0) {
            cout << "closed" << endl;
        }
        else if (result == -1) {
            cout << "DNE" << endl;
        }
        return -1;

    }

    else if (word == "isConnected") {
        string vertex1;
        ss >> vertex1;
        ss >> word;
        bool isValid = compass.isConnected(vertex1, word);
        return isValid;
    }

    else if (word == "printShortestEdges") {
        ss >> word;
        bool isValid = IDCheck(word);
        if (!isValid) {
            return false;
        }
        int ID = stoi(word);
        if (!isTest) {
            compass.printShortestEdges(ID);
        }
        return -1;
    }

    else if (word == "printStudentZone") {
        ss >> word;
        bool isValid = IDCheck(word);
        if (!isValid) {
            return false;
        }
        int ID = stoi(word);
        if (!isTest) {
            compass.printStudentZone(ID);
        }
        return -1;
    }

    else {
        return false;
    }
}

bool Parser::IDCheck(string ID) {
    if (!regex_match(ID, regex("^[0-9]{8,8}$"))) {
        return false;
    }
    return true;
}

bool Parser::nameCheck(string& name) {
    if (name[0] != '"' || name[name.size() - 1] != '"') {
        return false;
    }
    name = name.substr(1, name.size() - 2);
    if (!regex_match(name, regex("^[A-Za-z ]+$"))) {
        return false;
    }
    return true;
}

bool Parser::classCheck(string classCode) {
    if (classCode.length() != 7) {
        return false;
    }
    string letters = classCode.substr(0, 3);
    string numbers = classCode.substr(3, 4);
    if (!regex_match(letters, regex("^[A-Z]{3}$"))) {
        return false;
    }
    if (!regex_match(numbers, regex("^[0-9]{4}$"))) {
        return false;
    }
    return true;
}