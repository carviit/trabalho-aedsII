#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "funcionario.h"


void MSG_MENU( )
{
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPÇÕES DE MENU <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\n\t1. CRIAR BASE DE DADOS");
    printf("  \n\t2. IMPRIMIR BASE DE DADOS");
    printf("  \n\t3. BUSCA SEQUENCIAL");
    printf("  \n\t4. BUSCA BINÁRIA");
    printf("  \n\t5. LIMPAR TELA");
    printf("  \n\t6. SAIR");

}

void MENU(FILE *out)
{
    //Variaveis inteiras
    int opcao = 0;
    int numeroDeFuncionarios = 0;

    do
    {
        MSG_MENU();
        printf("\n\nDigite uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);
        switch(opcao)
        {
        case 1:

            int opc = 0;

            do{

            printf("\n1 --- Base Ordenada");
            printf("\n2 --- Base Desordenada\n");

            printf("\nOPÇÃO: ");
            scanf("%d", &opc);

            }while(opc != 1 && opc != 2);

            if(opc == 1){

            cria_e_salva(out);

            }else{


            }

            break;
        case 2:

                le_funcionarios_e_imprime(out);


            system("PAUSE");
            break;
        case 3:

            FILE *arquivo = fopen("funcionario.dat", "rb");
            busca_sequencial(arquivo);
            fclose(arquivo);
            break;

        case 4:

            busca_binaria(out, 5000);


            break;

        case 5:

            system("clear");
            break;

        default:
            system("clear");
            printf("\n\n\n\t >>>>>> MSG: Digite uma opcao valida!!! <<<<<<");
            system("PAUSE");
        } // fim do bloco switch
    }
    while(opcao != 6);
}

//FIM
