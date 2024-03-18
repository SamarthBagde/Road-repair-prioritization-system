#include <stdio.h>
#include <stdlib.h>

#define maxInt 100

struct roadSegment
{
    int startPoint;
    int endPoint;
    int potholesCount;
    int trafficDencity; // rating fro 1 - 10 // good - worst
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

    int priority = (-10 * road[index].potholesCount) + (-7 * road[index].roadCondition) + (-5 * road[index].trafficDencity);
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
        scanf("%d", &road[i].trafficDencity);
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

int main()
{

    int numOfCheckPoints /* V */, numOfRoads /*edges*/;
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

    printf("\n\n");
    dispalyG(G);

    return 0;
}