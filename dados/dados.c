/*=============================================================
 * UNIFAL = Universidade Federal de Alfenas .
 * BACHARELADO EM CIENCIA DA COMPUTACAO.
 * Trabalho . . : Imagem de dados
 * Disciplina : Processamento de Imagens
 * Professor . : Luiz Eduardo da Silva
 * Aluno . . . . . : Gabriel Pereira Soares
 * Data . . . . . . : 08/07/2022
*=============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "imagelib.h"
#include <stdbool.h>

int posicao_inicial = 0;
int posicao_final = 39;
int limite_colunas = 0;

image carrega_dado(image dado, image Out, image Icon){
    int limite = posicao_final;
    int inicio = posicao_inicial;

    for (int i = 0; i < 1600; i++){
        Out->px[inicio] = dado->px[i];
        //printf(" %d ", inicio);
        if(inicio < limite-1){
            inicio++;
        }else{
            limite = limite + Out->nc;
            inicio = limite - 40;
        }
    }

    if((posicao_final + 1) < limite_colunas){
        posicao_inicial = posicao_inicial + 40;
        posicao_final = posicao_final + 40;
    } else {
        limite_colunas = limite_colunas + 40 * Out->nc;
        posicao_inicial = posicao_inicial + 39 * Out->nc + 40;
        posicao_final = posicao_final + 39 * Out->nc + 40;
    }

    return Out;
}

image dados(image In, image Out, image Icon)
{
    // Carregando as imagens dos dados

    image dado0, dado1, dado2, dado3, dado4, dado5, dado6;

    // preto-0.pgm (DADO PRETO)
    dado0 = img_get("preto-0.pgm", GRAY);
    dado1 = img_get("preto-1.pgm", GRAY);
    dado2 = img_get("preto-2.pgm", GRAY);
    dado3 = img_get("preto-3.pgm", GRAY);
    dado4 = img_get("preto-4.pgm", GRAY);
    dado5 = img_get("preto-5.pgm", GRAY);
    dado6 = img_get("preto-6.pgm", GRAY);

    // 0.pgm (DADO BRANCO)
    // dado0 = img_get("0.pgm", GRAY);
    // dado1 = img_get("1.pgm", GRAY);
    // dado2 = img_get("2.pgm", GRAY);
    // dado3 = img_get("3.pgm", GRAY);
    // dado4 = img_get("4.pgm", GRAY);
    // dado5 = img_get("5.pgm", GRAY);
    // dado6 = img_get("6.pgm", GRAY);

    // dado-0.pgm (DADO MUITO PRETO)
    // dado0 = img_get("dado-0.pgm", GRAY);
    // dado1 = img_get("dado-1.pgm", GRAY);
    // dado2 = img_get("dado-2.pgm", GRAY);
    // dado3 = img_get("dado-3.pgm", GRAY);
    // dado4 = img_get("dado-4.pgm", GRAY);
    // dado5 = img_get("dado-5.pgm", GRAY);
    // dado6 = img_get("dado-6.pgm", GRAY);


    // Transformando imagem em ícone

    int inicio = 0;
    int limite = Icon->nc - 1;
    int pula_linha = (In->nr / Icon->nr) * In->nc;

    int j = 0;

    for (int i = 0; i < Icon->nr * Icon->nc; i++){

        Icon->px[i] = In->px[j];

        //printf("%d ", j);

        if(i + 1 <= limite){
            j = j + In->nc/Icon->nc;
        } else {
            inicio = inicio + pula_linha;
            j = inicio;          
            limite = limite + Icon->nc;
        }
    }

    // Fazendo o mosaico com os dados a partir do ícone

    int intensidade_dado = Out->ml / 7;

    limite_colunas = Out->nc;

    for (int i = 0; i < Icon->nr * Icon->nc; i++){
        if(Icon->px[i] <= intensidade_dado){
            Out = carrega_dado(dado0, Out, Icon);
        }else if(Icon->px[i] <= 2 * intensidade_dado){
            Out = carrega_dado(dado1, Out, Icon);
        }else if(Icon->px[i] <= 3 * intensidade_dado){
            Out = carrega_dado(dado2, Out, Icon);
        }else if(Icon->px[i] <= 4 * intensidade_dado){
            Out = carrega_dado(dado3, Out, Icon);
        }else if(Icon->px[i] <= 5 * intensidade_dado){
            Out = carrega_dado(dado4, Out, Icon);
        }else if(Icon->px[i] <= 6 * intensidade_dado){
            Out = carrega_dado(dado5, Out, Icon);
        }else if(Icon->px[i] <= Icon->ml){
            Out = carrega_dado(dado6, Out, Icon);
        }

    }

    // Desalocando imagens dos dados

    img_free(dado0);
    img_free(dado1);
    img_free(dado2);
    img_free(dado3);
    img_free(dado4);
    img_free(dado5);
    img_free(dado6);

    return Out;
}

/*

/////////// Seria uma opção para deixar a imagem reduzida mais fiel à original, porém estava dando muito trabalho desnecessário. ///////////

image dados(image In)
{

    int col, lin; 

    col = In->nc;
    lin = In->nr;

    if(In->nc > 100){
        lin = lin * 100 / col;
        col = 100;
    }

    image Out = img_create(lin, col, In->ml, In->tp);

    int inicio = 0;
    int limite = Out->nc - 1;
    int pula_linha = (In->nr / Out->nr) * In->nc;

    int resto_col = In->nc % Out->nc;
    bool ativa_col = resto_col != 0;

    // Se o resto for diferente de 0, quer dizer que a resolução não é proporcional, aí ele conserta
    int pula_col;
    int soma_col;
    int inc_pula_col;

    if(ativa_col){
        // Essa variável serve para definir o intervalo em que a coluna incrementará um valor a mais para ficar proporcional
        pula_col = Out->nc / resto_col;
        soma_col = pula_col;
        // Incrementa a variável que pula coluna
        inc_pula_col = 1;
    }

    int i, j = 0;

    for (i = 0; i < Out->nr * Out->nc; i++){

        Out->px[i] = In->px[j];

        printf("%d ", j);

        if(i + 1 <= limite){
            j = j + In->nc/Out->nc;
            if(i == soma_col && inc_pula_col <= resto_col && ativa_col){
                j++;
                inc_pula_col++;
                soma_col = soma_col + pula_col;
            }
        } else {
            inicio = inicio + pula_linha;
            j = inicio;          
            limite = limite + Out->nc;

            if(ativa_col){
                // Reseta o contador e continua o somatório
                inc_pula_col = 0;
                soma_col = soma_col + pula_col;
            }
        }
    }

    return Out;
}
*/

void msg(char *s)
{
    printf("\nDados");
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
    image In, Saida;
    if (argc < 2)
        msg(argv[0]);

    img_name(argv[1], nameIn, nameOut, GRAY, GRAY);

    //-- read image
    In = img_get(nameIn, GRAY);

    //-- transformation

    int col, lin;

    col = In->nc;
    lin = In->nr;

    if(In->nc > 100){
        lin = lin * 100 / col;
        col = 100;
    }

    image Icon = img_create(lin, col, In->ml, In->tp);
    image Out = img_create(Icon->nr * 40, Icon->nc * 40, Icon->ml, Icon->tp);

    Saida = dados(In, Out, Icon);

    //-- save image
    img_put(Saida, nameOut, GRAY);

    sprintf(cmd, "%s %s &", VIEW, nameOut);
    system(cmd);
    img_free(In);
    img_free(Saida);
    return 0;
}
