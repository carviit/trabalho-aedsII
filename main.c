#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcionario.h"
#include "interface.h"

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Portuguese");

    //declara ponteiro para arquivo
    FILE *out;

    //abre arquivo
    if ((out = fopen("funcionario.dat", "w+b")) == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else
    {

          MENU(out);

    }
}
