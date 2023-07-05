// Hierholzer's algorithm is a graph theory algorithm that is used to find Eulerian circuits or paths in a graph. 
// An Eulerian circuit is a path that visits every edge of the graph exactly once and ends at the starting vertex, 
// while an Eulerian path is a path that visits every edge of the graph exactly once 
// but does not necessarily end at the starting vertex.

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> adjList[100001];
stack<int> eulerPath;

void dfs(int node) {
    for(int i = 0; i < adjList[node].size(); i++) {
        int adjNode = adjList[node][i];
        if (adjNode != -1) {
            adjList[node][i] = -1;
            dfs(adjNode);
        }
    }
    eulerPath.push(node);
}

int main() {
    // number of nodes and edges
    int n, m; 
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v; 
        cin >> u >> v;
        adjList[u].push_back(v);
    }
    // assume 0 is the starting node
    dfs(0);
    while (!eulerPath.empty()) {
        cout << eulerPath.top() << " ";
        eulerPath.pop();
    }
    return 0;
}