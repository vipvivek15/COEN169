/*similar to cosine algorithm except add the user's average rating
and subtract active user's rating from average*/
#include "globals.h"
#include "structure.h"
#ifndef PEARSON
#define PEARSON
int pearson (int user, int movie)
{
	p.score= 0;
	int test[g.ratecounter];
	p.avg = 0;
	p.stdev = 0;
	int i, j;

    /*set data to 0*/
    for (i=0; i<200; i++)
	{
		for (j=0; j<4; j++)
			p.relevant[i][j] = 0;
	}
    /*calculate average rating*/
	p.count = 0;
	p.avg = 0;
	for (i=0; i<1000; i++)
	{
		if ((g.movieRatings[user][i] != 0) && (g.movieRatings[user][i] != 9))
		{
			test[p.count] = i;
			p.avg += g.movieRatings[user][i];
			p.count++;
		}
	}
    /*general average*/
	p.avg /= (float)p.count;
	p.count2 = 0;
    /*check trained data*/
	for (i=0; i<200; i++)
	{
		p.count = 0;
		for (j=0; j<g.ratecounter; j++) //up to number rated
		{
			if ((g.movieRatings[i][test[j]] != 0) && (g.movieRatings[i][test[j]] != 9))
				p.count++; //if within bounds, increment count
		}
		if (p.count == g.ratecounter) //check movies that have been rated the same
		{
			for (j=0; j<g.ratecounter; j++)
			{
				if ((g.movieRatings[i][test[j]] != 0) && (g.movieRatings[i][test[j]] != 9))
				{
					p.relevant[p.count2][3] = i;
					p.relevant[p.count2][0] += g.movieRatings[i][j];
				}
			}
			p.relevant[p.count2][0] /= p.count;
			p.count2++;
		}
	}
    //get denominator
	for (i=0; i<g.ratecounter; i++)
		p.stdev += (g.movieRatings[user][test[i]] - p.avg) * (g.movieRatings[user][test[i]] - p.avg);
	p.stdev = sqrt (p.stdev);
    //iterate through trained values
	for (i=0; i<200; i++)
	{
		if (p.relevant[i][3] != 0) /*updating relevant users*/
		{
			for (j=0; j<g.ratecounter; j++)
					p.relevant[i][1] += (g.movieRatings[(int)p.relevant[i][3]][test[j]] - p.relevant[i][0]) * (g.movieRatings[(int)p.relevant[i][3]][test[j]] - p.relevant[i][0]);
			p.relevant[i][1] = sqrt (p.relevant[i][1]);
		}
	}
	p.num = 0;
	p.denom = 0;
    /*if count is 0, return average*/
	if (p.count2 == 0)
	{
		p.score= p.avg;
		return p.score;
	}
    /*get part used in cosine algorithm*/
	for (i=0; i<200; i++)
	{
		if (p.relevant[i][3] != 0)
		{
			for (j=0; j<g.ratecounter; j++)
				p.num += (g.movieRatings[user][test[j]] - p.avg) * (g.movieRatings[(int)p.relevant[i][3]][test[j]] - p.relevant[i][0]);
			p.denom = p.stdev * p.relevant[i][1];
			p.relevant[i][2] = p.num / p.denom;
		}
	}
    /*get prediction*/
	p.num = 0;
	p.denom = 0;
	for (i=0; i<200; i++)
	{
		if (p.relevant[i][3] != 0)
		{
			for (j=0; j<g.ratecounter; j++)
			{

				p.num += p.relevant[i][2] * (g.movieRatings[(int)p.relevant[i][3]][test[j]] - p.relevant[i][0]);
				p.denom += fabsf(p.relevant[i][2]);
			}
		}
	}
    /*get pearson score and return it*/
	p.score= p.avg + (p.num / p.denom) + 0.5;

	if (p.score> 5)
		p.score= 5;
	if (p.score< 1)
		p.score= 1;	
	return p.score;
}
#endif