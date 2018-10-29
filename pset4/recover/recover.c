/**
 * cs50x - pset4
 * recover.c
 * 
 * Recover jpegs!
 * 
 * 
 **/
 
 #include <stdio.h>
 #include <stdint.h>
 
 const int block = 512;
 
 int main (void)
 {
    //create local file for card.raw data
    FILE *rawdat;
    
    //store card.raw in rawdat, if we can open card.raw, proceed to recover jpegs
    if ((rawdat = fopen("card.raw","r")) != NULL)
    {
        //initialize pic counter file names
        int pictotal = 0;
        
        //initialize our buffer space for temp storing found data
        uint8_t buffer [512];
        
        //initialize outfile for recovered jpegs
        FILE *jpegs = NULL;
        
        while (fread(buffer, block, 1, rawdat))
        {
            //if first four bitts of buffer are jpeg header
            if(      buffer[0] == 0xff 
                 &&  buffer[1] == 0xd8 
                 &&  buffer[2] == 0xff 
                 && (buffer[3] & 0xe0) == 0xe0)
            {
                //close current file if open
                if (jpegs != NULL)
                {
                    fclose(jpegs);
                }
                
                //create file name array
                char jpegname [8];
                
                //put the pictotal into jpegname
                sprintf(jpegname, "%03d.jpg", pictotal);
                
                //open new file with jpegname as name
                jpegs = fopen(jpegname, "a");
                
                //increment pictotal
                pictotal ++;
            }
            
            //keep writing those blocks to that jpeg file
            if (jpegs != NULL)
            {
                fwrite(buffer, block , 1, jpegs);
            }
            
        }
        
        //at this point we're out of the while loop, do we have a file open?
        //if so, close it.
        if (jpegs != NULL)
        {
            fclose(jpegs);
        }
        
        //we're done.
        return 0;
    }
    
    //this is if we tried to open a bad file or something.
    else if(rawdat == NULL)
    {
        printf("file could not be opened\n");
        return 1;
    }
 }
 