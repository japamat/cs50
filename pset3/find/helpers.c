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
    //initializing ints max, min, and mid
        int max = n - 1;
        int min = 0;
        
        while (max >= min)
        {
            
        //declare and calculate int mid
            int mid = (max + min) / 2;

        //check mid's value against max; throw away larger values
            if (values[mid] > value)
            {
                max = mid - 1;
            }

        //check mid's value against min; throw away lesser values
            else if (values[mid] < value)
            {
                min = mid + 1;
            }
        //if array[mid] == value, return true for found value
            else
            {
                return true;
            }
        }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
    //notes:
    //use i when iterating over list or temp list
    //use j when iterating over counter

{
//find the maximum value in unsorted list
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        if (max < values[i])
        {
            max = values [i];    
        }
        else{}
    }

//initialize temporary counter array with size of max (+1 to account for 0 index)
    int counter[max + 1];

//set all positions in counter array to value 0
    for (int j = 0; j <= max; j++)
    {
        counter[j] = 0;
    }

//Increment element's corresponding counter position's value by 1 for each occurrence in unsorted list
    for (int i = 0; i < n; i++)
    {
        counter[values[i]] = counter[values[i]] + 1;     
    }

//cumulative sum to capture last sorted list position of list elements
    for (int j = 1; j <= max; j++)
    {
        counter[j] = (counter[j] + counter[j - 1]);
    }
    
//initializing temporary sorted array
    int sorted[n];
    
//decrement counter value by 1, then place value in sorted position
    for (int i = n - 1; i >= 0; i--)
    {
        counter[values[i]] = counter[values[i]] - 1;
        sorted[counter[values[i]]] = values [i];
    }
    
//Place sorted values bac in vlaues array
    for (int i = 0; i < n; i++)
    {
        values[i] = sorted[i];
    }
    return;
}
