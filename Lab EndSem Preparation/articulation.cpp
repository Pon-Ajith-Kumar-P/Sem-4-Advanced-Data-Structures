#include<iostream>
#include<vector>
using namespace std;
class Graph
{
    int n;
    vector<vector<int>> adj;
    vector<bool> ap;
    vector<bool> visited;
    vector<int> parent, low, disc;
    int timer;

    public:
        Graph(int ver)
        {
            n = ver;
            adj.resize(n);
            ap.resize(n,false);
            visited.resize(n,false);
            parent.resize(n,-1);
            low.resize(n,0);
            disc.resize(n,0);
            timer = 0;
        } 
        void addEdge(int src, int dest)
        {
            adj[src].push_back(dest);
            adj[dest].push_back(src);
        }
        void showGraph()
        {
            //Adjacency List
            for(int i=0;i<n;i++)
            {
                cout<<i<<" : ";
                for(int v : adj[i])
                {
                    cout<<v<<" ";
                }
                cout<<endl;
            }

            //Adjacency Matrix
            vector<vector<int>> adjMatrix(n,vector<int>(n,0));
            for(int i=0;i<n;i++)
            {
                for(int v : adj[i])
                {
                    adjMatrix[i][v] = 1;
                }
            }

            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    cout<<adjMatrix[i][j]<<" ";
                }
                cout<<endl;
            }
        }

        void dfs(int u)
        {
            visited[u] = true;
            low[u] = disc[u] = ++timer;
            int children = 0;
            for(int v : adj[u])
            {
                if(!visited[v])
                {
                    children++;
                    parent[v] = u;
                    dfs(v);
                    low[u] = min(low[u],low[v]);

                    if(parent[u]==-1 && children>1)
                        ap[u] = true;
                    if(parent[u]!=-1 && low[v]>=disc[u])
                        ap[u] = true;
                }
                else if(v!=parent[u])
                {
                    low[u]=min(low[u],disc[v]);
                }
            }
        }

        bool isBiconnected()
        {
            fill(visited.begin(),visited.end(),false);
            fill(ap.begin(),ap.end(),false);
            fill(parent.begin(),parent.end(),-1);
            timer = 0;
            dfs(0);

            for(int i=0;i<n;i++)
            {
                if(ap[i])
                    return false;
            }

            for(int i=0;i<n;i++)
            {
                if(!visited[i])
                    return false;
            }

            return true;
        }

        void printArticulation()
        {
            cout<<"\nArticulation Points : ";
            for(int i=0;i<n;i++)
            {
                if(ap[i])
                    cout<<i<<" ";
            }
        }
};
int main()
{
    int vertices,edges;
    cout<<"\nEnter the number of vertices : ";
    cin>>vertices;
    cout<<"\nEnter the number of edges : ";
    cin>>edges;
    Graph g(vertices);
    cout<<"\nEnter the edges (source dest)\n";
    for(int i=0;i<edges;i++)
    {
        int src,dest;
        cin>>src>>dest;
        g.addEdge(src,dest);
    }
    g.showGraph();
    if(g.isBiconnected())
    {
        cout<<"\nGraph is Biconnected and no articulation points";
    }
    else
    {
        cout<<"\nGraph is not Biconnected.";
        g.printArticulation();
    }
}