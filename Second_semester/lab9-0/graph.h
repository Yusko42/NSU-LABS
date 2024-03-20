#ifndef LAB9_GRAPH_H
#define LAB9_GRAPH_H

#include <limits.h>
#include <malloc.h>

#define VERTEX struct vertex
#define GRAPH struct graph

VERTEX {
    int vert;
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

GRAPH* create_grph(int number) {
    GRAPH* new_graph = (GRAPH*)malloc(sizeof(GRAPH));
    new_graph->num_vert = number;
    new_graph->adj_list = (VERTEX**)malloc(number * sizeof(VERTEX*));

    for (int i = 0; i < number; i++)
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

#endif //LAB9_GRAPH_H
