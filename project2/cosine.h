/*cosine similarity*/
/*cos(d1,d2) = d1.d2/(sqrt(|d1|*|d2|))*/
#include "globals.h"
#include "structure.h"
#ifndef COSINE
#define COSINE
int cosine (int user, int movie)
{
	c.score= 0;
	int test[g.ratecounter];
	c.relevant[200][4]; 
	c.avg = 0;
	c.stdev = 0;
	int i, j;
	/*set data to 0*/
	for (i=0; i<200; i++)
	{
		for (j=0; j<4; j++)
			c.relevant[i][j] = 0;
	}
    
	/*calculate average rating */
	c.count = 0;
	c.avg = 0;
	for (i=0; i<1000; i++)
	{
		if ((g.movieRatings[user][i] != 0) && (g.movieRatings[user][i] != 9))
		{
			test[c.count] = i;
			c.avg += g.movieRatings[user][i];
			c.count++;
		}
	}
    /*get the general average*/
	c.avg /= (float)c.count;
	c.count2 = 0;
    /*check via trained data*/
	for (i=0; i<200; i++)
	{
		c.count = 0;
		for (j=0; j<g.ratecounter; j++) 
		{
			if ((g.movieRatings[i][test[j]] != 0) && (g.movieRatings[i][test[j]] != 9))
				c.count++; //count how many valid movies have been rated
		}
		if (c.count == g.ratecounter) //we want to check movies rated the same
		{
			for (j=0; j<g.ratecounter; j++)
			{
				if ((g.movieRatings[i][test[j]] != 0) && (g.movieRatings[i][test[j]] != 9))
				{
					c.relevant[c.count2][3] = i;
					c.relevant[c.count2][0] += g.movieRatings[i][j]; //get total
				}
			}
			c.count2++;
			c.relevant[c.count2][0] /= c.count;
		}
	}
    
	/*get the denominator for cosine similarity*/
	for (i=0; i<g.ratecounter; i++)
		c.stdev += (g.movieRatings[user][test[i]] - c.avg) * (g.movieRatings[user][test[i]] - c.avg); 
	c.stdev = sqrt (c.stdev);
    /*check trained values again to find relevant users*/
	for (i=0; i<200; i++)
	{
		if (c.relevant[i][3] != 0) 
		{
			for (j=0; j<g.ratecounter; j++)
                c.relevant[i][1] += (g.movieRatings[(int)c.relevant[i][3]][test[j]] - c.relevant[i][0]) * (g.movieRatings[(int)c.relevant[i][3]][test[j]] - c.relevant[i][0]);
			c.relevant[i][1] = sqrt (c.relevant[i][1]);
		}
	}
    /*return average if count is zero*/
	c.num = 0;
	c.denom = 0;
	if (c.count2 == 0)
	{
		c.score= c.avg;
		return c.score;
	}
    /*calculate part used in cosine algorithm*/
	for (i=0; i<200; i++) 
	{
		if (c.relevant[i][3] != 0)
		{
			for (j=0; j<g.ratecounter; j++)
				c.num += (g.movieRatings[user][test[j]] - c.avg) * (g.movieRatings[(int)c.relevant[i][3]][test[j]] - c.relevant[i][0]);	
			c.denom = c.stdev * c.relevant[i][1];
			c.relevant[i][2] = c.num / c.denom;
		}
	}
    /*get the prediction*/
	c.num = 0;
	c.denom = 0;
	for (i=0; i<200; i++)
	{
		if (c.relevant[i][3] != 0)
		{
			for (j=0; j<g.ratecounter; j++)
			{
				c.num += c.relevant[i][2] * g.movieRatings[(int)c.relevant[i][3]][test[j]];
				c.denom += c.relevant[i][2];
			}
		}
	}
    /*get rating by dividing numerator, denominator and then return rating*/
	c.score= (c.num / c.denom);

	if (c.score> 5)
		c.score= 5;
	if (c.score< 1)
		c.score= 1;
	return c.score;	
}
#endif