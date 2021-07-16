#include "globals.h"
#include "structure.h"
#ifndef CASEMOD
#define CASEMOD

int casemod (int user, int movie)
{
	m.score= 0;
	int test[g.ratecounter];
	m.relevant[200][4]; 
	m.avg = 0;
	m.stdev = 0;
	int i, j;
	/*reset data*/
    for (i=0; i<200; i++)
	{
		for (j=0; j<4; j++)
			m.relevant[i][j] = 0;
	}
	m.count = 0;
	m.avg = 0;
    /*count how many valid movies to find average*/
	for (i=0; i<1000; i++)
	{
		if ((g.movieRatings[user][i] != 0) && (g.movieRatings[user][i] != 9)) 
		{
			test[m.count] = i;
			m.avg += g.movieRatings[user][i];
			m.count++;
		}
	}

    /*compute average*/
	m.avg /= (float)m.count;

	m.count2 = 0;
    /*check if number of movies equals number rated*/
	for (i=0; i<200; i++)
	{
		m.count = 0;
		for (j=0; j<g.ratecounter; j++) 
		{
			if ((g.movieRatings[i][test[j]] != 0) && (g.movieRatings[i][test[j]] != 9))
				m.count++;
		}
		if (m.count == g.ratecounter) 
		{
			for (j=0; j<g.ratecounter; j++)
			{
				if ((g.movieRatings[i][test[j]] != 0) && (g.movieRatings[i][test[j]] != 9))
				{
					m.relevant[m.count2][3] = i;
					m.relevant[m.count2][0] += g.movieRatings[i][j];
				}
			}

			m.relevant[m.count2][0] /= m.count;
			m.count2++;


		}
	}
    /*find standard deviation*/
	for (i=0; i<g.ratecounter; i++)
		m.stdev += (g.movieRatings[user][test[i]] - m.avg) * (g.movieRatings[user][test[i]] - m.avg);
	m.stdev = sqrt (m.stdev);
	for (i=0; i<200; i++)
	{
		if (m.relevant[i][3] != 0)
		{
			for (j=0; j<g.ratecounter; j++)
                m.relevant[i][1] += (g.movieRatings[(int)m.relevant[i][3]][test[j]] - m.relevant[i][0]) * (g.movieRatings[(int)m.relevant[i][3]][test[j]] - m.relevant[i][0]);
			m.relevant[i][1] = sqrt (m.relevant[i][1]);
		}
	}
    
	m.num = 0;
	m.denom = 0;
	/*return average if count is zero*/
	if (m.count2 == 0)
	{
		m.score= m.avg;
		return m.score;
	}
	/*apply weights for casemod to compute similarity weight*/
	for (i=0; i<200; i++)
	{
		if (m.relevant[i][3] != 0)
		{
			for (j=0; j<g.ratecounter; j++)
				m.num += (g.movieRatings[user][test[j]] - m.avg) * (g.movieRatings[(int)m.relevant[i][3]][test[j]] - m.relevant[i][0]);
			m.denom = m.stdev * m.relevant[i][1];
			m.relevant[i][2] = m.num / m.denom;
            m.relevant[i][2] *= abs(pow (m.relevant[i][2], 1.5));
		}
	}
    /*compute prediction for casemod*/
	m.num = 0;
	m.denom = 0;
	for (i=0; i<200; i++)
	{
		if (m.relevant[i][3] != 0)
		{
			for (j=0; j<g.ratecounter; j++)
			{
                
				m.num += m.relevant[i][2] * (g.movieRatings[(int)m.relevant[i][3]][test[j]] - m.relevant[i][0]);
				m.denom += fabsf(m.relevant[i][2]);
			}
		}
	}
    /*get casemod score and return it*/
	m.score= m.avg + (m.num / m.denom) + 0.5;

	
	if (m.score> 5)
		m.score= 5;
	if (m.score< 1)
		m.score= 1;
	return m.score;
}
#endif