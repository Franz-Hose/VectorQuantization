#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

int NumberOfClusters = 0;
double X[1000] = {0};
double Y[1000] = {0};
double max_X = 0;
double max_Y = 0;

double randomvalue(double maxrandom) // Generiert random float Werte in vorgegebener Range maxrandom/2
{
    return maxrandom*((double)rand()/(double)RAND_MAX-0.5); // maxrandom = 2 ist Bereich -1...1
}




int main()
{
    int Clustertemp = 0;
    double x_temp = 0;
    double y_temp = 0;
    int numberOfPoints = 0;

    while(scanf("%d\n",&Clustertemp) == 1)
    {
        NumberOfClusters = Clustertemp;
        break;
    }

    while(scanf("%lf,%lf\n",&x_temp,&y_temp) == 2)
    {
        X[numberOfPoints] = x_temp;
        Y[numberOfPoints] = y_temp;


        numberOfPoints++;
    }
    /*Normiere den Input */
    for(int k = 0; k<numberOfPoints; k++)
    {
        if(fabs(X[k])> max_X)
        {
            max_X = fabs(X[k]);
        }
        if(fabs(Y[k])> max_Y)
        {
            max_Y = fabs(Y[k]);
        }
    }
    for(int k = 0; k<numberOfPoints; k++)
    {
        X[k] = X[k]/max_X;
        Y[k] = Y[k]/max_Y;
    }
    double *prototypes;
    prototypes = calloc(NumberOfClusters, sizeof(double));
    /* Initialize the prototypes with random values*/
    for(int Cluster = 0; Cluster < NumberOfClusters; Cluster++)
    {
        prototypes[Cluster] = randomvalue(2);
        printf("%f\n",prototypes[Cluster]);
    }

    return 0;
}
