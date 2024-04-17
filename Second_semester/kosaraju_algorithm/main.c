#include <stdio.h>
#include <malloc.h>

#include "graph.h"

#define VTX_MAX 2000
#define EDGE_MAX verts * (verts - 1) / 2

//A DFS traversal for the main graph, adding vertices to stack by priority
void dfs_graph(GRAPH* graph, int* visited, int* stack, int vert, int* idx) {
    visited[vert] = 1;
    VERTEX* cur_vrt = graph->adj_list[vert];

    while (cur_vrt) {
        if (visited[cur_vrt->vert] == 0)
            dfs_graph(graph, visited, stack, cur_vrt->vert, idx);
        cur_vrt = cur_vrt -> next;
    }
    stack[(*idx)++] = vert;
}

//A DFS traversal for the transpose graph, printing the vertices of the SSC
void dfs_trans(GRAPH* graph, int* visited, int vert) {
    visited[vert] = 1;
    VERTEX* cur_vrt = graph->adj_list[vert];

    while (cur_vrt) {
        if (visited[cur_vrt->vert] == 0)
            dfs_trans(graph, visited, cur_vrt->vert);
        cur_vrt = cur_vrt->next;
    }
    printf("%d ", vert + 1);
}

//The Kosaraju Algoritm
void kosaraju(GRAPH* graph, GRAPH* trans_graph){
    int verts = graph->vertices;
    int stack_idx = 0;
    int* visited = (int*)calloc(verts, sizeof(int));
    int* stack = (int*)malloc(verts * sizeof(int));

    for (int i = 0; i < verts; i++) {
        if (visited[i] == 0)
            dfs_graph(graph, visited, stack, i, &stack_idx);
    }

    //Resetting data on visited vertices (for the next DFS)
    for (int i = 0; i < verts; i++)
        visited[i] = 0;

    printf("Edges of the SCCs:\n");

    while (stack_idx--) {
        int stack_vert = stack[stack_idx];
        if (!visited[stack_vert]) {
            dfs_trans(trans_graph, visited, stack_vert);
            printf("\n");
        }
    }
    free(visited);
    free(stack);
}

int main() {
    int verts, edges;
    int start, finish;

    scanf_s("%d", &verts);
    scanf_s("%d", &edges);

    if (verts < 0 || verts > VTX_MAX) {
        puts("bad number of vertices");
        return 0;
    }

    if (edges < 0 || edges > EDGE_MAX) {
        puts("bad number of edges");
        return 0;
    }

    GRAPH* graph = create_graph(verts);
    GRAPH* trans_graph = create_graph(verts);

    for (int i = 0; i < edges; i++) {
        scanf_s("%d %d", &start, &finish);

        if ((start < 0 || start > verts) || (finish < 0 || finish > verts)) {
            puts("bad vertex");
            return 0;
        }
        add_edge(graph, start, finish);
        add_edge(trans_graph, finish, start);
    }

    kosaraju(graph, trans_graph);

    free(graph);
    free(trans_graph);
    return 0;
}
