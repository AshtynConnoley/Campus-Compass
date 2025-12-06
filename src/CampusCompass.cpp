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

bool CampusCompass::isConnected(string location1, string location2) {
    std::unordered_set<int> visited;
    std::queue<int> q;
    q.push(stoi(location1));
    visited.insert(stoi(location1));

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (curr == stoi(location2)) {
            return true;
        }

        for (auto edge : edges) {
            if ((edge[0] == curr && visited.find(edge[1]) == visited.end()) && edge[3] == true) {
                q.push(edge[1]);
                visited.insert(edge[1]);
            }
            else if (edge[1] == curr && visited.find(edge[0]) == visited.end() && edge[3] == true) {
                q.push(edge[0]);
                visited.insert(edge[0]);
            }
        }
    }
    return false;
}

pair<int, vector<int>> CampusCompass::dijkstra(int start, int end) {

    unordered_map<int, int> dist;
    for (auto &item : locations) {
        dist[item.first] = INT_MAX; // Set to max to relax later
    }
    dist[start] = 0;

    unordered_map<int, int> parent;
    parent[start] = -1; // Initial node


    // Asked GPT 5.0 "How can I set up a priority queue to use with dijkstra's algorithm"
    // Used its advice on making node and comparison operator structures as seen below.
    struct Node { int length, locationID; };
    struct Comparison { bool operator()(const Node &a, const Node &b) const { return a.length > b.length; } };

    priority_queue<Node, vector<Node>, Comparison> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int totalLength = pq.top().length;
        int locationID = pq.top().locationID;
        pq.pop();

        // If we've found a better path then the one currently on top of queue, then we ignore top of queue
        if (totalLength != dist[locationID]) {
            continue;
        }

        if (locationID == end) {
            break;
        }

        for (const auto &edge : edges) {
            if (edge[3] == false) { // Closed path
                continue;
            }

            // The two relaxation cases
            if (edge[0] == locationID) {
                int edgeLength = edge[2];
                if (dist[locationID] + edgeLength < dist[edge[1]]) { // Replace if better
                    dist[edge[1]] = dist[locationID] + edgeLength;
                    parent[edge[1]] = locationID;
                    pq.push({dist[edge[1]], edge[1]});
                }
            }
            else if (edge[1] == locationID) {
                int edgeLength = edge[2];
                if (dist[locationID] + edgeLength < dist[edge[0]]) { // Replace if better
                    dist[edge[0]] = dist[locationID] + edgeLength;
                    parent[edge[0]] = locationID;
                    pq.push({dist[edge[0]], edge[0]});
                }
            }
        }
    }

    if (dist[end] == INT_MAX)
        return { -1, {} };

    // Need to keep track of path taken for the purpose of printStudentZone
    vector<int> path;
    for (int curr = end; curr != -1; curr = parent[curr]) // Iterate backwards through path taken to destination
        path.push_back(curr);
    reverse(path.begin(), path.end()); // Order nodes correctly

    return { dist[end], path };
}

vector<pair<string, int>> CampusCompass::printShortestEdges(int ID) { // Make sure to sort classes
    Student* student = students[ID];
    int start = stoi(student->locationID);

    vector<pair<string, int>> result;

    vector<string> classes = student->classes;
    sort(classes.begin(), classes.end()); // Sort for printing

    for (string& item : classes) {

        int locationID = classList[item]; // Already made sure classes existed when they were inserted
        pair<int, vector<int>> shortest = dijkstra(start, locationID);
        result.push_back({item, shortest.first});
    }

    // Do printing here since we already have access to the name
    cout << "Name: " << student->name << endl;
    for (auto &item : result) {
        cout << item.first << " | Total Time: " << item.second << endl;
    }

    return result; // For potential testing
}

bool CampusCompass::printStudentZone(int ID) {
    if (students.find(ID) == students.end()) {
        return false;
    }

    Student* student = students[ID];
    int start = stoi(student->locationID);
    unordered_set<int> accessedNodes;

    for (string& item : student->classes) {
        int locationID = classList[item];
        pair<int, vector<int>> shortest = dijkstra(start, locationID); // Returns -1 if inaccessable
        if (shortest.first == -1) {
            continue;
        }
        vector<int> path = shortest.second;

        for (int node : path) {
            if (accessedNodes.find(node) == accessedNodes.end()) {
                accessedNodes.insert(node);
            }
        }
    }

    // Need subgraph of the accessed edges
    vector<vector<int>> subEdges;  // subEdges = e1, e2, length. Will filter out accessibility now.
    for (auto &edge : edges) {
        if (edge[3] == false) continue; // Accessibility check

        if (accessedNodes.count(edge[0]) > 0 && accessedNodes.count(edge[1]) > 0) {
            vector<int> validEdge = {edge[0], edge[1], edge[2]};
            subEdges.push_back(validEdge);
        }
    }

    // Need edges in ascending order
    sort(subEdges.begin(), subEdges.end(),
     [](auto &a, auto &b) {return a[2] < b[2];});


    // Union set approach to Kruskals
    unordered_map<int,int> parent;
    for (int vertex : accessedNodes) {
        parent[vertex] = vertex; // All nodes are in their own sets
    }

    auto getParent = [&](int vertex) { // Finds parent of the set the vertex is in
        while (parent[vertex] != vertex) {
            vertex = parent[vertex];
        }
        return vertex;
    };

    auto unite = [&](int vertex1, int vertex2) { // Adds vertex2 to vertex1's set
        int parent1 = getParent(vertex1);
        int parent2 = getParent(vertex2);
        if (parent1 != parent2) {
            parent[parent1] = parent2;
        }
    };

    int cost = 0;
    for (auto &edge : subEdges) {
        if (getParent(edge[0]) != getParent(edge[1])) { // Cycle detection
            unite(edge[0], edge[1]); // Now part of same set
            cost += edge[2];
        }
    }

    cout << "Student Zone Cost For " << student->name << ": " << cost << "\n";
    return true;
}





