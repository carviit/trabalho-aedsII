#include "funcionario.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Imprime funcionario
void imprime(TFunc *func)
{
    printf("**********************************************");
    printf("\nFuncionario de código ");
    printf("%d", func->cod);
    printf("\nNome: ");
    printf("%s", func->nome);
    printf("\nCPF: ");
    printf("%s", func->cpf);
    printf("\nData de Nascimento: ");
    printf("%s", func->data_nascimento);
    printf("\nSalário: ");
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


void gerarNome(int contador, char *nome)
{
    sprintf(nome, "Func %d", contador); // Gera o nome com base no valor do contador

}

int gerarNumeroAleatorio(int min, int max)
{

    return rand() % (max - min + 1) + min;
}

void gerarCPF(char *cpf)
{

    int digito1 = gerarNumeroAleatorio(0, 9);
    int digito2 = gerarNumeroAleatorio(0, 9);
    int digito3 = gerarNumeroAleatorio(0, 9);
    int digito4 = gerarNumeroAleatorio(0, 9);
    int digito5 = gerarNumeroAleatorio(0, 9);

    sprintf(cpf, "%d%d%d%d.%d%d%d%d%d", digito1, digito2, digito3, digito4, digito5, digito1, digito2, digito3, digito4);
}

void gerarDataNascimento(char *dataNascimento)
{
    int dia = gerarNumeroAleatorio(1, 28);
    int mes = gerarNumeroAleatorio(1, 12);
    int ano = gerarNumeroAleatorio(1970, 2002);

    sprintf(dataNascimento, "%02d/%02d/%04d", dia, mes, ano);
}

void cria_e_salva(FILE *out)
{
    int n = 0;

    printf("\nDigite quantos funcionários deseja cadastrar: ");
    scanf("%d", &n);

    printf("\n>>> Inserindo %d funcionários no arquivo...", n);

    int i = 0;

    srand(time(NULL));

    for (i = 0; i < n; i++)
    {
        char nome[50];
        gerarNome(i + 1, nome);

        char cpf[12];
        gerarCPF(cpf);

        char dataNascimento[11];
        gerarDataNascimento(dataNascimento);

        TFunc *f1 = funcionario(i + 1, nome, cpf, dataNascimento, (i + 1) * 450);
        salva(f1, out);
        fflush(out);
        free(f1);
    }
}

void le_funcionarios_e_imprime(FILE *in)
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

void busca_sequencial(FILE *in) {

    TFunc funcionario;
    int i = 0;
    int codigo;

    printf("\nDigite o código do funcionário que deseja buscar: ");
    scanf("%d", &codigo);

    while (fread(&funcionario.cod, sizeof(int), 1, in) == 1) {
        fread(funcionario.nome, sizeof(char), sizeof(funcionario.nome), in);
        fread(funcionario.cpf, sizeof(char), sizeof(funcionario.cpf), in);
        fread(funcionario.data_nascimento, sizeof(char), sizeof(funcionario.data_nascimento), in);
        fread(&funcionario.salario, sizeof(double), 1, in);

        if (codigo == funcionario.cod) {
            printf("\n\n====== Funcionário encontrado ======\n");
            printf("ID: %d\n", funcionario.cod);
            printf("Nome: %s\n", funcionario.nome);
            printf("CPF: %s\n", funcionario.cpf);
            printf("Data de Nascimento: %s\n", funcionario.data_nascimento);
            printf("Salário: R$%.2f\n", funcionario.salario);
            i = 1;
            break;
        }
    }

    if (!i) {
        printf("\n>>> Funcionário não encontrado.\n");
    }
}




