#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float chf;//declaring variable change as float for decimals
    
    do 
    
    {
    printf("How much change are you getting back?\n");
    chf = get_float();
    }
    
    while ( chf < 0 );//only accepts pos. amounts of change
    
    int ch = round(chf*100); //rounding off to eliminate errors
    
    int Q = (ch/25); //how many quarters
    int Qx = (ch%25);//whats left
    
    int D = (Qx/10);//how many dimes
    int Dx = (Qx%10);//whats left
    
    int N = (Dx/5);//how many nickels
    int Nx = (Dx%5);//whats left
    
    int P = (Nx/1);//how many pennies, non left
    
    int C = Q+D+N+P;//add it up
    
    printf("%i\n", C);//show the results
}