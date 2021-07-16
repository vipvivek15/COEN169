/*general declaration of structures used in program*/
#include "globals.h"
#ifndef STRUCTURE
#define STRUCTURE

typedef struct cosine
{
    int score;
    float relevant[200][4];
    float avg;
    float stdev;
    int count;
    int count2;
    float num;
    float denom;
}COSINE;
COSINE c;

typedef struct pearson
{
    int score;
    float relevant[200][4];
    float avg;
    float stdev;
    int count;
    int count2;
    float num;
    float denom;
}PEARSON;
PEARSON p;

typedef struct iuf
{
    int score;
    int total;
    int number;
    float relevant[200][4];
    float avg;
    float stdev;
    int count;
    int count2;
    float num;
    float denom;
}INVERSE;
INVERSE f;

typedef struct casemod
{
    int score;
    float relevant[200][4];
    float avg;
    float stdev;
    int count;
    int count2;
    float num;
    float denom;
}CASEMOD;
CASEMOD m;

typedef struct item
{
    int score;
    int min;
    float movies[1000][4];
    int count;
    float num;
    float denom;
    float left;
    float right;
}ITEM;
ITEM a;

typedef struct function
{
    int score;
    int choice;
}FUNCTION;
FUNCTION b;

#endif

