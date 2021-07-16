#include "globals.h"
#include "structure.h"
#ifndef ITEM
#define ITEM
int item (int user, int movie)
{
    a.score= 0;
    a.min = 1;
    a.movies[1000][4]; 
    int i, j;
    /*clearing data */
    for (i=0; i<1000; i++)
    {
        a.movies[i][0] = 2000;   
        a.movies[i][1] = 0;
        a.movies[i][2] = 0;
        a.movies[i][3] = 0;
    }
    
    /*find movies that are rated similarly*/
    /*find the number of pairs*/
    for (i=0; i<1000; i++)
    {
        a.count = 0;
        for (j=0; j<200; j++)
        {
        	/*check bounds*/
            if ((g.movieRatings[j][i] != 0 && g.movieRatings[j][i] != 9) && (g.movieRatings[j][movie] != 0 && g.movieRatings[j][movie] != 9))
                a.count++;
        }
        /*check bounds and update*/
        if (a.count >= a.min)
        {
            a.count = 0;
            for (j=0; j<200; j++)
            {
            	
                if ((g.movieRatings[j][i] != 0 && g.movieRatings[j][i] != 9)  && (g.movieRatings[j][movie] != 0 && g.movieRatings[j][movie] != 9))
                {
                    a.movies[a.count][0] = i; 
                    a.movies[a.count][1] = j;
                    a.count++;
                }
            }
        }
    }
    /*find average of all users*/
    for (i=0; i<1000; i++)
    {
        if (a.movies[i][0] != 2000)
        {
            a.count = 0;
            for (j=0; j<1000; j++)
            {
            	
                if ((g.movieRatings[(int)a.movies[i][1]][j] != 0) && (g.movieRatings[(int)a.movies[i][1]][j] != 9))
                {
                    a.movies[i][2] += g.movieRatings[(int)a.movies[i][1]][j]; 
                    a.count++; 
                }
            }
            a.movies[i][2] /= a.count; 
        }
    }
    
    i = 0;
    a.num = 0;
    a.denom = 0;
    a.left = 0;
    a.right = 0;
    /*clear all values and calculate average weights*/
    while ((i < 1000) && (a.movies[i][0] != 2000))
    {
        a.num += (g.movieRatings[(int)a.movies[i][1]][movie] - a.movies[i][2]) * (g.movieRatings[(int)a.movies[i][1]][(int)a.movies[i][0]] - a.movies[i][2]);
        a.left += (g.movieRatings[(int)a.movies[i][1]][movie] - a.movies[i][2]) * (g.movieRatings[(int)a.movies[i][1]][movie] - a.movies[i][2]);
        a.right += (g.movieRatings[(int)a.movies[i][1]][(int)a.movies[i][0]] - a.movies[i][2]) * (g.movieRatings[(int)a.movies[i][1]][(int)a.movies[i][0]] - a.movies[i][2]);
        j = i + 1;

        while ((j < 1000) && (a.movies[j][0] == a.movies[i][0]))
        {
            a.num += (g.movieRatings[(int)a.movies[j][1]][movie] - a.movies[j][2]) * (g.movieRatings[(int)a.movies[j][1]][(int)a.movies[j][0]] - a.movies[j][2]);
            a.left += (g.movieRatings[(int)a.movies[j][1]][movie] - a.movies[j][2]) * (g.movieRatings[(int)a.movies[j][1]][movie] - a.movies[j][2]);
            a.right += (g.movieRatings[(int)a.movies[j][1]][(int)a.movies[j][0]] - a.movies[j][2]) * (g.movieRatings[(int)a.movies[j][1]][(int)a.movies[j][0]] - a.movies[j][2]);
            j++;
        }

        a.denom = sqrt (a.left) * sqrt (a.right);
        a.movies[i][3] = a.num / a.denom;
        i = j;
    }
    
    a.num = 0;
    a.denom = 0;
    i = 0;
    /*compute item prediction*/
    while ((i < 1000) && (a.movies[i][0] != 2000))
    {
        a.num += a.movies[i][3] * g.movieRatings[user][(int)a.movies[i][0]];
        a.denom += fabsf (a.movies[i][3]);
        j = i + 1;

        while ((j < 1000) && (a.movies[j][0] == a.movies[i][0]))
            j++;
        i = j;
    }
    /*get item score and return it*/
    a.score= fabsf (a.num / a.denom) + 0.5;
    
    if (a.score> 5)
		a.score= 5;
	if (a.score< 1)
		a.score= 1;
	return a.score;
}
#endif