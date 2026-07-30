#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

const int INF = 1e9;

struct Edge
{
    int destination;
    int weight;
};

struct Point
{
    double x, y;
};

vector<vector<Edge>> graph;
vector<Point> coords;  

void printPath(int destination, vector<int> &parent)
{
    if (parent[destination] != -1)
    {
        printPath(parent[destination], parent);
        cout << " -> ";
    }
    cout << destination;
}

double heuristic(int a, int b)
{
    double dx = coords[a].x - coords[b].x;
    double dy = coords[a].y - coords[b].y;
    return sqrt(dx * dx + dy * dy);
}

void aStar(int vertices, int source, int destination)
{
    vector<double> distance(vertices, INF);
    vector<int> parent(vertices, -1);
    vector<bool> visited(vertices, false);

    priority_queue<pair<double, int>,
                   vector<pair<double, int>>,
                   greater<pair<double, int>>> pq;

    distance[source] = 0;
    pq.push({heuristic(source, destination), source});

    int nodesExplored = 0;

    while (!pq.empty())
    {
        int currentNode = pq.top().second;
        pq.pop();

        if (visited[currentNode])
            continue;
        visited[currentNode] = true;
        nodesExplored++;

        if (currentNode == destination)
            break;

        for (Edge edge : graph[currentNode])
        {
            int nextNode = edge.destination;
            double newDistance = distance[currentNode] + edge.weight;

            if (newDistance < distance[nextNode])
            {
                distance[nextNode] = newDistance;
                parent[nextNode] = currentNode;
                double priority = newDistance + heuristic(nextNode, destination);
                pq.push({priority, nextNode});
            }
        }
    }

    if (distance[destination] >= INF)
    {
        cout << "No Safe Path Found.\n";
        return;
    }

    cout << "\n===== A* RESULT =====\n";
    cout << "Shortest Distance : " << distance[destination] << endl;
    cout << "Nodes Explored    : " << nodesExplored << endl;
    cout << "Path : ";
    printPath(destination, parent);
    cout << endl;
}


int main()
{
    ifstream file("input_astar.txt");
    if (!file)
    {
        cout << "Cannot open input_astar.txt\n";
        return 0;
    }

    int vertices, edges;
    file >> vertices >> edges;
    graph.resize(vertices);

    for (int i = 0; i < edges; i++)
    {
        int u, v, weight, flooded;
        file >> u >> v >> weight >> flooded;

        if (u < 0 || u >= vertices || v < 0 || v >= vertices)
        {
            cout << "Invalid edge skipped: " << u << " " << v << "\n";
            continue;
        }

        if (flooded == 1)
            continue;  

        graph[u].push_back({v, weight});   
    }

    coords.resize(vertices);
    for (int i = 0; i < vertices; i++)
    {
        file >> coords[i].x >> coords[i].y;
    }

    int source, destination;
    file >> source >> destination;
    file.close();

    if (source < 0 || source >= vertices || destination < 0 || destination >= vertices)
    {
        cout << "Invalid source or destination node.\n";
        return 0;
    }

    aStar(vertices, source, destination);
    return 0;
}