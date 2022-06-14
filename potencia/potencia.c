/*-------------------------------------------------------------------------
 * 
 *   Program: Intensidade
 * By Luiz Eduardo da Silva.
 *-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imagelib.h"
#include <math.h>

void operacao(image In, image Out, int nl, int nc, int mn, float expo)
{
    float T[mn + 1];

    for(int i = 0; i < mn + 1; i++)
        T[i] = pow(i, expo) / pow(mn, expo) * mn;

    for (int i = 0; i < nl * nc; i++)
        Out[i] = T[In[i]];
}

void msg(char *s)
{
    printf("Erro no número de parâmetros\n");
    exit(1);
}

/*-------------------------------------------------------------------------
 * main function
 *-------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int nc, nr, ml;
    float expo;
    char *p, nameIn[100], nameOut[100], cmd[110];
    image In, Out;

    if (argc < 3)
        msg(argv[0]);

    expo = atof(argv[2]);

    //-- define input/output file name
    img_name(argv[1], nameIn, nameOut, GRAY);

    //-- read image
    In = img_get(nameIn, &nr, &nc, &ml, GRAY);

    //-- create output image
    Out = img_alloc(nr, nc);

    //-- transformation
    operacao(In, Out, nr, nc, ml, expo);

    //-- save image
    img_put(Out, nameOut, nr, nc, ml, GRAY);

    //-- show image
    sprintf(cmd, "%s %s &", VIEW, nameOut);

    system(cmd);
    img_free(In);
    img_free(Out);

    return 0;
}
