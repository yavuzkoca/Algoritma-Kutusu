#include <iostream>
#include <vector>

using namespace std;
#define MAX_N 500
#define INF 999999

vector< pair<int, int> > g[MAX_N];
int dist[MAX_N];
bool visited[MAX_N];

int main(){
    int a,b,c,v,e,s;
    cin >> v >> e;

    for(int i=0; i<e; i++){
        cin >> a >> b >> c;
        g[a].push_back(make_pair(b,c));
        g[b].push_back(make_pair(a,c));
    }

    cin >> s;
    for(int i=0; i<v; i++) dist[i] = 999999; // All vertices are in infinite distance from source

    dist[s] = 0;
    int nextVertex,minimum = 999999,min_index;
    for(int i=0; i<v-1; i++){
        min_index = 0;
        for(int j=0; j<v; j++)
            if(!visited[j] && dist[j] <= minimum){
                minimum = dist[j];
                min_index = j;
            }

        visited[min_index] = true;
        for(int j=0; j<v; j++)
            if(!visited[j] && g[min_index][j].second && dist[min_index] != 999999 && dist[min_index]+g[min_index][j].second < dist[j])
                dist[v] = dist[min_index] + g[min_index][j].second;
    }

    cout << "Vertex Distance from Source\n";
    for (int i = 0; i < v; i++)
        cout << i << "\t\t" << dist[i] << endl;

    return 0;
}