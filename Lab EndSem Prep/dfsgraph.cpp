#include<iostream>
#include<vector>
#include<stack>
using namespace std;
class Graph
{
    int vertices;
    vector<vector<int>> adjList;
    public:
        Graph(int v)
        {
            vertices = v;
            adjList.resize(v);
        }
        void addEdge(int src, int dest)
        {
            adjList[src].push_back(dest);
            adjList[dest].push_back(src);
        }
        void showGraph()
        {
            //Adjacency List
            for(int i=0;i<vertices;i++)
            {
                cout<<i<<" : ";
                for(int v : adjList[i])
                {
                    cout<<v<<" ";
                }
            }

            //Adjacency Matrix
            vector<vector<int>> adjMatrix(vertices,vector<int>(vertices,0));
            for(int i=0;i<vertices;i++)
            {
                for(int v : adjList[i])
                    adjMatrix[i][v] = 1;
            }
        
            for(int i=0;i<vertices;i++)
            {
                for(int j=0;j<vertices;j++)
                {
                    cout<<adjMatrix[i][j]<<" ";
                }
            }
        }
        void iterDFS(int start)
        {
            vector<bool> visited(vertices,false);
            stack<int> s;
            s.push(start);
            cout<<"\nIterative DFS : ";
            while(!s.empty())
            {
                int node = s.top();
                s.pop();
                if(!visited[node])
                {
                    cout<<node<<" ";    
                    visited[node]=true;
                }
                for(auto it = adjList[node].rbegin(); it!=adjList[node].rend(); it++)
                {
                    if(!visited[*it])
                        s.push(*it);
                }
            }
        }
        void dfsHelp(int node, vector<bool>& visited)
        {
            visited[node] = true;
            cout<<node<<" ";
            for(int neighbour : adjList[node])
            {
                if(!visited[neighbour])
                    dfsHelp(neighbour,visited);
            }
        }
        void recDFS(int start)
        {
            vector<bool> visited(vertices,false);
            cout<<"\nRecursive DFS\n";
            dfsHelp(start, visited);
            cout<<endl;
        }

};
int main()
{
    int vertices, edges, start;
    cout<<"\nEnter the no. of vertices : ";
    cin>>vertices;
    cout<<"\nEnter the no. of edges : ";
    cin>>edges;
    Graph g(vertices);
    for(int i=0;i<edges;i++)
    {
        cout<<"\nEnter the edges (source dest) : ";
        int src,dest;
        cin>>src>>dest;
        g.addEdge(src,dest);
    }
    cout<<"\nEnter the starting node for DFS : ";
    cin>>start;
    g.iterDFS(start);
    g.recDFS(start);
    

}