```
/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // make sure the array argument has at least one value
    if (n < 1)
    {
        return false;
    }
    
    int start_index = 0;
    int end_index = n - 1;
    
    // implement the binary search for the target value
    while (start_index <= end_index)
    {
        int mid_index = (start_index + end_index) / 2;
        if (values[mid_index] == value)
        {
            return true;
        }
        else if (values[mid_index] < value)
        {
            start_index = mid_index + 1;
        }
        else
        {
            end_index = mid_index - 1;
        }
    }
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // implement the insertion sort
    for (int i = 0; i < n; i++)
    {
        int smallest_index = i;
        int temp = values[i];
        
        for (int j = i + 1; j < n; j++)
        {
            if (values[j] < values[smallest_index])
            {
                smallest_index = j;
            }
        }
        
        values[i] = values[smallest_index];
        values[smallest_index] = temp;
    }
    return;
}
```
