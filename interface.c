#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include <dirent.h>

void MSG_MENU( )
{
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\n\t1. CRIAR BASE DE DADOS");
    printf("  \n\t2. IMPRIMIR BASE DE DADOS");
    printf("  \n\t3. BUSCA SEQUENCIAL");
    printf("  \n\t4. ORDENAR FUNCIONÁRIOS");
    printf("  \n\t5. BUSCA BINARIA");
    printf("  \n\t6. PARTICIONAR ARQUIVOS");
    printf("  \n\t7. LIMPAR TELA");
    printf("  \n\t8. SAIR");
}

void MENU(FILE *out)
{
    int controle;
    int aux, aux2, base_total = 0, base,op, numeroDeRegistros;
    TFunc *aux3;
    do
    {
        MSG_MENU();
        printf("\n\nDIGITE UMA OPCAO: ");
        fflush(stdin);
        scanf("%d", &controle);
        switch(controle)
        {
        case 1:

            printf("\n1 --- BASE ORDENADA");
            printf("\n2 --- BASE DESORDENADA\n");

            printf("\nOPÇÃO: ");
            scanf("%d", &op);

            if(op == 1)
            {

                base = cria_base_ordenada(out);
                base_total += base;

                printf("\n>>> BASE CRIADA COM SUCESSO");

            }
            else if(op == 2)
            {

                base = cria_base_desordenada(out);
                base_total += base;
                printf("\n>>> BASE CRIADA COM SUCESSO");

            }
            break;

        case 2:
            le_funcionarios(out);
            break;

        case 3:
            busca_sequencial(out);
            break;

        case 4:

            printf("\n1 --- Insertion Sort");
            printf("\n2 --- Selection Sort\n");

            printf("\nOPÇÃO: ");
            scanf("%d", &op);

            if(op == 1)
            {
                insertion_sort_disco(out, base_total);

            }
            else if (op == 2)
            {
                selection_sort_disco(out, base_total);

            }

            break;

        case 5:
            printf("\nDigite o codigo que deseja buscar: ");
            scanf("%d", &aux);
            busca_binaria(aux, out, base_total);
            break;

        case 6:

            printf("\nDigite a quantidade de registros por partição desejadas: ");
            scanf("%d", &numeroDeRegistros);

            int particoes_total = calcularNumeroParticoes(base_total, numeroDeRegistros);

            criaParticao(particoes_total);

            particionaArquivo(out, particoes_total, base_total);

            break;

        case 7:

            system("clear");
            break;

        case 8:

            //SAIR
            system("clear");
            apagarParticoes();
            printf("\n\n\n\t >>>>>> MSG: Saindo do MODULO...!!! <<<<<<");
            break;

        default:
            system("clear");
            printf("\n\n\n\t >>>>>> MSG: Digite uma opcao valida!!! <<<<<<");
        } // fim do bloco switch
    }
    while(controle != 8);
}
