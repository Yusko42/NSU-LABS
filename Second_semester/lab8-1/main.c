#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"
#include "prim.h"

#define VERT_MAX 5000
#define EDGE_MAX vert*(vert-1)/2
#define WGHT_MAX INT_MAX

// ��������, �㦭� ��२�������� vertex � edge
// � ��

int main() {
    int vert, edge;
    int cnt_chk = 0;

    scanf_s("%d", &vert);
    scanf_s("%d", &edge);

    GRAPH* graph = create_grph(vert);

    //��� �訡��
    if (vert < 0 || vert > VERT_MAX){
        puts("bad number of vertices");
        return 0;
    }

    if (edge < 0 || edge > EDGE_MAX){
        puts("bad number of edges");
        return 0;
    }

    for (int i = 0; i < edge; i++) {
        int start, finish;
        long int weight;
        scanf_s("%d %d %ld", &start, &finish, &weight);

        //��� �訡��
        if ((start < 1 || start > vert) || (finish < 1 || finish > vert)) {
            puts("bad vertex");
            return 0;
        }

        if (weight < 0 || weight > WGHT_MAX) {
            puts("bed length");
            return 0;
        }

        add_edge(graph, finish-1, start-1, weight);
        add_edge(graph, start-1, finish-1, weight);
        cnt_chk++;
    }

    //�� �訡�� (�஢�ઠ)
    if (cnt_chk > edge) {
        puts("bad number of lines");
        return 0;
    }

    prim(graph);

    return 0;
}
