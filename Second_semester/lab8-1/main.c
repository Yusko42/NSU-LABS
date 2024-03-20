#include <stdio.h>
#include "graph.h"
#include "prim.h"

#define MIN 0
#define MAX_VRT 5000
#define MAX_EDGE (vert * (vert + 1) / 2)

int errors(int vert, int edge) {
    if (vert < MIN || vert > MAX_VRT) {
        puts("bad number of vertices");
        return -1;
    }
    if (edge < MIN || edge > MAX_EDGE) {
        puts("bad number of edges");
        return -1;
    }

    return 0;
}

int main() {
    int n_vert, m_edge;
    int start, finish, len;
    int cnt = 0, sp_cnt = 0;

    scanf_s("%d", &n_vert);
    scanf_s("%d", &m_edge);

    //тут ошибки прописать надо
    if (errors(n_vert, m_edge))
        return 0;

    GRAPH* graph = create_graph(n_vert, m_edge);

    for (int i = 0; i < m_edge; i++) {
        scanf_s("%d %d %d", &start, &finish, &len);

        if ((start < 1 || start > n_vert) || (finish < 1 || finish > n_vert)) {
            printf("bad vertex");
            return 0;
        }

        if ((len < 0) || (len > INT_MAX)) {
            printf("bad length");
            return 0;
        }

        if (start == n_vert || finish == n_vert)
            sp_cnt++;

        add_edge(graph, start, finish, len, i);
        cnt++;
    }

    if (cnt < m_edge) {
        puts("bad number of lines");
        return 0;
    }

    if (sp_cnt == 0) {
        puts("no spanning tree");
        return 0;
    }

    //уже в приме сделать это
    prim(graph);

    return 0;
}
