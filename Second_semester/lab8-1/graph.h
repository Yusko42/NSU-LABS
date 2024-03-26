#ifndef LAB8_1_NEW_GRAPH_H
#define LAB8_1_NEW_GRAPH_H

#define VERTEX struct vertex
#define GRAPH struct graph

VERTEX {
    int vert; //конечная вершина
    long int weight;
    VERTEX* next;
};

GRAPH {
    int num_vert;
    VERTEX** adj_list;
};

VERTEX* create_vrtx(int vert, int w) {
    VERTEX* new_vrtx = (VERTEX*)malloc(sizeof(VERTEX));

    new_vrtx->vert = vert;
    new_vrtx->weight = w;
    new_vrtx->next = NULL;

    return new_vrtx;
}

GRAPH* create_grph(int vert) {
    GRAPH* new_graph = (GRAPH*)malloc(sizeof(GRAPH));
    new_graph->num_vert = vert;
    new_graph->adj_list = (VERTEX**)malloc(vert * sizeof(VERTEX*));

    for (int i = 0; i < vert; i++)
        new_graph->adj_list[i] = NULL;
    return new_graph;
}

void add_edge(GRAPH* graph, int start, int finish, int weight) {
    VERTEX* new_vrtx = create_vrtx(finish, weight);
    new_vrtx->next = graph->adj_list[start];
    graph->adj_list[start] = new_vrtx;
}

void free_grph(GRAPH* graph) {
    free(graph->adj_list);
    free(graph);
}

#endif //LAB8_1_NEW_GRAPH_H
