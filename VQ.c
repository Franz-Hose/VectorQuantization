#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


#define eta 0.01
#define threshold 0.00001
int NumberOfClusters = 0;
double X[1000] = {0};
double Y[1000] = {0};
double max_X = 0;
double max_Y = 0;
double *prototypesX, *prototypesY;
int currentWinner = 0;

void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shufflearray(int arr[], int n)
// A function to generate a random permutation of arr[]
/* source from http://www.geeksforgeeks.org/shuffle-a-given-array/
                       this is a function to shuffle the array of inputs for every new epoch */
{


    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand ( time(NULL) );

    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = n-1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);

        // Swap arr[i] with the element at random index
        swap(&arr[i], &arr[j]);
    }
}



double randomvalue(double maxrandom) // Generiert random float Werte in vorgegebener Range maxrandom/2
{
    return maxrandom*((double)rand()/(double)RAND_MAX-0.5); // maxrandom = 2 ist Bereich -1...1
}

double euclideanDistance(double X1, double X2, double Y1, double Y2) // Funktion um die Eukildische Distanz zweier 2D-Vektoren zu finden
{
    double distance = 0;

    distance = sqrt(pow((X1-X2),2) + pow((Y1-Y2),2));
    return distance;
}

int findWinner(int numberOfPoints, int NumberOfClusters, int point)
{
    double mindistance = INFINITY;
    double distance = INFINITY;


    for(int center = 0; center < NumberOfClusters; center++)
    {
        distance = euclideanDistance(X[point], prototypesX[center], Y[point], prototypesY[center]);
        if(distance < mindistance)
        {
            mindistance = distance; // finde den aktuellen Gewinner
            currentWinner = center;
        }
    }
    return currentWinner;
}
void train(int numberOfPoints, int NumberOfClusters)
{
    int *helpingArray; // erstelle Hilfsarray
    helpingArray = calloc(numberOfPoints, sizeof(int));
    for(int point = 0; point < numberOfPoints; point++)
    {
        helpingArray[point] = point; // fülle das Array mit int werten aufsteigend bis numberOfPoints
    }

    double *prototypesX_last = prototypesX; // speichere das aktuellste prototypes array
    double *prototypesY_last = prototypesY;

    do
    {
        shufflearray(helpingArray,numberOfPoints); // shuffle das Array umd zufällige indices auswählen zu können

        for(int point = 0; point < numberOfPoints; point++)
        {
            currentWinner = findWinner(numberOfPoints, NumberOfClusters, point);
            prototypesX[currentWinner] += eta * (X[helpingArray[point]] - prototypesX[currentWinner]); // helpingArray[point] um zufälligen wert zu nehemn
            prototypesY[currentWinner] += eta * (Y[helpingArray[point]] - prototypesY[currentWinner]);
        }

        prototypesX_last = prototypesX;
        prototypesY_last = prototypesY;
    }
    while(fabs(prototypesX_last- prototypesX) > threshold || fabs(prototypesY_last- prototypesY) > threshold );



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
    /* allokiere speicher für die Prototype Gewichte in der Länge des inputs*/
    prototypesX = calloc(NumberOfClusters, sizeof(double));
    prototypesY = calloc(NumberOfClusters, sizeof(double));
    /* Initialize the prototypes with random values*/
    for(int Cluster = 0; Cluster < NumberOfClusters; Cluster++)
    {
        prototypesX[Cluster] = randomvalue(2);
        prototypesY[Cluster] = randomvalue(2);
    }

    return 0;
}
