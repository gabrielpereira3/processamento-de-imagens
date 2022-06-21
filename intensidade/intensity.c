/*-------------------------------------------------------------------------
 * Tranformação de intensidade
 * Por Luiz Eduardo da Silva.
 *-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "imagelib.h"

void intensidade(image In, image Out, int nl, int nc, int mn)
{
    float T[mn + 1];
    float expo = 2;
    for (int i = 0; i < mn + 1; i++)
    {
        //--- Transformacao Potência/Raiz
        T[i] = pow(i, expo) / pow(mn, expo) * mn;
        //--- Transformacao Logaritmica
        // T[i] = log(i + 1) / log(mn + 1) * mn;
        // printf("T[%d] = %.0f\n", i, T[i]);
    }
    for (int i = 0; i < nl * nc; i++)
        Out[i] = T[In[i]];
}

void msg(char *s)
{
    printf("\nIntensidade");
    printf("\n-------------------------------");
    printf("\nUso:  %s  nome-imagem[.pgm] \n\n", s);
    printf("    nome-imagem[.pgm] é o nome do arquivo da imagem \n");
    exit(1);
}

/*-------------------------------------------------------------------------
 * main function
 *-------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int nc, nr, ml;
    char *p, nameIn[100], nameOut[100], cmd[110];
    image In, Out;
    if (argc < 2)
        msg(argv[0]);

    img_name(argv[1], nameIn, nameOut, GRAY);
    //-- read image
    In = img_get(nameIn, &nr, &nc, &ml, GRAY);
    Out = img_alloc(nr, nc);

    //-- transformation
    intensidade(In, Out, nr, nc, ml);

    //-- save image
    img_put(Out, nameOut, nr, nc, ml, GRAY);
    sprintf(cmd, "%s %s &", VIEW, nameOut);
    system(cmd);
    img_free(In);
    img_free(Out);
    return 0;
}
