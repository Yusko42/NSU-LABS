#ifndef LAB8_1_GRAPH_H
#define LAB8_1_GRAPH_H

#define EDGE struct edge
#define GRAPH struct graph

#include <malloc.h>

EDGE {
    int start;
    int finish;
    int weight;
};

GRAPH {
    int numb_vert;
    int numb_edge;
    EDGE* edge;
};

GRAPH* create_graph(int vrcs, int edges) {
    GRAPH* new_graph = (GRAPH*)malloc(sizeof(GRAPH));

    new_graph->numb_vert = vrcs;
    new_graph->numb_edge = edges;
    new_graph->edge = (EDGE*)malloc(edges * sizeof(EDGE));

    return new_graph;
}

void add_edge(GRAPH* graph, int start, int finish, int wei, int i) {
    graph->edge[i].start = start;
    graph->edge[i].finish = finish;
    graph->edge[i].weight = wei;
}

#endif //LAB8_1_GRAPH_H
