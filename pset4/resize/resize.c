/**
 * pset4 - resize more
 * 
 * 
 * 
 * 
 * 
 * 
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize resize_factor infile.bmp outfile_name.bmp\n");
        return 1;
    }

    // convert resize factor to type float
    int f = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    if (f < 0 || f > 100)
    {
        fprintf(stderr, "%i value not within parameters (f must be positive and no greater than 100.\n", f);
        return 2;
    }

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
    //defining variables to store infile height and width
    int infilewidth = bi.biWidth;
    int infileheight = bi.biHeight;
    
    //adjusting bi.biWidth & bi.biHeight by factor of f
    bi.biWidth *= f;
    bi.biHeight *= f;
    
    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int infilepadding = (4 - (infilewidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //calculating new bi.biSizeImage & bf.bfSize
    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth * sizeof(RGBTRIPLE) + padding);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(infileheight); i < biHeight; i++)
    {
        //for each row, write to outfil f times (copying height f times)
        for (int l = 0; l < f; l++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < infilewidth; j++)
            {
                //for each pixel in row, write to outfile f times (copying width f times)
                for (int k = 0; k < f; k++)
                {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                
                //move cursor back to beginning of pixel
                if (k < (f - 1))
                fseek(inptr, -sizeof(RGBTRIPLE), SEEK_CUR);
                }
            }
        // skip over padding, if any
        fseek(inptr, infilepadding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
        //move cursor 
        if (l < (f - 1))
        fseek(inptr, (-sizeof(RGBTRIPLE) * infilewidth) - infilepadding , SEEK_CUR);   
        }
    }
    

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
