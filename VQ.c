#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int NumberOfClusters = 0;
double X[1000] = {0};
double Y[1000] = {0};
double max_X = 0;
double max_Y = 0;

int main()
{
    int Clustertemp = 0;
    double x_temp = 0;
    double y_temp = 0;
    int numberOfPoints = 0;


    while(scanf("%i",&Clustertemp) == 1)
    {
        NumberOfClusters = Clustertemp;
    }
    while(scanf("%lf,%lf",&x_temp,&y_temp) == 2)
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

}
