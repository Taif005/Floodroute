#include <bits/stdc++.h>
using namespace std;

// Edge representation: destination node, weight (cost) of the edge
struct Edge {
    int to;
    double weight;
};

// Graph represented as an adjacency list
// graph[u] = list of edges going out from node u
using Graph = vector<vector<Edge>>;

// Dijkstra's algorithm
// start  -> source node
// end    -> destination node
// returns: {shortest distance, path as a list of node indices}
pair<double, vector<int>> dijkstra(const Graph& graph, int start, int end) {
    int n = graph.size();
    vector<double> dist(n, numeric_limits<double>::infinity());
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);

    // min-heap of (distance, node), smallest distance on top
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

    dist[start] = 0.0;
    pq.push({0.0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;   // skip if already finalized
        visited[u] = true;

        if (u == end) break;        // early exit once destination is reached

        for (const Edge& e : graph[u]) {
            if (e.weight == numeric_limits<double>::infinity())
                continue;           // blocked/flooded road, skip entirely

            double newDist = dist[u] + e.weight;
            if (newDist < dist[e.to]) {
                dist[e.to] = newDist;
                prev[e.to] = u;
                pq.push({newDist, e.to});
            }
        }
    }

    // Reconstruct path by walking back through prev[]
    vector<int> path;
    if (dist[end] == numeric_limits<double>::infinity()) {
        return {dist[end], path};   // no path found
    }

    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    return {dist[end], path};
}

int main() {
    // Example graph setup: 5 nodes (0-4), edges represent road segments
    // Weight already includes flood risk multiplier (as computed in Stage 4)
    int numNodes = 5;
    Graph graph(numNodes);

    // Helper to add a directed edge (roads are directed, matching MultiDiGraph in Python)
    auto addEdge = [&](int u, int v, double weight) {
        graph[u].push_back({v, weight});
    };

    // Sample road network with weights (distance * risk multiplier)
    addEdge(0, 1, 4.0);
    addEdge(0, 2, 1.0);
    addEdge(2, 1, 2.0);
    addEdge(1, 3, 5.0);
    addEdge(2, 3, 8.0);
    addEdge(3, 4, 3.0);
    addEdge(2, 4, numeric_limits<double>::infinity()); // blocked: high flood risk

    int start = 0, end = 4;
    auto [distance, path] = dijkstra(graph, start, end);

    if (path.empty()) {
        cout << "No safe path found from " << start << " to " << end << ".\n";
    } else {
        cout << "Safest path cost: " << distance << "\n";
        cout << "Path: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << "\n";
    }

    return 0;
}
