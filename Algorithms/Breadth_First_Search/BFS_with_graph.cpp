#include <iostream>
#include <list>
#include <queue>

using namespace std;

class Graph{
    int N;
    list<int> *adj;
public:
    explicit Graph(int);
    void add_edge(int, int);
    void BFS(int);
};

Graph::Graph(int n) : N(n) {
    this->adj = new list<int>[n];
}

void Graph::add_edge(int a, int b) {
    this->adj[a].push_back(b);
}

void Graph::BFS(int s) {
    auto *visited = new bool[N];
    for(int i=0; i<N; i++) visited[i] = false;
    visited[s] = true;
    queue<int> q;
    q.push(s);

    list<int>::iterator i;

    while(!q.empty()){
        s = q.front();
        cout << s << " ";
        q.pop();

        for(i=adj[s].begin(); i!=adj[s].end(); ++i)
            if(!visited[*i]){
                q.push(*i);
                visited[*i] = true;
            }

    }
}


int main(){
    Graph g(4);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.add_edge(2, 3);
    g.add_edge(3, 3);
    g.BFS(2);
}