#include <bits/stdc++.h>
using namespace std;


const int INF=1e9;

struct Edge{
    int destination;
    int weight;
};

struct Point{
    double x,y;
};


vector<vector<Edge>> graph;
 vector<Point> coords;
  vector<string> locationName;

double heuristic(int a,int b){
    double dx=coords[a].x-coords[b].x,
    dy=coords[a].y-coords[b].y;
    return sqrt(dx*dx+dy*dy);
}

void printPath(int n,vector<int>&p){
    if(p[n]!=-1){
        printPath(p[n],p);
        cout<<" -> ";
    }
    
    cout<<locationName[n];
}
void aStar(int V,int s,int d){
    vector<double> dist(V,INF);
    vector<int> par(V,-1);
    vector<bool> vis(V,false);

    priority_queue<pair<double,int>,
            vector<pair<double,int>>,
            greater<pair<double,int>>> pq;

            dist[s]=0;

            pq.push({heuristic(s,d),s});

            int explored=0;

            while(!pq.empty()){
                int u=pq.top().second;
                pq.pop();

                if(vis[u])
                continue;
                vis[u]=true;
                explored++;

                if(u==d)break;
                for(auto e:graph[u])
                {
                    double nd=dist[u]+e.weight;
                    if(nd<dist[e.destination])
                    {
                        dist[e.destination]=nd;
                        par[e.destination]=u;
                        pq.push({nd+heuristic(e.destination,d),e.destination});
                    }
                }
            }
            if(dist[d]>=INF)
                {
                    cout<<"No Safe Path Found\n";
                    return;
                }
                    cout<<"\n========== A* RESULT ==========\n\n";
                    cout << "Output with 5000 nodes\n";
                    cout<<"Source              : "<<locationName[s]<<"\n";
                    cout<<"Destination         : "<<locationName[d]<<"\n";
                    cout<<"Shortest Distance   : "<<dist[d]<<"\n";
                    cout<<"Nodes Explored      : "<<explored<<"\n";
                    cout<<"Shortest Path       : ";printPath(d,par);
                    cout<<"\n";
                }
int main(){
    ifstream file("Astar_5000_nodes.txt");
    if(!file){cout<<"Cannot open dhaka_astar_50_node.txt\n";
        return 0;
    }
    int V,E;file>>V>>E;graph.resize(V);
    locationName.resize(V);


    for(int i=0;i<V;i++)
    file>>locationName[i];


    for(int i=0;i<E;i++){
        int u,v,w,f;file>>u>>v>>w>>f;
        if(f)continue;graph[u].push_back({v,w});
    }
    coords.resize(V);
    for(int i=0;i<V;i++)
    {
        file>>coords[i].x>>coords[i].y;
    }
    int s,d;
    file>>s>>d;
    aStar(V,s,d);
}