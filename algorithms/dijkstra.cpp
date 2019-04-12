#include <algorithm>
#include <queue>

void dijkstra(int start)
{
    nodes[start].calcWeight = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pQueue;
    pQueue.push({start, 0});
    while(!pQueue.empty())
    {
        int current = pQueue.top().first;
        int weight = pQueue.top().second;
        pQueue.pop();
        if(nodes[current].visited)
        {
            continue;
        }
        nodes[current].visited = true;
        for(auto a : nodes[current].edges)
        {
            if(nodes[a.first].calcWeight > weight + a.second)
            {
                nodes[a.first].calcWeight = weight + a.second;
                pQueue.push({a.first, weight + a.second});
            }
        }
    }
}