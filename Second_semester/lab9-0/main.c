#include <stdio.h>
#include "graph.h"
#include "dijkstra.h"

#define MIN 0
#define MAX_VRT 5000
#define MAX_EDGE (vert * (vert + 1) / 2)

int errors(int vert, int start, int finish, int edge) {
    if (vert < MIN || vert > MAX_VRT) {
        puts("bad number of vertices");
        return -1;
    }
    if (edge < MIN || edge > MAX_EDGE) {
        puts("bad number of edges");
        return -1;
    }
    if ((start < 1 || start > vert) || (finish < 1 || finish > vert)) {
        puts("bad vertex");
        return -1;
    }

    return 0;
}

int main() {
    int n_vert, start, finish, m_edge;
    int cnt_edge = 0;
    scanf_s("%d", &n_vert);
    scanf_s("%d %d", &start, &finish);
    scanf_s("%d", &m_edge);

    if (errors(n_vert, start, finish, m_edge) == -1)
        return 0;

    GRAPH* graph = create_grph(n_vert);

    for (int i = 0; i < m_edge; i++) {
        int l_start, l_finish;
        long int l_len;
        scanf_s("%d %d %ld", &l_start, &l_finish, &l_len);


        add_edge(graph, l_start, l_finish, l_len);
        add_edge(graph, l_finish, l_start, l_len);
        cnt_edge++;
    }

    if (cnt_edge != m_edge) {
        puts("bad number of lines");
        return 0;
    }

    dijkstra(graph, start, finish);

    free(graph); // подумать об очистке всего тут
    return 0;
}


