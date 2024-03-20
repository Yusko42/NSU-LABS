#ifndef LAB9_DIJKSTRA_H
#define LAB9_DIJKSTRA_H

#define VISITED struct visited

VISITED {
    long int distance;
    int ancestor;
    int passed;
};

void print_vert(VISITED* visited, int n_vert, int start) {
    for (int i = 0; i < n_vert; i++) {
        if (visited[i].distance == LONG_MAX)
            puts("oo ");
        else if (visited[i].distance > INT_MAX)
            puts("INT_MAX+ ");
        else
            printf("%ld ", visited[i].distance - visited[start-1].distance);
    }

    putchar('\n');
}

int min_dist(VISITED* visited, VERTEX* vertex) {
    long int min_len = LONG_MAX;
    int min_idx = -1;
    VERTEX* cur = vertex;

    while (cur) {
        int v = cur->vert;

        if (visited[v].passed == 0 && visited[v].distance <= min_len) {
            min_len = visited[v].distance;
            min_idx = v;
        }
        cur = cur->next;
    }
    return min_idx;
}

void dijkstra(GRAPH* graph, int start, int finish) {
    int n_vert = graph->num_vert;
    int over_cnt = 0;

    VISITED* visited = (VISITED*)malloc(n_vert * sizeof(VISITED));
    VERTEX* vert;

    for (int i = 0; i < n_vert; i++) {
        visited[i].distance = LONG_MAX;
        visited[i].passed = 0;
        visited[i].ancestor = -1;
    }

    visited[start-1].distance = 0;

    vert = create_vrtx(start-1, 0);

    VERTEX* queue = vert;

    while (queue != NULL) {
        int min_edge = min_dist(visited, queue);

        if (min_edge == -1)
            break;

        visited[min_edge].passed = 1;
        VERTEX* temp = graph->adj_list[min_edge];

        while (temp != NULL) {
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


    print_vert(visited, n_vert, start);

    int path[n_vert], p_idx = 0;

    while (curr != -1) {
        path[p_idx++] = curr + 1;
        curr = visited[curr].ancestor;
    }

    if (visited[finish - 1].distance == LONG_MAX) {
        puts("no path");
        return;
    }

    for (int i = 0; i < p_idx; i++) {
        if ((visited[i].distance >= INT_MAX) && (visited[i].distance != LONG_MAX))
            over_cnt++;
    }

    if (over_cnt > 2) {
        puts("overflow");
        return;
    }

    for (int i = 0; i < p_idx; i++) {
        printf("%dl", path[i]);
    }
}


#endif //LAB9_DIJKSTRA_H
