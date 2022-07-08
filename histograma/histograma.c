/*-------------------------------------------------------------------------
 * Tranformação de intensidade
 * Por Luiz Eduardo da Silva.
 *-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "imagelib.h"

image histograma(image In)
{
    int T[In->ml + 1];
    float M[In->ml + 1];
    int R = In->nr * In->nc;
    image Out = img_clone(In);

    // Zerando histograma
    for (int i = 0; i < In->ml + 1; i++)
        T[i] = 0;

    // Preenchendo histograma
    for (int i = 0; i < In->nr * In->nc; i++)
        T[In->px[i]]++;

    // Calculando média acumulada
    M[0] = (float)T[0] / R * In->ml;
    for (int i = 1; i < In->ml + 1; i++)
        M[i] = ((float)T[i] / R * In->ml) + M[i - 1];

    // Equalizando histograma
    for (int i = 0; i < In->nr * In->nc; i++)
        Out->px[i] = M[In->px[i]];

    return Out;
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
    char nameIn[100], nameOut[100], cmd[110];
    image In, Out;
    if (argc < 2)
        msg(argv[0]);

    img_name(argv[1], nameIn, nameOut, GRAY, GRAY);

    //-- read image
    In = img_get(nameIn, GRAY);
    //-- transformation
    Out = histograma(In);
    //-- save image
    img_put(Out, nameOut, GRAY);

    sprintf(cmd, "%s %s &", VIEW, nameOut);
    system(cmd);
    img_free(In);
    img_free(Out);
    return 0;
}
