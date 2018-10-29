#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height, r, s, b;//declaring my ints
    do
    {
        printf("Height: ");
        height = get_int();
        
    }
    while ( height > 23 || height < 0 );//do while loop, execute at least once, set condition for pyramid no greater than 23
    
    for (r = 0 ; r < height; r++)//print rows
    {
        for (s=0; s < height - r - 1; s++)// print spaces on a given iteration of each row r
        {
            printf(" ");
        }
        for (b=0; b < r + 1; b++)// print blocks on a given iteration of each row r
        {
            printf("#");
        }
        printf("  ");//prints double space in the middle of the row
        for (b=0; b < r + 1; b++)// prints blocks back half on a given iteration of each row r
        {
            printf("#");
        }
        printf("\n");  
    }
    
}
