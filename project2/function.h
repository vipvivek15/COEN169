#include "globals.h"
#include "cosine.h"
#include "pearson.h"
#include "IUF.h"
#include "casemod.h"
#include "item.h"
#include "custom.h"
#ifndef FUNCTION
#define FUNCTION
void function (void)
{
	int i = 0;
	int j = 0;
    printf ("\nPlease select which algorithm you would like to use:\n");
    printf ("0: Exit\n");
    printf ("1: Cosine Similarity\n");
    printf ("2: Pearson Correlation\n");
    printf ("3: Pearson Correlation - Inverse User Frequency\n");
    printf ("4: Pearson Correlation - Case Modification\n");
    printf ("5: Item Based Similarity - Cosine\n");
    printf ("6: Custom Algorithm\n");
    scanf ("%d", &(b.choice));
    for (i=g.change; i<g.change+100; i++)
    {
        for (j=0; j<1000; j++)
        {
            if (g.movieRatings[i][j] == 0)
            {
                switch (b.choice)
                {
                    case 0:
                        printf("Exit, thank you. \n");
                        exit(0);
                    case 1:
                        b.score= cosine (i, j);
                        break;
                    case 2:
                        b.score= pearson (i, j);
                        break;
                    case 3:
                        b.score= IUF (i, j);
                        break;
                    case 4:
                        b.score= casemod (i, j);
                        break;
                    case 5:
                        b.score= item (i, j);
                        break;
                    case 6:
                        b.score= custom (i, j);
                        break;
                    default:
                        printf("Please enter a valid option of 1,2,3,4,5 or 6 only.\n");
                }
                g.results[i-g.change][j] = b.score;
            }
        }
    }
}
#endif