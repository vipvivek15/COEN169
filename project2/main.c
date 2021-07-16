#include "globals.h"
#include "cosine.h"
#include "pearson.h"
#include "IUF.h"
#include "casemod.h"
#include "item.h"
#include "custom.h"
#include "function.h"

/*clear data in arrays*/
void reset_main(void)
{
	int i, j;
	for (i=0; i<500; i++)
	{
		for (j=0; j<1000; j++)
			g.movieRatings[i][j] = 9;
	}

	for (i=0; i<100; i++)
	{
		for (j=0; j<1000; j++)
			g.results[i][j] = 0;
	}
}
int main (void)
{
	int i, j;
	FILE *fp;

	/*clear data in arrays*/
	reset_main();
    /*open train.txt*/
	fp = fopen ("train.txt", "rt");
    /*scan in values*/
	if(fp!=NULL)
	{
		int input;
		i = 0;
		j = 0;
		while (fscanf (fp, "%d", &input) != EOF)
		{
			if (j < 1000)
			{
				g.movieRatings[i][j] = input;
				j++;
			}
			if (j >= 1000)
			{
				j = 0;
				i++;
			}
		}
	}
    /*print error*/
    else
	{
		perror("Error is: ");
		exit (0);
	}
	fclose (fp); //close file

	int test;
	char input[20];
	char output[20];
	//user prompt
	printf ("\nWhich file would you like to use for testing?\n");
	int k;
    /*print files*/
    for(k=0;k<3;k++)
    {
        if(k<2)
        {
            printf("%d - test%d.txt\t", k+1, 5*(k+1));
        }
        if(k==2)
        {
            printf("%d - test%d.txt\n", k+1, 10*k);
        }
    }
	scanf ("%d", &test);

    /*calculate offset based on file length differences*/
    switch(test)
    {
        case 1:
            g.change = 200;
		    g.ratecounter = 5;
		    strcpy (input, "test5.txt");
		    strcpy (output, "result5.txt");
            break;
        case 2:
            g.change = 300;
		    g.ratecounter = 10;
		    strcpy (input, "test10.txt");
		    strcpy (output, "result10.txt");
            break;
        case 3:
            g.change = 400;
		    g.ratecounter = 20;
		    strcpy (input, "test20.txt");
		    strcpy (output, "result20.txt");
            break;
        default:
            printf("Please enter value of 1, 2 or 3 only. \n");
    }
    /*input file to operate on*/
	fp = fopen (input, "rt"); 
    /*scan values*/
	if (fp != NULL)
	{
		int input; 
		i = 0;
		j = 0;
		while (fscanf (fp, "%d%d%d", &i, &j, &input) != EOF)
		{
			g.movieRatings[i-1][j-1] = input;
		}
	}
    else
    {
        perror("Error is: ");
		exit (0);
    }
	fclose (fp); 

	// Call the function to handle algorithm selection
	function ();
    /*output results*/
	int user, movie, score;
	FILE *ofp;
	ofp = fopen (output, "wt"); 
	if (ofp != NULL)
	{
		for (i=0; i<100; i++)
		{
			for (j=0; j<1000; j++)
			{
				if (g.results[i][j] != 0)
				{
					user = i + g.change + 1;
					movie = j + 1;
					score= g.results[i][j];
					fprintf (ofp, "%d %d %d\n", user, movie, score);
				}
			}
		}
	}
    else
    {
        perror("Error is: ");
        exit(0);
    }
	fclose (ofp);
    /*print which result file has been outputted*/
	switch(test)
    {
        case 1:
            printf("result5.txt has been outputted. \n");
            break;
        case 2:
            printf("result10.txt has been outputted. \n");
            break;
        case 3:
            printf("result20.txt has been outputted. \n");
            break;
        default:
            printf("Please enter a valid test number to get results. \n");
            break;
    }
    return 0;
}