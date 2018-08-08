#include <vector> // std::vector
#include <limits> // std::numeric_limits
#include <../ds/Graph.hpp> // Vertex, WAdjList, Weight, MinWVPQ, WV

// Fills the shortest_path vector with respect to source
void dijkstra(Vertex source, WAdjList& adjlist, std::vector<Weight>& shortest_path)
{
    shortest_path.resize(adjlist.size());
    
    const Weight INF = std::numeric_limits<Weight>::max() / 4; // safe !overflow
    for(Weight& weight : shortest_path) weight = INF;

    shortest_path[source] = 0;
    
    MinWVPQ pq;
    pq.push({shortest_path[source], source});

    while(!pq.empty())
    {
        WV top_wv = pq.top(); pq.pop();
        Weight top_weight = top_wv.first;
        Vertex top_vertex = top_wv.second;

        if(top_weight > shortest_path[top_vertex]) continue; // lazy deletion
        // now top_weight is the shortest path of top_vertex
        
        for(WV& adj_wv : adjlist[top_vertex]) {
            Weight adj_weight = adj_wv.first;
            Vertex adj_vertex = adj_wv.second;

            if(shortest_path[adj_vertex] <= top_weight + adj_weight)
                continue; // does not makes the older path shorter
            
            // a new shorter path found
            shortest_path[adj_vertex] = top_weight + adj_weight;
            pq.push({shortest_path[adj_weight], adj_vertex});
        }
    }
}
