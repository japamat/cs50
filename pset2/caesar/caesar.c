// ********** headers & function declaration **********


#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main (int argc, string argv[])


// ********** valid arguments check, staging variables **********


{
    //print error message if argc is not 2 
    if (argc != 2)
    {
        printf("Invalid Command Line Argument\n");
        return 1;
    }
    
    int k = atoi(argv[1]);
    if (k < 1)
    {
        printf("Invalid Command Line Argument\n");
        return 1;
    }
    
    //print PLAINTEXT prompt and gets string for enciphering from user
    printf("plaintext: ");
    string P = get_string();
    
    
// ********** enciphering str P **********
    
    
    printf("ciphertext: ");
    
    //iterate over each char in str P, to convert to ciphertext
    for (int i = 0, n = strlen(P); i < n; i++)
    {
        //check that i'th char in str P is letter not num
        if (isalpha(P[i]))
        {
            if (isupper(P[i]))
            {
                //encoding uppr case chars
                printf("%c", (((P[i] - 65) + k) % 26) + 65);
            }
            else
            {
                //encoding lower case chars
                printf("%c", (((P[i] - 97) + k) % 26) + 97);    
            }
        }
        else 
        {
            //print non letter chars in str P
            printf("%c", P[i]);
        }
    }
    printf("\n");
    return 0;
}