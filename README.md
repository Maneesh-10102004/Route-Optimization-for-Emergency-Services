# Route-Optimization-for-Emergency-Services
Developed a system using graphs and Dijkstra's algorithm to find optimal routes for emergency services (e.g., hospitals, fire trucks) on city maps. Features OOP design, priority queues, hashmaps for shortest paths, and generates path-highlighted map images.
## How to Compile and Run:
- Type the following commands one by one in the terminal of your IDE:<br>
g++ -o main main.cpp <br>
./main<br>
- Then , type the name of the hospital you want to go to.
- Path and the minimum distance to the chosen hospital are outputted.
- After this, even a "graph.dot" file is generated.
- To get the city's image with the shortest path highlighted in red, perform the following steps:
- Open the command prompt ( type cmd in the search palette or search it via the Start icon(looks like a window) ).
- Navigate to the directory/folder containing the "graph.dot" file in the Command Prompt.
- Then, enter the following in Command Prompt:<br>
dot -Tpng graph.dot -o graph.png <br>
- A png file containing the required image is created in the same directory as that of the "graph.dot" file.

- Note: The graph.dot and graph.png files that I have uploaded are for my specific city map and I uploaded them just for your reference.
- You can create your own city map and do the same if you wish.
- For detailed functioning, please refer to the documentation.md file in the repo.
