#include "globals.h"
#include "cosine.h"
#include "pearson.h"
#include "IUF.h"
#include "casemod.h"
#include "item.h"
#ifndef CUSTOM
#define CUSTOM
/*get average of all algorithms and add 0.3 and divide by 4.5*/
int custom (int user, int movie)
{
    return ( pearson (user, movie) + casemod (user, movie) + IUF (user, movie) + cosine (user, movie) + item (user, movie) + 0.3) / 4.5;
}
#endif
