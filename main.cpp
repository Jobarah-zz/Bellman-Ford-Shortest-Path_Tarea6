#include "Test.h"
#include <string.h>
#include <limits.h>
using namespace std;
struct Edge
{
    int src, dest, weight;
};

struct Graph
{
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );

    return graph;
}

int* BellmanFord(struct Graph* graph, int src)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];
    int *res = new int[V];

    for (int i = 0; i < V; i++){
        dist[i] = INT_MAX;
        res[i] = NULL;
    }
    dist[src] = 0;

    for (int i = 1; i <= V-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
                dist[v] = dist[u] + weight;
                res[v]=u;
            }
        }
    }

    for (int i = 0; i < E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            cout<<"Negative weight cycle found in graph"<<endl;
    }
    return res;
}

int getSizeVertices(int** graph, int size){
    int i = 0, j = 1, cont = 0;

    while (i < size) {
        while (j < size) {
            if(graph[i][j] != -1)
                cont += 1;
            j++;
        }
        j = 1;
        i++;
    }
    return cont;
}

int* getShortestPath(int** graph, int size, int origin)
{
    int E = getSizeVertices(graph, size);
    struct Graph* graphs = createGraph(size, E);
    int i = 0, j = 1, cont = 0;

    while (i < size) {

        while (j < size) {

            if(graph[i][j]!=-1){

                graphs->edge[cont].src = i;
                graphs->edge[cont].dest = j;
                graphs->edge[cont].weight = graph[i][j];
                cont +=1;
            }

            j++;
        }

        j = 1;
        i++;
    }
    return BellmanFord(graphs, 0);
}

int main ()
{
    test();
    return 0;
}