#include<iostream>
#include<vector>
using namespace std;
class Graph
{
    int vertices;
    int edgesCount;
    struct Edge
    {
        int u,v,w;
    };
    vector<Edge> edges;

    public:
        Graph(int v, int e)
        {
            vertices = v;
            edgesCount = e;
            edges.resize(edgesCount);
        }
        void addEdge(int i, int u, int v, int w)
        {
            edges[i]={u,v,w};
        }
        void showGraph()
        {
            //Adjacency List
            vector<vector<int>> adjList(vertices);
            for(auto &edge : edges)
            {
                adjList[edge.u].push_back(edge.v);
            }
            for(int i=0;i<vertices;i++)
            {
                cout<<i<<" : ";
                for(int v : adjList[i])
                {
                    cout<<v<<" ";
                }
                cout<<endl;
            }

            //Adjacency Matrix
            vector<vector<int>> adjMatrix(vertices,vector<int>(vertices,0));
            for(auto &edge : edges)
            {
                adjMatrix[edge.u][edge.v] = edge.w;
            }
            for(int i=0;i<vertices;i++)
            {
                for(int j=0;j<vertices;j++)
                {
                    cout<<adjMatrix[i][j]<<" ";
                }
                cout<<endl;
            }
        }
        bool bellman(int source, vector<int>& distance)
        {
            distance.resize(vertices,1e9);
            distance[source] = 0;
            //Check for v-1 times
            for(int i=1;i<=vertices-1;i++)
            {
                for(int j=0;j<edgesCount;j++)
                {
                    int u = edges[j].u;
                    int v = edges[j].v;
                    int w = edges[j].w;
                    if(distance[u]!=1e9 && distance[u]+w < distance[v])
                        distance[v] = distance[u] + w;
                }
            }
            //check for negative cycle
            for(int j=0;j<edgesCount;j++)
            {
                int u = edges[j].u;
                int v = edges[j].v;
                int w = edges[j].w;
                if(distance[u]!=1e9 && distance[u]+w < distance[v])
                    return false;
            }
            return true;
        }
};
int main()
{
    int vertices, edges;
    cout<<"\nEnter the number of vertices : ";
    cin>>vertices;
    cout<<"\nEnter the number of edges : ";
    cin>>edges;
    Graph g(vertices,edges);
    cout<<"\nEnter the edges (u v weight)\n";
    for(int i=0;i<edges;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        g.addEdge(i,u,v,w);
    }
    g.showGraph();
    int source;
    cout<<"\nEnter a source vertex  : ";
    cin>>source;
    vector<int> distance;
    bool noNeg = g.bellman(source,distance);
    if(noNeg)
    {
        for(int i=0;i<vertices;i++)
        {
            if(distance[i]==1e9)
                cout<<i<<" : INF"<<"\n";
            else
                cout<<i<<" : "<<distance[i]<<"\n";
        }
    }
    else
    {
        cout<<"\nGraph contains negative edge cycle";
    }

}