//Vivek Ponnala
//COEN 169 - Web Information Management
//Project 2 - Movie Recommendation System
//Pedro Sanchez
#ifndef GLOBALS
#define GLOBALS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*standard data declarations*/
typedef struct data
{
    int movieRatings[500][1000];
    int results[100][1000];
    int ratecounter;
    int change;
}DATA;
DATA g;

#endif