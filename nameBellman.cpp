#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

//------------------------------------------------------------
// Edge Structure
//------------------------------------------------------------
struct Edge
{
    int u;
    int v;
    int weight;
};

vector<Edge> edgeList;
vector<string> locationName;

//------------------------------------------------------------
// Print Shortest Path
//------------------------------------------------------------
void printPath(int destination, vector<int> &parent)
{
    if (parent[destination] != -1)
    {
        printPath(parent[destination], parent);
        cout << " -> ";
    }

    cout << locationName[destination];
}

//------------------------------------------------------------
// Bellman-Ford Algorithm
//------------------------------------------------------------
void bellmanFord(int vertices, int source, int destination)
{
    vector<int> distance(vertices, INF);
    vector<int> parent(vertices, -1);

    distance[source] = 0;

    // Relax all edges (V-1) times
    for (int i = 0; i < vertices - 1; i++)
    {
        bool updated = false;

        for (Edge edge : edgeList)
        {
            if (distance[edge.u] == INF)
                continue;

            if (distance[edge.u] + edge.weight < distance[edge.v])
            {
                distance[edge.v] = distance[edge.u] + edge.weight;
                parent[edge.v] = edge.u;
                updated = true;
            }
        }

        if (!updated)
            break;
    }

    // Check for negative cycle
    for (Edge edge : edgeList)
    {
        if (distance[edge.u] == INF)
            continue;

        if (distance[edge.u] + edge.weight < distance[edge.v])
        {
            cout << "Negative Weight Cycle Detected!\n";
            return;
        }
    }

    if (distance[destination] == INF)
    {
        cout << "No Safe Path Found.\n";
        return;
    }

    cout << "\n========== BELLMAN-FORD RESULT ==========\n\n";

    cout << "Source              : "
         << locationName[source] << endl;

    cout << "Destination         : "
         << locationName[destination] << endl;

    cout << "Shortest Distance   : "
         << distance[destination] << endl;

    cout << "Shortest Path       : ";

    printPath(destination, parent);

    cout << endl;
}

//------------------------------------------------------------
// Main Function
//------------------------------------------------------------
int main()
{
    ifstream file("dhaka_city_input_20_nodes.txt");

    if (!file)
    {
        cout << "Cannot open input file.\n";
        return 0;
    }

    int vertices, edges;

    file >> vertices >> edges;

    // Read location names
    locationName.resize(vertices);

    for (int i = 0; i < vertices; i++)
    {
        file >> locationName[i];
    }

    // Read edges
    for (int i = 0; i < edges; i++)
    {
        int u, v, weight, flooded;

        file >> u >> v >> weight >> flooded;

        if (u < 0 || u >= vertices ||
            v < 0 || v >= vertices)
        {
            cout << "Invalid Edge Skipped\n";
            continue;
        }

        if (flooded == 1)
            continue;

        edgeList.push_back({u, v, weight});

        // Uncomment if roads are two-way
        // edgeList.push_back({v, u, weight});
    }

    int source, destination;

    file >> source >> destination;

    file.close();

    if (source < 0 || source >= vertices ||
        destination < 0 || destination >= vertices)
    {
        cout << "Invalid Source/Destination.\n";
        return 0;
    }

    bellmanFord(vertices, source, destination);

    return 0;
}