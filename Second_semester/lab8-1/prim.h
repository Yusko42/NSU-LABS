#ifndef LAB8_1_NEW_PRIM_H
#define LAB8_1_NEW_PRIM_H

#include <stdbool.h>

//Searchinf for the min weight from "the table"
int min_wght(int* weight, bool* passed, int vert) {
    int min = LONG_MAX;
    int min_idx;

    for (int i = 0; i < vert; ++i) {
        if (passed[i] == false && weight[i] < min) {
            min = weight[i];
            min_idx = i;
        }
    }

    return min_idx;
}

void prim(GRAPH* graph) {
    int vert = graph->num_vert;

    int* parent = (int*)malloc(vert * sizeof(int));
    int* weight = (int*)malloc(vert * sizeof(int));
    bool passed[vert];

    for (int idx = 0; idx < vert; ++idx) {
        weight[idx] = LONG_MAX;
        passed[idx] = false;
    }

    //Start - the 1st vertex
    weight[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < vert; i++) {
        int u = min_wght(weight, passed, vert);
        passed[u] = true;

        VERTEX* vertex = graph->adj_list[u];

        //Comparing the edge weight values
        while (vertex != NULL) {
            int v = vertex->vert;
            if (passed[v] == false && vertex->weight < weight[v]) {
                weight[v] = vertex->weight;
                parent[v] = u;
            }
            vertex = vertex->next;
        }
    }

    //Searching for the min edge weight
    int min_wght = LONG_MAX;
    for (int i = 1; i < vert; i++)
        if (weight[i] < min_wght)
            min_wght = weight[i];

    //Printing vertices of an edge with the min weight
    for (int idx = 1; idx < vert; idx++)
        if (weight[idx] == min_wght) {
            if (parent[idx] < idx)
                printf("%d %d \n", parent[idx] + 1, idx + 1);
            else
                printf("%d %d \n", idx + 1, parent[idx] + 1);
        }
}

#endif //LAB8_1_NEW_PRIM_H
