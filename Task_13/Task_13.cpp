#include <iostream>
#include "Graph.h"


auto main()->int
{
    auto vertexes_number{15};
    Graph<int> graph(vertexes_number);

    srand(1);
    auto rand_max{RAND_MAX};

    for (auto i{0}; i < vertexes_number; ++i)
    {
        graph.addVertex(i);
    }

    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 4, 1);
    graph.addEdge(4, 5, 1);
    graph.addEdge(5, 10, 1);

    graph.addEdge(3, 6, 1);
    graph.addEdge(6, 7, 1);
    
    graph.addEdge(3, 8, 1);
    graph.addEdge(8, 9, 1);

    graph.findMinPath(1);

    return 0;
}

