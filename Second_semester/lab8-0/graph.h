#ifndef LAB8_0_GRAPH_H
#define LAB8_0_GRAPH_H

#define EDGE struct edge
#define GRAPH struct graph

EDGE {
    int start;
    int finish;
    int weight;
};

GRAPH {
    int num_vert;
    EDGE* edge_list;
};

GRAPH* create_grph(int vert) {
    GRAPH* new_graph = (GRAPH*)malloc(sizeof(GRAPH));
    new_graph->num_vert = vert;
    new_graph->edge_list = (EDGE*)malloc(vert * sizeof(EDGE));

    return new_graph;
}

void add_edge(GRAPH* graph, int start, int finish, int weight, int i) {
    graph->edge_list[i].start = start;
    graph->edge_list[i].finish = finish;
    graph->edge_list[i].weight = weight;
}

#endif //LAB8_0_GRAPH_H
