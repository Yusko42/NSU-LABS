#ifndef LAB8_0_KRUSKAL_H
#define LAB8_0_KRUSKAL_H

void make_set(int* parent, int* rank, int x) {
    parent[x] = x;
    rank[x] = 0;
}

int find(int* parent, int x) {
    if (parent[x] == x)
        return x;
    else
        parent[x] = find(parent, x);
}

void union_set(int* parent, int* rank, int a, int b) {
    int id_a = find(parent, a);
    int id_b = find(parent, b);

    if (rank[id_a] < rank[id_b])
        parent[id_a] = id_b;
    else if (rank[id_a] > rank[id_b])
        parent[id_b] = id_a;
    else {
        parent[id_b] = id_a;
        rank[id_a]++;
    }
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
    //Rank: stores the approx value of the height of the subtree
    int* parent = (int*)malloc(vert * sizeof(int));
    int* rank = (int*)malloc(vert * sizeof(int));

    qsort(graph->edge_list, edge, sizeof(graph->edge_list[0]), cmp_edge);

    for (int v = 0; v < vert; v++)
        make_set(parent, rank, v);
    
    int vert_idx = 0;
    int edge_idx= 0;

    while (vert_idx < vert - 1 && edge_idx < edge) {
        EDGE next_edge = graph->edge_list[edge_idx++];

        int x = find(parent, next_edge.start);
        int y = find(parent, next_edge.finish);

        //Checking for a cycle
        if (x != y){
            result[vert_idx++] = next_edge;
            union_set(parent, rank, x, y);
        }
    }

    if (vert_idx < vert - 1) {
        puts("no spanning tree");
        free(parent);
        free(rank);
        exit(0);
    }

    for (int i = 0; i < vert_idx; ++i)
        if (result[i].start < result[i].finish)
            printf("%d %d\n", result[i].start + 1, result[i].finish + 1);
        else
            printf("%d %d\n", result[i].finish + 1, result[i].start + 1);

    free(parent);
    free(rank);
}

#endif //LAB8_0_KRUSKAL_H
