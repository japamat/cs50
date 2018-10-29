#include <stdio.h>
#include <cs50.h>

int main (void)
{
        printf("Minutes: ");
        int Minutes = get_int();
        int Bottles = Minutes * 12;
        printf("Bottles: %i\n", Bottles);
}