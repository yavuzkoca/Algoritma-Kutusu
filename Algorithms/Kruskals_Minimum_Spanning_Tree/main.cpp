#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int rnk[10005];
int parent[10005];
typedef pair<int, pair<int, int> > LOL;
int find(int);
void merge(int, int);

int main(){
    int v,e,a,b,c;
    cin >> v >> e;
    int weight = 0;
    vector< LOL > edges;
    for(int i=0; i<e; i++){
        cin >> a >> b >> c;
        edges.push_back(make_pair(c,make_pair(a,b)));
        parent[i] = i;
    }
    sort(edges.begin(), edges.end());
    for(int i=0; i<e; i++){
        if(find(edges[i].second.first) != find(edges[i].second.second)){
            cout << edges[i].second.first << " " << edges[i].second.second << endl;
            weight += edges[i].first;
            merge(edges[i].second.first, edges[i].second.second);
        }
    }
    cout << weight;
    return 0;
}

int find(int u) {
    if (u != parent[u])
        parent[u] = find(parent[u]);
    return parent[u];
}

void merge(int x, int y) {
    x = find(x), y = find(y);
    if (rnk[x] > rnk[y])
        parent[y] = x;
    else
        parent[x] = y;

    if (rnk[x] == rnk[y])
        rnk[y]++;
}