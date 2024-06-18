#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <climits>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <cctype>
using namespace std;

class Edge {
public:
    string from;
    string to;
    int weight;

    Edge(const string& from, const string& to, int weight)
        : from(from), to(to), weight(weight) {}
};

class Graph {
public:
    unordered_map<string, vector<Edge>> adjList;

    void addEdge(const string& from, const string& to, int weight) {
        adjList[from].emplace_back(from, to, weight);
        adjList[to].emplace_back(to, from, weight); // Assuming undirected graph
    }
};

pair<int, vector<string>> dijkstra(const Graph& graph, const string& start, const string& end) {
    unordered_map<string, int> distances;
    unordered_map<string, string> parent;
    set<pair<int, string>> nodes;

    for (const auto& pair : graph.adjList) {
        distances[pair.first] = INT_MAX;
        nodes.insert({INT_MAX, pair.first});
    }

    distances[start] = 0;
    nodes.insert({0, start});

    while (!nodes.empty()) {
        auto smallest = *nodes.begin();
        nodes.erase(nodes.begin());

        if (smallest.second == end) {
            vector<string> path;
            string current = end;

            while (parent.find(current) != parent.end()) {
                path.push_back(current);
                current = parent[current];
            }

            path.push_back(start);
            reverse(path.begin(), path.end());
            return {smallest.first, path};
        }

        if (smallest.first == INT_MAX) {
            break;
        }

        for (const auto& neighbor : graph.adjList.at(smallest.second)) {
            int alt = smallest.first + neighbor.weight;

            if (alt < distances[neighbor.to]) {
                nodes.erase({distances[neighbor.to], neighbor.to});
                distances[neighbor.to] = alt;
                parent[neighbor.to] = smallest.second;
                nodes.insert({alt, neighbor.to});
            }
        }
    }

    return {INT_MAX, {}};
}

// Helper function to trim whitespace from both ends of a string
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}

int main() {
    Graph cityMap;

    string start = "MY_LOCATION";

    vector<tuple<string, string, int>> edges = {

    // Connections from MY LOCATION to hospitals
    {start, "Apollo", 100},
    {start, "SIMS", 115},
    {start, "Kauvery", 120},
    {start, "MIOT", 125},
    {start, "Fortis_Malar", 130},
    {start, "Vijaya", 235},
    {start, "Global_Health_City", 340},
    {start, "Prashanth_Hospital", 245},
    {start, "SRMC", 150},

    // Additional connections between hospitals and other locations
    {"Apollo", "SIMS", 5},
    {"Apollo", "Kauvery", 8},
    {"SIMS", "Kauvery", 3},
    {"SIMS", "MIOT", 7},
    {"Kauvery", "MIOT", 10},
    {"MIOT", "Fortis_Malar", 4},
    {"Fortis_Malar", "Vijaya", 6},
    {"Vijaya", "Apollo", 9},
    {"Global_Health_City", "Prashanth_Hospital", 7},
    {"Prashanth_Hospital", "SRMC", 5},
    {"SRMC", "Apollo", 12},
    {"SRMC", "MIOT", 9},
    {"Global_Health_City", "Kauvery", 11},
    {"Fortis_Malar", "Global_Health_City", 13},

    // Additional intermediate points (e.g., intersections)
    {"Intersection_1", "Apollo", 40},
    {"Intersection_1", "SIMS", 60},
    {"Intersection_2", "Kauvery", 52},
    {"Intersection_2", "MIOT", 75},
    {"Intersection_3", "Fortis_Malar", 58},
    {"Intersection_3", "Vijaya", 23},
    {"Intersection_4", "Global_Health_City", 46},
    {"Intersection_4", "Prashanth_Hospital", 95},
    {"Intersection_5", "SRMC", 77},
    {"Intersection_5", "Fortis_Malar", 28},
    {"Intersection_6", "Apollo", 59},
    {"Intersection_6", "MIOT", 84},
    {"Intersection_1", "Intersection_2", 5},
    {"Intersection_2", "Intersection_3", 4},
    {"Intersection_3", "Intersection_4", 7},
    {"Intersection_4", "Intersection_5", 6},
    {"Intersection_5", "Intersection_6", 5},

    {start, "Intersection_1", 1},
    {start, "Intersection_2", 5},
    {start, "Intersection_3", 2},
    {start, "Intersection_4", 3},
    {start, "Intersection_5", 4},
    {start, "Intersection_6", 6}
};


    for (const auto& edge : edges) {
        cityMap.addEdge(get<0>(edge), get<1>(edge), get<2>(edge));
    }

    vector<string> hospitals = {
        "Apollo", "SIMS", "Kauvery", "Prashanth_Hospital", "SRMC",
        "MIOT", "Fortis_Malar", "Vijaya", "Global_Health_City"
    };

    unordered_map<string, pair<int, vector<string>>> hospitalRoutes;

    for (const auto& hospital : hospitals) {
        hospitalRoutes[hospital] = dijkstra(cityMap, start, hospital);
    }

    string userChoiceHospital;
    cout << "Available hospitals: ";
    for (const auto& hospital : hospitals) {
        cout << hospital << " ";
    }
    cout << "\nEnter the hospital you want to go to: ";
    getline(cin, userChoiceHospital);

    // Normalize user input
    userChoiceHospital = trim(userChoiceHospital);

    

    if (hospitalRoutes.find(userChoiceHospital) == hospitalRoutes.end()) {
        cerr << "Invalid hospital choice." << endl;
        return 1;
    }

    auto chosenHospitalRoute = hospitalRoutes[userChoiceHospital];
    cout << "Route to chosen hospital " << userChoiceHospital << " with minimum distance " << chosenHospitalRoute.first << ":\n";
    for (size_t i = 0; i < chosenHospitalRoute.second.size(); ++i) {
    cout << chosenHospitalRoute.second[i];
    if (i != chosenHospitalRoute.second.size() - 1) {
        cout << " -> ";
    }
}
cout << endl;

    // Save the graph and path to a DOT file
    // Save the graph and path to a DOT file
ofstream dotFile("graph.dot");
dotFile << "graph G {\n";

// Create a set to store the edges in the shortest path
set<pair<string, string>> shortestPathEdges;
for (size_t i = 0; i < chosenHospitalRoute.second.size() - 1; ++i) {
    string from = chosenHospitalRoute.second[i];
    string to = chosenHospitalRoute.second[i + 1];
    shortestPathEdges.insert({from, to});
    shortestPathEdges.insert({to, from}); // Since the graph is undirected
}

// Write all edges, highlighting the shortest path in red
for (const auto& edge : edges) {
    string from = get<0>(edge);
    string to = get<1>(edge);
    int weight = get<2>(edge);
    if (shortestPathEdges.find({from, to}) != shortestPathEdges.end() || 
        shortestPathEdges.find({to, from}) != shortestPathEdges.end()) {
        dotFile << "    " << from << " -- " << to << " [color=red,penwidth=2.0,label=\"" << weight << "\"];\n";
    } else {
        dotFile << "    " << from << " -- " << to << " [label=\"" << weight << "\"];\n";
    }
}

dotFile << "}\n";
dotFile.close();

}
