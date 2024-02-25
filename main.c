#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define maxInt 100

struct roadSegment
{
    int startPoint;
    int endPoint;
    int potholesCount;
    int trafficDencity; // rating fro 1 - 10 // low - high
    int roadCondition;
    int connectivityImportance; // is there any alternative way for it
};

int calculatePriority(struct roadSegment road[], int index)
{

    int priority = (-10 * road[index].potholesCount) + (-7 * road[index].roadCondition) + (-5 * road[index].trafficDencity) + (-3 * road[index].connectivityImportance);
    return priority;
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

    // adj matrix init
    int adjMatrix[numOfCheckPoints][numOfCheckPoints];
    struct roadSegment road[numOfRoads];

    for (int i = 0; i < numOfCheckPoints; i++)
    {
        for (int j = 0; j < numOfCheckPoints; j++)
        {
            adjMatrix[i][j] = 99999;
        }
    }
    //

    printf("Enter paths details : \n");
    for (int i = 0; i < numOfRoads; i++)
    {
        printf("Enter road %d (startpoint - endpoint) : \n", i);
        scanf("%d %d", &road[i].startPoint, &road[i].endPoint);
        printf("Enter pothole count : \n");
        scanf("%d", &road[i].potholesCount);
        printf("Enter traffic dencity [1 (low) - 10 (high)] : \n");
        scanf("%d", &road[i].trafficDencity);
        printf("Enter road condition [1 (Good) - 10 (Worst)] : \n");
        scanf("%d", &road[i].roadCondition);
        printf("Enter road connectivity [1 (Good) - 10 (Not good)] : \n");
        scanf("%d", &road[i].connectivityImportance);

        int priority = calculatePriority(road, i);

        adjMatrix[road[i].startPoint][road[i].endPoint] = priority;
        adjMatrix[road[i].endPoint][road[i].startPoint] = priority;

        printf("\n");
    }

    for (int i = 0; i < numOfRoads; i++)
    {
        printf("Road %d : %s to %s\n", i, checkPoimtsName[road[i].startPoint], checkPoimtsName[road[i].endPoint]);
    }

    for (int i = 0; i < numOfCheckPoints; i++)
    {
        for (int j = 0; j < numOfCheckPoints; j++)
        {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}