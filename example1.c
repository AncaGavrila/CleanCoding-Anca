#include <stdlib.h>
#include <stdio.h>

typedef struct Node
 {
    int data;
    struct Node *next;
} NODE;

///  graf
typedef struct Graph
 {
    int v;              // varfuri
    int *vis;           // vector de vizite
    struct Node **alst; // liste
} GPH;

/// stiva
typedef struct Stack
{
    int top;
    int scap;
    int *arr;
} STK;

// nodnou
NODE *create_node(int v)
{
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

// muchie
void add_edge(GPH *g, int src, int dest)
{
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

// garf cu v noduri
GPH *create_g(int v)
{
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(sizeof(NODE *) * v); // aloca doar 1 nod
    g->vis = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

// stiva
STK *create_s(int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->top = -1;
    s->scap = scap;
    return s;
}

// se adauga in stiva 
void push(int pshd, STK *s) {
    s->top++;
    s->arr[s->top] = pshd;
}

// DFS
void DFS(GPH *g, STK *s, int v_nr) {
    NODE *aux = g->alst[v_nr];
    g->vis[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);

    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        aux = aux->next;
    }
}

// Introduce muchii
void insert_edges(GPH *g, int edg_nr, int nrv) {
    int src, dest;
    printf("Adauga %d muchii (de la 0 la %d):\n", edg_nr, nrv - 1);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }
}

// vector de vizite 
void wipe(GPH *g, int nrv) {
    for (int i = 0; i < nrv; i++) {
        g->vis[i] = 0;
    }
}


void canbe(GPH *g, int nrv, STK *s1, STK *s2)
 {
    printf("\nVerificare posibila conectare intre noduri (de completat...)\n");
    
}

int main() {
    int nrv;      // nr varfuri
    int edg_nr;   // nr muchii

    printf("Cate noduri are graful? ");
    scanf("%d", &nrv);
    printf("Cate muchii are graful? ");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv); 
    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr, nrv);
    printf("\nDFS din nodul 0: ");
    DFS(g, s1, 0); 
    wipe(g, nrv);
    printf("\nDFS din nodul 1: ");
    DFS(g, s2, 1); 
    printf("\n");

    
    return 0;
}
