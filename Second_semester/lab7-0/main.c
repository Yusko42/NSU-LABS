#include <stdio.h>
#include <malloc.h>

#define VTX_MAX 2000
#define EDGE_MAX vert * (vert - 1) / 2

#define GRAPH struct graph
#define LIST struct list

LIST {
    int dest;
    LIST* next;
};

GRAPH {
    int vert;
    LIST** adj_list;
};

//In case there is a cycle in the graph
void impsort(GRAPH* graph, int* visited, int* stack) {
    printf_s("impossible to sort");
    free(stack);
    free(visited);
    free(graph->adj_list);
    free(graph);
    exit(0);
}

//Depth-first search
void dfs(GRAPH* graph, int* visited, int* stack, int vert, int* idx) {
    visited[vert] = 1;
    LIST* cur_vrt = graph->adj_list[vert];

    while (cur_vrt) {
        if (visited[cur_vrt->dest] == 0)
            dfs(graph, visited, stack, cur_vrt->dest, idx);
        else if (visited[cur_vrt->dest] == 1){
            impsort(graph, visited, stack);
        }
        cur_vrt = cur_vrt -> next;
    }

    visited[vert] = 2;
    stack[(*idx)++] = vert;
}

void topsort(GRAPH* graph) {
    int num_vert = graph->vert;
    int stack_idx = 0;
    int* visited = NULL;
    int* stack = NULL;

    visited = (int*)malloc(num_vert * sizeof(int));
    stack = (int*)malloc(num_vert * sizeof(int));

    for (int i = 0; i < num_vert; i++)
        visited[i] = 0;

    for (int i = 0; i < num_vert; i++) {
        if (visited[i] == 0)
            dfs(graph, visited, stack, i, &stack_idx);
    }

    //Printing the result from the stack
    while (stack_idx)
        printf("%d ", stack[--stack_idx] + 1);

    free(visited);
    free(stack);
}

GRAPH* create_grph(int vert) {
    GRAPH* new_graph = (GRAPH*)malloc(sizeof(GRAPH));
    new_graph->vert = vert;
    new_graph->adj_list = (LIST**)malloc(vert * sizeof(LIST*));

    for (int i = 0; i < vert; i++)
        new_graph->adj_list[i] = NULL;
    return new_graph;
}

LIST* create_vrtx(int vert) {
    LIST* new_list = (LIST*)malloc(sizeof(LIST));

    new_list->dest = vert;
    new_list->next = NULL;

    return new_list;
}

void add_edge(GRAPH* graph, int start, int finish) {
    LIST* new_vrtx = create_vrtx(finish - 1);
    new_vrtx->next = graph->adj_list[start - 1];
    graph->adj_list[start - 1] = new_vrtx;
}

int main() {
    int vert, edges;
    int start, finish;
    int check = 0;

    scanf_s("%d", &vert);
    scanf_s("%d", &edges);

    if (vert < 0 || vert > VTX_MAX) {
        puts("bad number of vertices");
        return 0;
    }

    if (edges < 0 || edges > EDGE_MAX) {
        puts("bad number of edges");
        return 0;
    }

    GRAPH* graph = NULL;
    graph = create_grph(vert);

    for (int i = 0; i < edges; i++) {
        scanf_s("%d %d", &start, &finish);
        if ((start < 1 || start > vert) || (finish < 1 || finish > vert)) {
            puts("bad vertex");
            return 0;
        }

        add_edge(graph, start, finish);
        check++;
    }

    if (check < edges) {
        puts("bad number of lines");
        return 0;
    }

    topsort(graph);
    free(graph->adj_list);
    free(graph);

    return 0;
}
