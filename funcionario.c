#include "funcionario.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Imprime funcionario
void imprime(TFunc *func)
{
    printf("**********************************************");
    printf("\nFuncionario de codigo ");
    printf("%d", func->cod);
    printf("\nNome: ");
    printf("%s", func->nome);
    printf("\nCPF: ");
    printf("%s", func->cpf);
    printf("\nData de Nascimento: ");
    printf("%s", func->data_nascimento);
    printf("\nSalario: ");
    printf("%4.2f", func->salario);
    printf("\n**********************************************");
}

// Cria funcionario. Lembrar de usar free(func)
TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, double salario)
{
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    //inicializa espaço de memória com ZEROS
    if (func) memset(func, 0, sizeof(TFunc));
    //copia valores para os campos de func
    func->cod = cod;
    strcpy(func->nome, nome);
    strcpy(func->cpf, cpf);
    strcpy(func->data_nascimento, data_nascimento);
    func->salario = salario;
    return func;
}

// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(TFunc *func, FILE *out)
{
    fwrite(&func->cod, sizeof(int), 1, out);
    //func->nome ao invés de &func->nome, pois string já é ponteiro
    fwrite(func->nome, sizeof(char), sizeof(func->nome), out);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), out);
    fwrite(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), out);
    fwrite(&func->salario, sizeof(double), 1, out);
}

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
TFunc *le(FILE *in)
{
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    if (0 >= fread(&func->cod, sizeof(int), 1, in))
    {
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    fread(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), in);
    fread(&func->salario, sizeof(double), 1, in);
    return func;
}

// Retorna tamanho do funcionario em bytes
int tamanho()
{
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 15 //cpf
           + sizeof(char) * 11 //data_nascimento
           + sizeof(double); //salario
}

void insere_5_funcionarios(FILE *out)
{
    printf("Inserindo 5 funcionários no arquivo...");

    TFunc *f1 = funcionario(1, "Ana", "000.000.000-00", "01/01/1980", 3000);
    salva(f1, out);
    free(f1);
    TFunc *f2 = funcionario(2, "Carlos", "111.111.111-11", "01/01/1990", 500);
    salva(f2, out);
    free(f2);
    TFunc *f3 = funcionario(3, "Fátima", "222.222.222-22", "02/02/1980", 1000);
    salva(f3, out);
    free(f3);
    TFunc *f4 = funcionario(4, "Marcelo", "333.333.333-33", "03/03/1990", 1500);
    salva(f4, out);
    free(f4);
    TFunc *f5 = funcionario(5, "Silvia", "444.444.444-44", "04/04/1980", 900);
    salva(f5, out);
    free(f5);
}

int cria_base_desordenada(FILE *out)
{
    int numeroDeFuncionarios = 0;

    printf("\nInforme quantos funcionarios deseja cadastrar: ");
    scanf("%d", &numeroDeFuncionarios);

    int codigos[numeroDeFuncionarios];

    srand(time(NULL));

    for (int i = 0; i < numeroDeFuncionarios; i++)
    {
        codigos[i] = i + 1;
    }

    for (int i = numeroDeFuncionarios - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = codigos[i];
        codigos[i] = codigos[j];
        codigos[j] = temp;
    }

    for (int x = 0; x < numeroDeFuncionarios; x++)
    {
        int codigoAleatorio = codigos[x];
        TFunc *f1 = funcionario(codigoAleatorio, "Carlos", "000.000.000-00", "01/01/1980", 3000);
        salva(f1, out);
        free(f1);
    }

    return numeroDeFuncionarios;
}


int cria_base_ordenada(FILE *out)
{

    int numeroDeFuncionarios = 0;
    printf("\nInforme quantos funcionarios deseja cadastrar: ");
    scanf("%d", &numeroDeFuncionarios);

    srand(time(NULL));

    for(int x = 0; x < numeroDeFuncionarios; x++)
    {
        TFunc *f1 = funcionario(x+1, "Carlos", "000.000.000-00", "01/01/1980", 3000);
        salva(f1, out);
        free(f1);
    }

    return numeroDeFuncionarios;
}

void le_funcionarios(FILE *in)
{
    printf("\n\nLendo funcionários do arquivo...\n\n");
    rewind(in);
    TFunc *f;
    while ((f = le(in)) != NULL)
    {
        imprime(f);
        free(f);
    }
}

void le_segundo_funcionario(FILE *in)
{
    printf("\n\nLendo segundo funcionário do arquivo...\n\n");
    //tamanho() indica quantos bytes vamos pular, o que aqui é igual ao tamanho de um registro
    //(vamos pular o primeiro e nos posicionar no início do segundo)
    //** ATENÇÃO: não usar sizeof(Funcionario), pois ele pode retornar valor maior que o tamanho ocupado em disco,
    //            devido a alinhamento automático (ver https://en.wikipedia.org/wiki/Data_structure_alignment))
    //SEEK_SET indica o início do arquivo
    //ao final, o cursor estará posicionado em 0 + tamanho() +1
    fseek(in, tamanho(), SEEK_SET);
    TFunc *f = le(in);
    if (f != NULL)
    {
        imprime(f);
        free(f);
    }
}

void adiciona_funcionario(FILE *in)
{
    printf("\n\nAdicionando funcionário no final do arquivo...\n\n");
    //pula 5 registros para posicionar no início do final do arquivo
    fseek(in, tamanho() * 5, SEEK_SET);
    TFunc *f = funcionario(6, "Bruna", "666.666.666-66", "06/06/1980", 2500);
    salva(f, in);
    free(f);

    //lê funcionário que acabou de ser gravado
    //posiciona novamente o cursor no início desse registro
    fseek(in, tamanho() * 5, SEEK_SET);
    TFunc *f6 = le(in);
    if (f6 != NULL)
    {
        imprime(f6);
        free(f6);
    }
}

void sobrescreve_quarto_funcionario(FILE *in)
{
    printf("\n\nSobrescrevendo quarto funcionário do arquivo...\n\n");
    //pula primeiros 3 registros para posicionar no início do quarto registro
    fseek(in, tamanho() * 3, SEEK_SET);
    TFunc *f4 = funcionario(7, "Catarina", "777.777.777-77", "07/07/1990", 5000);
    salva(f4, in);
    free(f4);

    //lê funcionário que acabou de ser gravado
    //posiciona novamente o cursor no início desse registro
    fseek(in, tamanho() * 3, SEEK_SET);
    TFunc *f = le(in);
    if (f != NULL)
    {
        imprime(f);
        free(f);
    }
}

void busca_sequencial(FILE *in)
{
    int c;
    rewind(in);
    TFunc *f;
    int found = 0;
    int cont = 0;

    clock_t inicio = clock();

    printf("\n\nInforme o codigo do funcionario: ");
    scanf("%d", &c);

    while((f = le(in)) != NULL)
    {
        cont++;
        if (f->cod == c)
        {
            printf("\n======== Funcionario Encontrado ========\n\n");
            imprime(f);
            found = 1;
            break;
        }
        free(f);
    }
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    if(found)
    {
        printf("\n\nTempo de execucao da busca: %.2f\n segundos", tempo);
        printf("Numero de comparacoes: %d\n", cont);
    }
    else
    {
        printf("Funcionario nao pertence a base de dados!...");
        printf("\nNumero de comparacoes: %d\n", cont);
    }
}


int tamanho_registro()
{
    return sizeof(TFunc);
}

TFunc* busca_binaria(int cod, FILE *arq, int tam)
{
    clock_t inicio = clock();
    int left = 0, right = tam - 1;
    int cont = 0;
    TFunc* func;
    while(left <= right)
    {
        cont++;
        int middle = (left + right) / 2;
        fseek(arq, middle * tamanho_registro(), SEEK_SET);
        func = le(arq);
        if(cod == func->cod)
        {
            cont++;
            printf("\n====== F U N C I O N Á R I O   E N C O N T R A D O =======\n\n");
            imprime(func);
            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("\nTempo de busca: %lf segundos",tempo);
            printf("\nNumero de comparacoes: %d", cont);
            return func;
        }
        else if(func->cod < cod)
        {
            cont++;
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de busca: %lf\nNumero de comparacoes: %d\n", tempo, cont);
    return NULL;
}

void insertion_sort_disco(FILE *arq, int tam)
{
    int i;
    //faz o insertion sort
    for (int j = 2; j <= tam; j++)
    {
        //posiciona o arquivo no registro j
        fseek(arq, (j-1) * tamanho_registro(), SEEK_SET);
        TFunc *fj = le(arq);
        printf("\n********* Funcionario atual: %d\n", fj->cod);
        i = j - 1;
        //posiciona o cursor no registro i
        fseek(arq, (i-1) * tamanho_registro(), SEEK_SET);
        TFunc *fi = le(arq);
        printf("fi = %d\n", fi->cod);
        while ((i > 0) && (fi->cod > fj->cod))
        {
            //posiciona o cursor no registro i+1
            fseek(arq, i * tamanho_registro(), SEEK_SET);
            printf("Salvando funcionario %d na posicao %d\n", fi->cod, i+1);
            salva(fi, arq);
            i = i - 1;
            //lÃª registro i
            fseek(arq, (i-1) * tamanho_registro(), SEEK_SET);
            fi = le(arq);
            printf("fi = %d; i = %d\n", fi->cod, i);
        }
        //posiciona cursor no registro i + 1
        fseek(arq, (i) * tamanho_registro(), SEEK_SET);
        printf("*** Salvando funcionario %d na posicao %d\n", fj->cod, i+1);
        //salva registro j na posiÃ§Ã£o i
        salva(fj, arq);
    }
    //descarrega o buffer para ter certeza que dados foram gravados
    fflush(arq);
}
