```
/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // if the programme does not have 2 or 3 command-line arguments, exit the programme with an error code of 1
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // convert the 2nd command-line argument from string to integer and store the value in the newly creately integer variable n 
    int n = atoi(argv[1]);

    // if a 3rd command-line argument is provided, it is converted to integer and used by srand48 to create a seed for the random number generator algorithm drand48
    // if a 3rd command-line argument is not provided, the computer's internal clock is used to generate the seed. As the time is forever changing, the seed differs each time when created
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    // print n numbers of random number, which is printed out one each line
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
```
