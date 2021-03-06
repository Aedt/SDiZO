#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <cstring>
#include <limits.h>
using namespace std;


#define V 1000

int minDistance(int dist[], bool sptSet[])
{

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[])
{
    cout << "Vertex \tDistance from Source" << endl;
    for (int i = 0; i < V; i++)
        if (dist[i] == INT_MAX)
        {
            cout << i << " \t\t"
                 << "no connection between vertices" << endl;
        }
        else
        {
            cout << i << " \t\t" << dist[i] << endl;
        }
}

void dijkstra(int **graph, int src)
{
    int dist[V];
    bool sptSet[V];
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V-1; count++)
    {

        int u = minDistance(dist, sptSet);

        sptSet[u] = true;

        for (int v = 0; v < V; v++)

            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
                
            }
    }
    cout << endl;
    printSolution(dist);
}


int main()
{
    clock_t t;
    

    int dist[V];
    int size = 1000;
    int **graf = new int *[size];
    for (int i = 0; i < size; ++i)
    {
        graf[i] = new int[size];
    }
    FILE *file;
    file = fopen("skierowana.txt", "r");

    if (file == NULL)
    {
        printf("Error reading file\n");
        exit(1);
    }

    int newNumber = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            {
                fscanf(file, "%d,", &newNumber);
                graf[i][j] = newNumber;
            }
        }
    }
    fclose(file);

    t = clock();

    dijkstra(graf, 0);

    t = clock() - t;

    double czas = ((double)t) / CLOCKS_PER_SEC;
    cout << "exec time: " << czas << endl;


    // for(int i = 0; i < V; i++){
    //     for(int j = 0; j < V; j++){
    //         cout << graf[i][j] << "; ";
    //     }
    //     cout << endl;
    // }
    
    for (int i = 0; i < size; ++i)
    {
        delete[] graf[i];
    }

    
    delete[] graf;

    getchar();
    return 0;
}