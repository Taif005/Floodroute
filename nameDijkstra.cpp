#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Edge
{
    int destination;
    int weight;
};

vector<vector<Edge>> graph;
vector<string> locationName;


void printPath(int destination, vector<int> &parent)
{
    if (parent[destination] != -1)
    {
        printPath(parent[destination], parent);
        cout << " -> ";
    }
    cout << locationName[destination];
}

void dijkstra(int vertices, int source, int destination)
{
    vector<int> distance(vertices, INF);
    vector<int> parent(vertices, -1);

    priority_queue<pair<int, int>,
                   vector<pair<int, int>>,
                   greater<pair<int, int>>> pq;

    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        int currentDistance = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if (currentDistance > distance[currentNode])
            continue;

        for (auto edge : graph[currentNode])
        {
            int nextNode = edge.destination;
            int newDistance = currentDistance + edge.weight;

            if (newDistance < distance[nextNode])
            {
                distance[nextNode] = newDistance;
                parent[nextNode] = currentNode;
                pq.push({newDistance, nextNode});
            }
        }
    }

    if (distance[destination] == INF)
    {
        cout << "No safe path found.\n";
        return;
    }

    cout << "\n========== DIJKSTRA RESULT ==========\n\n";
    cout << "Source          : " << locationName[source] << endl;
    cout << "Destination     : " << locationName[destination] << endl;
    cout << "Shortest Distance : " << distance[destination] << endl;

    cout << "Shortest Path   : ";
    printPath(destination, parent);
    cout << endl;
}

int main()
{
    ifstream file("dhaka_city_input_20_nodes.txt");

    if (!file)
    {
        cout << "Cannot open input file!\n";
        return 0;
    }

    int vertices, edges;
    file >> vertices >> edges;

    graph.resize(vertices);

    locationName.resize(vertices);

    for (int i = 0; i < vertices; i++)
    {
        file >> locationName[i];
    }

    for (int i = 0; i < edges; i++)
    {
        int u, v, weight, flooded;
        file >> u >> v >> weight >> flooded;

        if (u < 0 || u >= vertices || v < 0 || v >= vertices)
        {
            cout << "Invalid edge skipped.\n";
            continue;
        }
        if (flooded == 1)
            continue;

        graph[u].push_back({v, weight});

    }

    int source, destination;
    file >> source >> destination;

    file.close();

    if (source < 0 || source >= vertices ||
        destination < 0 || destination >= vertices)
    {
        cout << "Invalid source or destination.\n";
        return 0;
    }

    dijkstra(vertices, source, destination);

    return 0;
}