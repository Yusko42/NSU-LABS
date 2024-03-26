#ifndef LAB8_1_NEW_PRIM_H
#define LAB8_1_NEW_PRIM_H

int min_wght(int weight[], bool passed[], int vert) {
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

    int parent[vert];
    int weight[vert];
    bool passed[vert];
    //Надо переделать в дин. массивы, но пока ок

    for (int idx = 0; idx < vert; ++idx) {
        weight[idx] = LONG_MAX;
        passed[idx] = false;
    }

    //Начинаем с 1-й вершины
    weight[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < vert - 1; ++i) {
        int u = min_wght(weight, passed, vert);
        passed[u] = true; //мы ждем перемен (названий переменных)

        VERTEX* vertex = graph->adj_list[u];

        while (vertex!=NULL) {
            int v = vertex->vert;
            if (passed[v] == false && vertex->weight < weight[v]) {
                weight[v] = vertex->weight;
                parent[v] = u;
            }
            vertex = vertex->next;
        }
    }

    int min_wght = LONG_MAX;
    for (int i = 1; i < vert; i++)
        if (weight[i] < min_wght)
            min_wght = weight[i];

    for (int idx = 1; idx < vert; idx++)
        if (weight[idx] == min_wght)
            printf("%d %d \n", parent[idx] + 1, idx + 1);

}

#endif //LAB8_1_NEW_PRIM_H
