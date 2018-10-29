// ********** including headers **********


#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = get_string();
    
    //if the first char is an alphabet character, print it uppercase
    if (isalpha (name[0]))
    {
        printf("%c", toupper (name[0]));
    }
    
    // iterate over the string
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        //if (it is a letter AND has space before it)
        if (isalpha (name[i]) && isspace (name[i-1])) 
        {
            printf("%c", toupper (name[i]));
        }
    }
    printf("\n");
}  