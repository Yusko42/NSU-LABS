#ifndef LAB8_0_PRIM_H
#define LAB8_0_PRIM_H

void make_set(int* parent, int x) {
    parent[x] = x;
}

int find(int* parent, int x) {
    if (parent[x] == x)
        return x;
    else
        parent[x] = find(parent, x);
}

int cmp_edge(const void* a, const void* b) {
    EDGE* edge1 = (EDGE*)a;
    EDGE* edge2 = (EDGE*)b;

    return (edge1->weight - edge2->weight);
}

void kruskal(GRAPH* graph, int edge) {
    int vert = graph->num_vert;
    EDGE* result= (EDGE*)malloc(vert * sizeof(EDGE));

    //Parent: stores the ancestor of the vertex
    int* parent = (int*)malloc(vert * sizeof(int));

    qsort(graph->edge_list, edge, sizeof(graph->edge_list[0]), cmp_edge);

    for (int v = 0; v < vert; v++)
        make_set(parent, v);
    
    int vert_idx = 0;
    int edge_idx= 0;

    while (vert_idx < vert - 1 && edge_idx < edge) {
        EDGE next_edge = graph->edge_list[edge_idx++];

        int x = find(parent, next_edge.start);
        int y = find(parent, next_edge.finish);

        //Checking for a cycle
        if (x != y){
            result[vert_idx++] = next_edge;
            parent[y] = x;
        }
    }

    if (vert_idx < vert - 1) {
        puts("no spanning tree");
        free(parent);
        exit(0);
    }

    for (int i = 0; i < vert_idx; ++i)
        if (result[i].start < result[i].finish)
            printf("%d %d\n", result[i].start + 1, result[i].finish + 1);
        else
            printf("%d %d\n", result[i].finish + 1, result[i].start + 1);

    free(parent);
}

#endif //LAB8_0_PRIM_H
