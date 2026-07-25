#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Edge{
    int u;
    int v;
    int weight;
};

vector<Edge> edgeList;

void printPath(int destination, vector<int> &parent){
    if(parent[destination] != -1){
        printPath(parent[destination], parent);
        cout << " ->";
    }
    if(destination == -1){
        cout << "No safe path found.\n";
        return;
    }
    cout << " " << destination;
}

void bellmanFord(int vertices, int source, int destination){
      vector<int> distance(vertices, INF);
    vector<int> parent(vertices, -1);
    distance[source] = 0;
 
    for (int i = 0; i < vertices - 1; i++)
    {
        for (Edge &e : edgeList)
        {
            if (distance[e.u] == INF)
                continue;   
 
            if (distance[e.u] + e.weight < distance[e.v])
            {
                distance[e.v] = distance[e.u] + e.weight;
                parent[e.v] = e.u;
            }
        }
    }
    for (Edge &e : edgeList)
    {
        if (distance[e.u] == INF)
            continue;
        if (distance[e.u] + e.weight < distance[e.v])
        {
            cout << "Warning: Negative cycle detected in graph.\n";
            return;
        }
    }
 
    if (distance[destination] == INF)
    {
        cout << "No Safe Path Found.\n";
        return;
    }
 
    cout << "\n===== BELLMAN-FORD RESULT =====\n";
    cout << "Shortest Distance : " << distance[destination] << endl;
    cout << "Path : ";
    printPath(destination, parent);
    cout << endl;
}

int main()
{
    ifstream file("input.txt");
    if (!file)
    {
        cout << "Cannot open input.txt\n";
        return 0;
    }
 
    int vertices, edges;
    file >> vertices >> edges;
 
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
 
        edgeList.push_back({u, v, weight});   
    }
 
    int source, destination;
    file >> source >> destination;
    file.close();
 
    if (source < 0 || source >= vertices || destination < 0 || destination >= vertices)
    {
        cout << "Invalid source or destination node.\n";
        return 0;
    }
 
    bellmanFord(vertices, source, destination);
    return 0;
}