#include <iostream>
#include <vector>
#include <list>

using std::cin;
using std::cout;

std::vector<std::pair<int, int> > g[500];

#define INF 99999

int main(){
    int n, a, b, c, e;
    cin >> n >> e; // Node and edge number
    for(int i=0; i<n; i++){
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
    }

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            for(int k=0; k<n; k++)
                if(g[j][i].first + g[i][k].first < g[j][k].first)
                    g[j][k].first = g[j][i].first + g[i][k].first;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (g[i][j].first == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", g[i][j].first);
        }
        printf("\n");
    }

    return 0;
}