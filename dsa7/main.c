#include<stdio.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 26 

typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
}node ;

typedef struct AdjList {
    struct AdjListNode* head;
} list;

typedef struct Graph {
    int numVertices;
    list* array; // array of vertices with lists
} Graph;

list * newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    graph->array = (list*)malloc(numVertices * sizeof(struct AdjList));

    for (int i = 0; i < numVertices; ++i)
        graph->array[i].head = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    node* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// BFS traversal function
void BFS(struct Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};

    // Create a queue for BFS
    int queue[MAX_VERTICES] = {0};
    int front = -1, rear = -1;

    // Mark the current node as visited and enqueue it
    visited[startVertex] = 1;
    queue[++rear] = startVertex;

    while (front != rear) {
        // Dequeue a vertex from queue and print it
        int vertex = queue[++front];
        printf("%d ", vertex);

        // Get all adjacent vertices of the dequeued vertex.
        // If a adjacent has not been visited, then mark it
        // visited and enqueue it
        struct AdjListNode* temp = graph->array[vertex].head;
        while (temp) {
            if (!visited[temp->dest]) {
                visited[temp->dest] = 1;
                queue[++rear] = temp->dest;
            }
            temp = temp->next;
        }
    }
}

// DFS traversal function (using recursion)
void DFSUtil(struct Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    struct AdjListNode* temp = graph->array[vertex].head;
    while (temp) {
        if (!visited[temp->dest])
            DFSUtil(graph, temp->dest, visited);
        temp = temp->next;
    }
}

void DFS(struct Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    DFSUtil(graph, startVertex, visited);
}

int main() {
    // Create a graph with 8 vertices (as seen in the image)
    Graph* graph = createGraph(8);
