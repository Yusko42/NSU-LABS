#ifndef LAB8_1_PRIM_H
#define LAB8_1_PRIM_H

typedef struct {
    int* key;
    int* parent;
    int* passed;
} S_TREE;

int min_key(S_TREE* tree, int numb_edge) {
    int min_wght = LONG_MAX;
    int min_idx;

    for (int i = 0; i < numb_edge; i++) {
        if (tree->passed[i] == 0 && tree->key[i] < min_wght) {
            min_wght = tree->key[i];
            min_idx = i;
        }
    }
    return min_idx;
}

void prim(GRAPH* graph) {
    int n_edge = graph->numb_edge;

    S_TREE* tree = (S_TREE*)malloc(sizeof(S_TREE));
    tree->key = (int*)malloc(n_edge * sizeof(int));
    tree->parent = (int*)malloc(n_edge * sizeof(int));
    tree->passed = (int*)malloc(n_edge * sizeof(int));

    for (int i = 0; i < n_edge; i++) {
        tree->key[i] = LONG_MAX;
        tree->passed[i] = 0;
    }

    tree->key[0] = 0;
    tree->parent[0] = -1;

    for (int cnt = 0; cnt < n_edge - 1; cnt++) {
        int u = min_key(tree, n_edge);
        tree->passed[u] = 1;

        for (int v = 0; v < n_edge; v++) {
            if (graph->edge[v].start == u + 1 &&
            tree->passed[graph->edge[v].finish - 1] == 0 &&
            graph->edge[v].weight < tree->key[graph->edge[v].finish - 1]) {
                tree->parent[graph->edge[v].finish - 1] = u;
                tree->key[graph->edge[v].finish - 1] = graph->edge[v].weight;
            }
            else if (graph->edge[v].finish == u + 1 &&
            tree->passed[graph->edge[v].start - 1] == 0 &&
            graph->edge[v].weight < tree->key[graph->edge[v].start - 1]) {
                tree->parent[graph->edge[v].start - 1] = u;
                tree->key[graph->edge[v].start - 1] = graph->edge[v].weight;
            }
        }
    }

    for (int i = 1; i < n_edge; i++) {
        printf("%d %d\n", tree->parent[i] + 1, i + 1);
    }

}


#endif //LAB8_1_PRIM_H
