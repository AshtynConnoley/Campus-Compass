#include "CampusCompass.h"


using namespace std;

CampusCompass::CampusCompass() {
    // initialize your object
}
CampusCompass::Student::Student(int ID, string name, string locationID, vector<string> classes) {
    this->ID = ID;
    this->name = name;
    this->locationID = locationID;
    this->classes = classes;
}

CampusCompass::~CampusCompass() {
    for (auto item : students) {
        delete item.second;
    }
}

string CampusCompass::getStudentName(int ID) {
    return students[ID]->name;
}

bool CampusCompass::parseCSV(const string &edgeFile, const string &classFile) {
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
        int e1 = stoi(cell);
        getline(ss, cell, ',');
        int e2 = stoi(cell);
        getline(ss, cell, ',');
        if (locations.find(e1) != locations.end()) {
            locations.insert({e1, cell});
        }
        getline(ss, cell, ',');
        if (locations.find(e2) != locations.end()) {
            locations.insert({e2, cell});
        }
        getline(ss, cell, ',');
        int distance = stoi(cell);
        edges.push_back({e1, e2, distance, 1}); // Last int signals if the road is available
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
        classList[code] = stoi(cell);
        getline(ss, cell, ',');
        // int time1 = stoi(cell);
        getline(ss, cell, ',');
        // int time2 = stoi(cell);

    }
    file.close();

    return true;
}

bool CampusCompass::parseCommand(const string &command) {
    stringstream ss(command);
    string word;
    ss >> word;
    if (word == "insert") {}
    else if (word == "remove") {}
    else if (word == "dropClass") {}
    else if (word == "replaceClass") {}
    else if (word == "removeClass") {}
    else if (word == "toggleEdgeClosure") {}
    else if (word == "checkEdgeStatus") {}
    else if (word == "isConnected") {}
    else if (word == "printShortestEdges") {}
    else if (word == "printStudentZone") {}

    return false;
}

bool CampusCompass::insert(string name, int ID, string locationID, const vector<string>& classes) {
    if (students.find(ID) != students.end()) {
        return false;
    }
    for (auto item : classes) {
        if (classList.find(item) == classList.end()) {
            return false;
        }
    }
    students[ID] = new Student(ID, name, locationID, classes);
    return true;
}

bool CampusCompass::remove(int ID) {
    if (students.find(ID) == students.end()) {
        return false;
    }
    delete students[ID];
    students.erase(ID);
    return true;
}

bool CampusCompass::dropClass(int ID, const string& classCode) {
    if (students.find(ID) == students.end()) {
        return false;
    }
    Student* curr = students[ID];
    for (size_t i=0; i < curr->classes.size(); i++) {
        if (curr->classes[i] == classCode) {
            curr->classes.erase(curr->classes.begin() + i);
            if (curr->classes.size() == 0) {
                delete students[ID];
                students.erase(ID);
            }
            return true;
        }
    }
    return false;
}

bool CampusCompass::replaceClass(int ID, const string& classCode1, const string& classCode2) { // replace 1 with 2
    if (students.find(ID) == students.end()) { // student exists
        return false;
    }
    if (classList.find(classCode2) == classList.end()) {
        return false;
    }
    Student* curr = students[ID];
    for (auto item : curr->classes) { // doesn't already have class 2
        if (item == classCode2) {
            return false;
        }
    }
    for (auto& item : curr->classes) { // classes get switched
        if (item == classCode1) {
            item = classCode2;
            return true;
        }
    }
    return false;
}

int CampusCompass::removeClass(const string& classCode) {
    int count = 0;
    if (classList.find(classCode) == classList.end()) {
        return 0;
    }
    for (auto person : students) {
        for (size_t i = 0; i < person.second->classes.size(); i++) {
            if (person.second->classes[i] == classCode) {
                person.second->classes.erase(person.second->classes.begin() + i);
                if (person.second->classes.empty()) {
                    delete students[person.first];
                    students.erase(person.first);
                }
                count += 1;
            }
        }
    }
    classList.erase(classCode);
    return count;
}

bool CampusCompass::toggleEdgeClosure(const string& location1, const string& location2) {
    for (auto edge : edges) {
        if ((edge[0] == stoi(location1) && edge[1] == stoi(location2)) || edge[0] == stoi(location2) || edge[1] == stoi(location1)) {
            edge[3] == !edge[3];
            return true;
        }
    }
    return false;
}

int CampusCompass::checkEdgeStatus(const string& location1, const string& location2) {
    for (auto edge : edges) {
        if ((edge[0] == stoi(location1) && edge[1] == stoi(location2)) || (edge[0] == stoi(location2) && edge[1] == stoi(location1))) {
            return edge[3];
        }
    }
    return -1;
}

bool isConnected(string location1, string location2);

vector<pair<string, int>> printShortestEdges(int ID); // Make sure to sort classes

int minimumSpanningTree(vector<pair<int, int>> edges);


