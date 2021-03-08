#include <bits/stdc++.h>
using namespace std;

map<int,list<pair<int,int>>>graph;             

void AddEdge(int x,int y, int w,bool bidirectional=true)           //x=source  y=destination  w=weight/cost
{
    graph[x].push_back({y,w});
    if(bidirectional)
    graph[y].push_back({x,w});
}

void helper(int source, vector<int>& res)
{
    map<int,int> distance;                                                  //for storing distance from source

    for(auto j: graph)                                                          // Initially every node is at diatnce INFINITY
       distance[j.first]=INT_MAX;
    
    distance[source]=0;                                                     

    set<pair<int,int>>s;                                                    //pair of weight/distance and destination                        
    s.insert(make_pair(0,source));

    while(!s.empty())
    {
        auto p = *(s.begin());
        int dist_node = p.first;
        auto node = p.second;
        s.erase(s.begin());

        for(auto neighbours: graph[node])
        {
            if(dist_node + neighbours.second < distance[neighbours.first]) //if original distance of source to destination 
            {                                                              //is more than new distance then update the distance 
                auto destination = neighbours.first;
                auto position= s.find({distance[destination],destination});         //finding the desired pair in the set

                if(position!=s.end())                             //if the pair is present in the set
                  s.erase(position);

                distance[destination] = dist_node + neighbours.second;
                s.insert({distance[destination],destination});
            }
        }
    }
       
    for(auto x: distance)
    {
      res.push_back(x.second);          
    }
}

vector <int> dijkstra(int vertices, vector<vector<int>> adj[], int source) 
{
int first,destination,weight;
vector<int> res;

for(int i=0;i<vertices;i++)
{
for(auto itr:adj[i])
{
    first=i;
    destination=itr[0];
    weight=itr[1];
    AddEdge(first,destination,weight);
}
}

helper(source,res);
return res;
}