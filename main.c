#include <stdio.h>
#include <stdlib.h>

typedef struct Node 
{
    int data;
    struct Node *next;
} Node;

typedef struct Graph 
{
    int vertices;
    int *visited;
    Node **adjacency_lists;
} Graph;

Node* create_node(int v) 
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

Graph* create_graph(int vertices) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;

    graph->adjacency_lists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++)
     {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
     return graph;
}

void add_edge(Graph *graph, int src, int dest) {
    Node *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insert_edges(Graph *graph, int num_edges) {
    int src, dest;
    printf("Adauga %d muchii (indexare de la 0):\n", num_edges);
    for (int i = 0; i < num_edges; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

int is_empty(Node *queue) {
    return queue == NULL;
}

void enqueue(Node **queue, int data) {
    Node *new_node = create_node(data);
    if (*queue == NULL) 
    {
        *queue = new_node;
    } else {
        Node *temp = *queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(Node **queue) {
    if (*queue == NULL) return -1;
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void wipe_visited(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

void DFS(Graph *graph, int vertex) {
    Node *adj_list = graph->adjacency_lists[vertex];
    Node *temp = adj_list;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(Graph *graph, int start_vertex) {
    Node *queue = NULL;

    graph->visited[start_vertex] = 1;
    enqueue(&queue, start_vertex);

    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        Node *temp = graph->adjacency_lists[current];
        while (temp != NULL) {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main()
 {
    int num_vertices, num_edges, start_vertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &num_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &num_edges);

    Graph *graph = create_graph(num_vertices);
    insert_edges(graph, num_edges);

    printf("De unde incepem DFS? ");
    scanf("%d", &start_vertex);
    printf("Parcurgere DFS: ");
    DFS(graph, start_vertex);

    wipe_visited(graph);
    printf("\n");

    printf("De unde incepem BFS? ");
    scanf("%d", &start_vertex);
    printf("Parcurgere BFS: ");
    BFS(graph, start_vertex);
    printf("\n");

    return 0;
}
