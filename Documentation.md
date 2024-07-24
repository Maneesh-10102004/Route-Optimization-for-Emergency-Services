# Route Optimization for Emergency Services

## Problem Statement
In emergency situations, it's crucial for emergency services (like ambulances, fire trucks, or police cars) to reach their destinations as quickly as possible. Given a map of a city, with locations represented as nodes and roads as edges, I have developed a system that finds the optimal route for emergency services. I have implemented this for hospitals, but it can easily be modified for fire trucks or any other application just by changing the map which we provide.

## Key Features
- Graph Representation: Uses graphs to represent the city map.
- Priority Queue: Implements Dijkstra's algorithm for finding the shortest path using priority queues.
- Object Oriented Programming: Solution design involves using OOP principles.
- Hashmaps: For storing the minimum distance and shortest path corresponding to a node.
- Image Output: Generates a png file containing the whole map along with a highlighted path indicating the shortest path possible from the start point to the end point decided by user.

## Detailed functionality
- First, an object of type 'Graph' is created.
- _Graph Class_:
- The Graph class represents an undirected graph using an adjacency list. An undirected graph is a set of nodes (also called vertices) connected by edges, where each edge has no direction. The adjacency list is a common way to store this information, where each node has a list of all nodes it's directly connected to, along with the weights of these connections.

- Its components are:
- adjList- which is an unordered map whose key is a string(representing the node) and value is vector of strings(representing the weights of the neighbours of the node), and
- addEdge- Is a method(like a function) which adds an edge to the graph. It takes three parameters: the names of the two nodes (from and to) and the weight of the edge (weight).
- When you call addEdge, it updates the adjacency list to include this new edge.
- Since this is an undirected graph, the edge is added in both directions:<br>
From from to to<br>
From to to from<br>
This ensures that the connection can be traversed both ways.

#### Example

```cpp
Graph cityMap;

// Adding edges to the graph
cityMap.addEdge("A", "B", 5);
cityMap.addEdge("A", "C", 3);
cityMap.addEdge("B", "C", 2);

// Adjacency list after adding edges:
// "A" -> [Edge("A", "B", 5), Edge("A", "C", 3)]
// "B" -> [Edge("B", "A", 5), Edge("B", "C", 2)]
// "C" -> [Edge("C", "A", 3), Edge("C", "B", 2)]
```

- Then, the string "start" ( represents our current location) is declared.
- Then, the city's roadways are declared and are represented as a collection of edges connecting two places(nodes).
- Then, these edges are added to the city's map.
- Then, a vector of strings named "hospitals" is declared which stores the names of each hospital in the city.
- The code implements Dijkstra's algorithm to find the shortest path from the starting location to various hospitals in a city represented as a graph.
```cpp 
unordered_map<string, pair<int, vector<string>>> hospitalRoutes 
``` 
"hospitalRoutes" Stores the shortest path and its distance from the starting location to each hospital.
The key is the hospital name, and the value is a pair containing the distance and the path (a vector of nodes).

### Dijkstra's Algorithm:
- First, the distance of each node from the start node is initialised to infinity(INT_MAX) and the distance of start node from itself is initialised to 0. A map called parent is declared to keep track of the path traversed (backtracking).
- These nodes are stored in a set, so it is sorted. Now, the element eith the smallest distance is taken.
- If the destination is reached,  the path is reconstructed by following the 'parent' map and  the distance and path are returned.
- If current 'smallest' node has a distance of INT_MAX, it means that the remaining nodes are not reachable, and the algorithm terminates.
- For each neighbor of smallest:
- The new potential distance (alt) from the start node to the neighbor through smallest node is calculated.
If alt is smaller than the current known distance to the neighbor, the distance and the previous node are updated. Also, the nodes set with the new distance are updated.
<br>
<br>
- Then, the user is asked about which hospital he/she wants to go to.
- All the white spaces are trimmed from the user's input to avoid confusion.
- If the hospital does not exist, appropriate error message is outputted.
- Then , using the 'hospitalRoutes' map(contains the shortest distance and corresponding path to all hospitals), the shortest distance and corresponding path to the required hospital is printed.
<br>
- Then, a file is opened in the DOT Format(The DOT format is used by Graphviz library to create visual representations of graphs).
- Then, for loops are used to iterate over all edges in the graph and highlight only the shortest one in red and the remaining in black.
- For each edge, it writes a line in the DOT file representing the edge. The format " A -- B [label="weight"]; " specifies an undirected edge between nodes A and B with a label showing the edge's weight.

- At last, the DOT file is closed.

- Note: To create the image of the graph, in addition to the user input, you should type the following line in Command Prompt after navigating to the directory containing the "graph.dot" file: <br>
dot -Tpng graph.dot -o graph.png

- graph.png is just the name of the image, you can have any name you want.

