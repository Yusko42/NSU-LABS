#ifndef LAB9_DIJKSTRA_H
#define LAB9_DIJKSTRA_H

#define VISITED struct visited

// Dijkstra data (данные по алгоритму: посещенные узлы, мин. длины до них)
VISITED {
    long int distance;
    int ancestor;
    int passed;
};

// Переименовать v

int min_dist(VISITED* visited, VERTEX* vertex) {
    long int min_len = LONG_MAX;
    int min_index;
    VERTEX* cur = vertex;

    while (cur) {
        int v = cur->vert;

        if (visited[v].passed == 0 && visited[v].distance <= min_len) {
            min_len = visited[v].distance;
            min_index = v;
        }
        cur = cur->next;
    }
    return min_index;
}

void dijkstra(GRAPH* graph, int start, int finish) {
    int n_vert = graph->num_vert;

    VISITED* visited = (VISITED*)malloc(n_vert * sizeof(VISITED));
    VERTEX* vert = malloc(sizeof(VERTEX));

    for (int i = 0; i < n_vert; i++) {
        visited[i].distance = LONG_MAX;
        visited[i].passed = 0;
        visited[i].ancestor = -1;
    }

    //Нужно ли вводить пер., типа start_idx?
    visited[start - 1].distance = 0;

    //За этим проследить: тут могут быть ошибки из-за минуса
    //а еще тут логичнее через create_vtrx сделать, все равно тут NULL
    vert->vert = start - 1;
    vert->weight = 0;
    vert->next = NULL;

    //вершина, которая не посещена (пока что)
    VERTEX* queue = vert;

    //Все здесь переименовать
    // Да и в целом переиначить, можно бы кое-что и поменять...
    // Ну или вынести за пределы цикла, как функцию
    while (queue) {
        int min_edge = min_dist(visited, queue);

        if (min_edge == -1)
            break;

        visited[min_edge].passed = 1;
        VERTEX* temp = graph->adj_list[min_edge];

        while (temp) {
            int adj_vert = temp->vert - 1;
            int smlr_path = visited[min_edge].distance + temp->weight;

            if (visited[adj_vert].distance >= smlr_path) {
                visited[adj_vert].distance = smlr_path;
                visited[adj_vert].ancestor = min_edge;

                VERTEX* new_v = create_vrtx(adj_vert, smlr_path);
                new_v->next = queue;

                queue = new_v;
            }
            temp = temp->next;
        }
    }
    int curr = finish - 1;

    while (curr != -1) {
        path[]
    }
    //здесь проверка
}


#endif //LAB9_DIJKSTRA_H
