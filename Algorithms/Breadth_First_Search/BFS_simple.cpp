#include <iostream>
#include <vector>
#include <queue>

using namespace std;
vector<int> g[500];
bool visited[500];

void add_edge(int a, int b){
    g[a].push_back(b);
}

void bfs(int s){
    queue<int> q;
    q.push(s);
    visited[s] = true;

    while(!q.empty()){
        int n = q.front();
        cout << n << " ";
        q.pop();
        for (int i : g[n]) {
            if(!visited[i]){
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

int main(){
    int n,a,b;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a >> b;
        add_edge(a,b);
        add_edge(b,a);
    }

    bfs(2);

    return 0;
}