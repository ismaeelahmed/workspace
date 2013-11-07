#include <map>
#include <string>
#include <utility>
#include <functional>
#include <queue>
#include <vector>
#include <iostream>

typedef std::string Nodelabel;				//node name
typedef std::map<Nodelabel, int> Nodelist;	//node and associated edge cost
typedef std::map<Nodelabel, Nodelist> Graph;//connected nodes form a graph
typedef std::pair<Nodelabel, Nodelist> Node;//node
typedef std::pair<int, Nodelabel> Edg;		//edge

bool operator>(const Edg r, const Edg k){ return r.first>k.first; }//compare edge cost

void dijkstra(Graph &graph, Nodelabel source, Nodelist &distance){
  distance.clear();
  std::priority_queue<Edg, std::vector<Edg>, std::greater<Edg> > que;
  que.push(Edg(0, source));

  while(!que.empty()){
    Edg tmped=que.top();			//get edge with highest cost
    Nodelabel tmpnl=tmped.second;	//extract node label
    que.pop();						//pop it
    if(distance.count(tmpnl)==0){	//find number of elements with this name(key)
      int dist=tmped.first;			//note its edge cost
      distance[tmpnl]=dist;			//save the distance in list
      Nodelist tempgraph=graph[tmpnl];	//
      Nodelist::iterator it;
      for(it=tempgraph.begin(); it!=tempgraph.end(); ++it){
        int distint=it->second;
        Nodelabel distlabel=it->first;
        que.push(Edg(dist+distint, distlabel));
      }
    }
  }
}

int main(){
  Graph test;
  test["japan"]["usa"]=12;
  test["usa"]["kanada"]=14;
  test["usa"]["kuba"]=3;
  test["kuba"]["kanada"]=4;

  Nodelist strecke;

  dijkstra(test, "japan", strecke);

  Nodelist::iterator it;
  for(it=strecke.begin(); it!=strecke.end(); ++it){
    std::cout<<it->second<<" <=> "<<it->first<<std::endl;
  }
  return 1;
}




/*
 *
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
using namespace std;

#define pb push_back
#define mp make_pair
#define MAXN 50100
#define INF 1000000000

int N, M, d[MAXN]; vector<int> G[MAXN], C[MAXN];
set< pair<int, int> > T;

void solve(void)
{
    int i, j, k, val, x;

    for(i = 2; i <= N; i++) d[i] = INF;
    T.insert( mp(0, 1) );

    while( T.size() > 0 )
    {
        val = (*T.begin()).first, x = (*T.begin()).second;
        T.erase(*T.begin());
        for(i = 0; i < G[x].size(); i++)
         if(d[ G[x][i] ] > val + C[x][i] )
            d[ G[x][i] ] = val + C[x][i], T.insert(mp(d[G[x][i]],G[x][i]));
    }
}

int main(void)
{
    freopen("dijkstra.in", "rt", stdin);
    freopen("dijkstra.out", "wt", stdout);

    int i, a, b, c;

    scanf("%d %d\n", &N, &M);

    for(i = 1; i <= M; i++)
        scanf("%d %d %d\n", &a, &b, &c), G[a].pb(b), C[a].pb(c);

    solve();

    for(i = 2; i <= N; i++)
        printf("%d ", d[i] == INF ? 0 : d[i]);

    return 0;
}

*/





