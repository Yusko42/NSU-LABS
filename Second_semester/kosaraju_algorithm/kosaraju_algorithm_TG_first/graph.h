#ifndef KOSARAJU_ALG_GRAPH_H
#define KOSARAJU_ALG_GRAPH_H

#define VERTEX struct vertex
#define GRAPH struct graph

struct vertex {
    int vert;
    VERTEX* next;
};

struct graph {
    int vertices;
    VERTEX** adj_list;
};

GRAPH* create_graph(int verts) {
    GRAPH* new_graph = (GRAPH*)malloc(sizeof(GRAPH));
    new_graph->vertices = verts;
    new_graph->adj_list = (VERTEX**)malloc(verts * sizeof(VERTEX*));
    for (int i = 0; i < verts; i++)
        new_graph->adj_list[i] = NULL;
    return new_graph;
}

VERTEX* create_vrtx(int finish){
    VERTEX* new_vertx = (VERTEX*)malloc(sizeof(VERTEX));
    new_vertx->vert = finish;
    new_vertx->next = NULL;
    return new_vertx;
}

void add_edge(GRAPH* graph, int start, int finish) {
    VERTEX* new_vrtx = create_vrtx(finish - 1);
    new_vrtx->next = graph->adj_list[start - 1];
    graph->adj_list[start - 1] = new_vrtx;
}

#endif //KOSARAJU_ALG_GRAPH_H
