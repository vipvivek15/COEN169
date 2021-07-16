#include "globals.h"
#include "structure.h"
#ifndef INVERSE
#define INVERSE

int IUF (int user,  int movie)
{
	f.score= 0;
	int test[g.ratecounter];
    float IUFweights[g.ratecounter];
    f.total = 200;
	f.avg = 0;
	f.stdev = 0;
	int i, j;
    /*reset data to 0 in relevant*/
    for (i=0; i<200; i++)
	{
		for (j=0; j<4; j++)
		{
			f.relevant[i][j] = 0;
		}
	}

    f.count = 0;
    /*increment if within bounds of valid rated movies*/
    for (i=0; i<1000; i++)
	{
		if ((g.movieRatings[user][i] != 0) && (g.movieRatings[user][i] != 9))
		{
			test[f.count] = i;
            f.count++;
        }
    }
    /*create an IUF weight matrix*/
    for (i=0; i<g.ratecounter; i++)
    {
        f.number = 0;
        for (j=0; j<200; j++)
        {
            if ((g.movieRatings[j][test[i]] != 0) && (g.movieRatings[j][test[i]] != 9))
                f.number++;
        }
        /*IUF calculation*/
        IUFweights[i] = log ((float)f.total / (float)f.number);
    }
    
	f.count = 0;
	f.avg = 0;

	for (i=0; i<1000; i++)
	{
		if ((g.movieRatings[user][i] != 0) && (g.movieRatings[user][i] != 9))
		{
			f.avg += g.movieRatings[user][i] * IUFweights[f.count];
			f.count++;
		}
	}
    /*get average*/
	f.avg /= (float)f.count;
	f.count2 = 0;

	for (i=0; i<200; i++)
	{
		f.count = 0;
		for (j=0; j<g.ratecounter; j++) 
		{
			if ((g.movieRatings[i][test[j]] != 0) && (g.movieRatings[i][test[j]] != 9))
				f.count++;
		}

		if (f.count == g.ratecounter)
		{
			for (j=0; j<g.ratecounter; j++)
			{
				if ((g.movieRatings[i][test[j]] != 0) && (g.movieRatings[i][test[j]] != 9))
				{
					f.relevant[f.count2][3] = i;
					f.relevant[f.count2][0] += g.movieRatings[i][j] * IUFweights[f.count2];
				}
			}
			f.relevant[f.count2][0] /= f.count;
			f.count2++;
		}
	}
    
	for (i=0; i<g.ratecounter; i++)
		f.stdev += ((g.movieRatings[user][test[i]] * IUFweights[i]) - f.avg) * ((g.movieRatings[user][test[i]] * IUFweights[i]) - f.avg);
	f.stdev = sqrt (f.stdev);
	for (i=0; i<200; i++)
	{
		if (f.relevant[i][3] != 0)
		{
			for (j=0; j<g.ratecounter; j++)
                f.relevant[i][1] += ((g.movieRatings[(int)f.relevant[i][3]][test[j]] * IUFweights[j]) - f.relevant[i][0]) * ((g.movieRatings[(int)f.relevant[i][3]][test[j]] * IUFweights[j]) - f.relevant[i][0]);
			f.relevant[i][1] = sqrt (f.relevant[i][1]);
		}
	}
    
	f.num = 0;
	f.denom = 0;
	/*return rating if average+0.5*/
	if (f.count2 == 0)
	{
		f.score= f.avg + 0.5;
        if (f.score> 5)
            f.score= 5;
        if (f.score< 1)
            f.score= 1;      
		return f.score;
	}
	
	for (i=0; i<200; i++)
	{
		if (f.relevant[i][3] != 0)
		{
			for (j=0; j<g.ratecounter; j++) /*IUF weight implementation*/
				f.num += ((g.movieRatings[user][test[j]] * IUFweights[j]) - f.avg) * ((g.movieRatings[(int)f.relevant[i][3]][test[j]] * IUFweights[j]) - f.relevant[i][0]);
			f.denom = f.stdev * f.relevant[i][1];
			f.relevant[i][2] = f.num / f.denom;
		}
	}
    
	f.num = 0;
	f.denom = 0;
    /*compute prediction for IUF*/
	for (i=0; i<200; i++)
	{
		if (f.relevant[i][3] != 0)
		{
			for (j=0; j<g.ratecounter; j++) 
			{
                
				f.num += f.relevant[i][2] * ((g.movieRatings[(int)f.relevant[i][3]][test[j]] * IUFweights[j]) - f.relevant[i][0]);
				f.denom += fabsf(f.relevant[i][2]);
			}
		}
	}
    /*get IUF score and return it*/
	f.score= f.avg + (f.num / f.denom) + 0.5;
	
	if (f.score> 5)
		f.score= 5;
	if (f.score< 1)
		f.score= 1;
	return f.score;
}
#endif