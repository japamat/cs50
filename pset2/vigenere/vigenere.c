// ********** headers & function declaration **********


#include <stdio.h> // printf
#include <cs50.h> // get_string
#include <ctype.h> // isalpha, toupper, islower
#include <string.h> // strlen

// declaring encipher function for later use
char encipher (char l, int  c);


int main (int argc, string argv[])


// ********** valid arguments check **********


{
    //print error message if argc is not 2 
    if (argc != 2)
    {
        printf("incorrect command line argument count\n");
        return 1;
    }
    //iterating over each char in argv[1]
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        //checking i'th char in srgv[1] for letter value
        if (isalpha(argv[1][i]) == 0)
        {
            printf("argv[1] doesn't contain only letters\n");
            return 1;
        }
    }
    
    
// ********** staging variables, collecting plaintext **********
    
    
    //collect string length of argv1
    int ciphlen = strlen(argv[1]);
    
    //use that to define array of ints length for conversion to numbers for key
    int cipher[ciphlen];
    
    //iterate over i'th char 
    for (int a =0; a < ciphlen; a++)
    {
        //convert to number and store in array cipher
        cipher[a] = toupper(argv[1][a]) - 65;
    }
    
    //get plaintext from user
    printf("plaintext:  ");
    string ptxt = get_string();
    
    //create int for length of str ptxt
    int ptxtlen = strlen(ptxt);
    

// ********** applying cipher (aka argv[1]) to str ptxt **********


    printf("ciphertext: ");
    
    //iterating over ptext to encipher any letters
    for (int i = 0, j = 0; i < ptxtlen; i++)
    {
        //check if i'th char of ptxt is letter, if true, then apply cipher 
        if (isalpha(ptxt[i]))
        {
            // encipher i'th char in ptxt with j'th int in cipher
            printf("%c", encipher(ptxt[i], cipher[j]));
            
            //increment j
            j++;
            
            // check if j'th int in cipher is last int in ccipher
            if (j == ciphlen)
            {
                //if it is at last, set j back to zero to begin looping
                (j = 0);   
            }
        }
        else
        {
            // print non letter chars in ptxt as is
            printf("%c", ptxt[i]);
        }
    }
    printf("\n");
    return 0;
}


// ********** cipher function with upper/lower check **********


char encipher (char l, int  c)
 {
    if (islower(l))
    {
        // returns char; 4 step math breakdown for enciphering as follows 
        // 1. i'th char in ptxt - 97 [to bring i'th char in ptxt down to ascii index0]
        // 2. + j'th int in cipher [this moves i'th char in ptxt to encoded position as per j'th int in cipher]
        // 3. modulo 26 [preprocessing for moving back to ascii letter range]
        // 4. + 97 [actually moves to new ascii position]
        return ((((l - 97) + c) % 26) + 97);
    }
    else
    {
        // same mathematical steps as before, substituting 65 [used for uppercase ascii transposition] for 97 [for lowercase]
        return ((((l - 65) + c) % 26) + 65);
    }
 }