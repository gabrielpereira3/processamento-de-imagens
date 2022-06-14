/*-------------------------------------------------------------------------
 * Image Processing using C-Ansi
 *   Program: Negative from grayscale image
 * By Luiz Eduardo da Silva.
 *-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imagelib.h"

void neg_pbm(image In, image Out, int nl, int nc)
{
    for (int i = 0; i < nl * nc; i++)
        Out[i] = !In[i];
}

void neg_pgm(image In, image Out, int nl, int nc, int mn)
{
    for (int i = 0; i < nl * nc; i++)
        Out[i] = mn - In[i];
}

void neg_ppm(image In, image Out, int nl, int nc, int mn)
{
    for (int i = 0; i < nl * nc; i++)
    {
        int r = mn - (In[i] >> 16) & 0xFF;
        int g = mn - (In[i] >> 8) & 0xFF;
        int b = mn - In[i] & 0xFF;
        Out[i] = (r << 16) + (g << 8) + b;
    }
}

void msg(char *s)
{
    printf("\nNegative image");
    printf("\n-------------------------------");
    printf("\nUsage:  %s  image-name[.pnm] tp\n\n", s);
    printf("    image-name[.pnm] is image file file \n");
    printf("    tp = image type (1 = BW, 2 = Gray, 3 = Color)\n\n");
    exit(1);
}

/*-------------------------------------------------------------------------
 * main function
 *-------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int nc, nr, ml, tp;
    char *p, nameIn[100], nameOut[100], cmd[110];
    image In, Out;
    if (argc < 3)
        msg(argv[0]);
    tp = atoi(argv[2]);
    //-- define input/output file name
    img_name(argv[1], nameIn, nameOut, tp);
    //-- read image
    In = img_get(nameIn, &nr, &nc, &ml, tp);
    //-- create output image
    Out = img_alloc(nr, nc);
    //-- transformation
    switch (tp)
    {
    case 1:
        neg_pbm(In, Out, nr, nc);
        break;
    case 2:
        neg_pgm(In, Out, nr, nc, ml);
        break;
    case 3:
        neg_ppm(In, Out, nr, nc, ml);
    }
    //-- save image
    img_put(Out, nameOut, nr, nc, ml, tp);
    //-- show image
    sprintf(cmd, "%s %s &", VIEW, nameOut);
    system(cmd);
    img_free(In);
    img_free(Out);
    return 0;
}
