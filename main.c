#include <stdio.h>
#include <stdlib.h>
#include "priority.h"

#define maxInt 100

struct roadSegment
{
    int startPoint;
    int endPoint;
    int potholesCount;
    int trafficDensity; // rating fro 1 - 10 // good - worst
    int roadCondition;
    int weight;
};

struct listNode
{
    int ver;
    int w;
    struct listNode *next;
};
struct graph
{
    int V;
    struct listNode **A;
};

struct graph *creteGraph(int v)
{
    struct graph *g = (struct graph *)malloc(sizeof(struct graph));
    g->V = v;
    g->A = (struct listNode **)malloc(v * sizeof(struct listNode *));
    for (int i = 0; i < v; i++)
    {
        g->A[i] = NULL;
    }
    return g;
}

struct listNode *createNew(int data, int w)
{
    struct listNode *n = (struct listNode *)malloc(sizeof(struct listNode));
    n->ver = data;
    n->w = w;
    n->next = NULL;
    return n;
}

int calculatePriority(struct roadSegment road[], int index)
{
    struct priorityValues p = getPriorityValues();
    int priority = (p.pot * road[index].potholesCount) + (p.road * road[index].roadCondition) + (p.traffic * road[index].trafficDensity);
    return priority;
}

void adjList(struct graph *g, int v, int e, struct roadSegment *road)
{

    struct listNode *ptr, *newV;
    printf("Enter paths details : \n\n");
    for (int i = 0; i < e; i++)
    {
        int a, b;
        printf("Enter road %d (startpoint - endpoint) : \n", i);
        scanf("%d %d", &a, &b);
        road[i].startPoint = a;
        road[i].endPoint = b;

        printf("Enter pothole count : \n");
        scanf("%d", &road[i].potholesCount);
        printf("Enter traffic dencity [1 (low) - 10 (high)] : \n");
        scanf("%d", &road[i].trafficDensity);
        printf("Enter road condition [1 (Good) - 10 (Worst)] : \n");
        scanf("%d", &road[i].roadCondition);
        printf("\n\n");
        int priority = calculatePriority(road, i);
        road[i].weight = priority;

        newV = createNew(a, priority);
        ptr = g->A[b];
        if (ptr == NULL)
        {
            g->A[b] = newV;
        }
        else
        {
            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }
            ptr->next = newV;
        }

        newV = createNew(b, priority);
        ptr = g->A[a];
        if (ptr == NULL)
        {
            g->A[a] = newV;
        }
        else
        {
            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }
            ptr->next = newV;
        }
    }
}

void dispalyG(struct graph *g)
{
    for (int i = 0; i < g->V; i++)
    {
        struct listNode *ptr = g->A[i];
        printf("%d ||  ", i);
        while (ptr != NULL)
        {
            printf("[v: %d | w: %d] -> ", ptr->ver, ptr->w);
            ptr = ptr->next;
        }
        printf("NULL");
        printf("\n");
    }
}

int findParent(int i, int parent[])
{
    while (i != parent[i])
    {
        i = parent[i];
    }
    return i;
}

void uni(int i, int j, int parent[])
{

    int a = findParent(i, parent);
    int b = findParent(j, parent);
    parent[b] = a;
}

void kruskals(struct graph *g, int v, int parent[], char names[maxInt][maxInt], struct roadSegment *road, int numOfRoads)
{
    int a, b, min, ne = 0, minWeight = 0;

    printf("The priority order of the road repair operations suggested by the system is : \n\n");
    while (ne < v - 1)
    {
        min = 999;
        for (int i = 0; i < v; i++)
        {
            struct listNode *ptr = g->A[i];
            while (ptr != NULL)
            {
                if (ptr->w < min && findParent(ptr->ver, parent) != findParent(i, parent))
                {
                    min = ptr->w;
                    a = i;
                    b = ptr->ver;
                }
                ptr = ptr->next;
            }
        }
        uni(a, b, parent);
        printf("Road : %s - %s\n", names[a], names[b]);
        for (int i = 0; i < numOfRoads; i++)
        {
            if ((a == road[i].startPoint && b == road[i].endPoint) || (b == road[i].startPoint && a == road[i].endPoint))
            {
                printf("Pothole Count : %d\tTraffic Density : %d\tRoad Condition : %d\n\n", road[i].potholesCount, road[i].trafficDensity, road[i].roadCondition);
                break;
            }
        }
        ne++;
        minWeight += min;
    }
}

int main()
{

    int numOfCheckPoints, numOfRoads;
    char checkPoimtsName[maxInt][maxInt];

    printf("Enter number of check points : \n");
    scanf("%d", &numOfCheckPoints);

    for (int i = 0; i < numOfCheckPoints; i++)
    {
        printf("Enter name of check point %d : ", i);
        scanf("%s", &checkPoimtsName[i]);
    }
    printf("\n");

    printf("Enter number of Paths (Roads) want to repair : \n");
    scanf("%d", &numOfRoads);
    struct roadSegment *road = (struct roadSegment *)malloc(numOfRoads * sizeof(struct roadSegment));

    struct graph *G = creteGraph(numOfCheckPoints);
    adjList(G, numOfCheckPoints, numOfRoads, road);

    int parent[numOfCheckPoints + 1];
    for (int i = 0; i <= numOfCheckPoints; i++)
    {
        parent[i] = i;
    }

    printf("\n\n");
    kruskals(G, numOfCheckPoints, parent, checkPoimtsName, road, numOfRoads);

    return 0;
}