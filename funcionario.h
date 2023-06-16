#ifndef FUNCIONARIOS_FUNCIONARIO_H
#define FUNCIONARIOS_FUNCIONARIO_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>

typedef struct Funcionario
{
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
} TFunc;

// Imprime funcionario
void imprime(TFunc *func);

// Cria funcionario. Lembrar de usar free(funcionario)
TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, double salario);

// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(TFunc *func, FILE *out);

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
TFunc *le(FILE *in);

// Retorna tamanho do funcionario em bytes
int tamanho();

void sobrescreve_quarto_funcionario(FILE *in);

void adiciona_funcionario(FILE *in);

void adiciona_funcionario(FILE *in);

void le_funcionarios(FILE *out);

int cria_base_desordenada(FILE *out);

int cria_base_ordenada(FILE *out);

void busca_sequencial(FILE *in);

int tamanho_registro();

void apagarParticoes();

int qtdRegistros(FILE *in);

TFunc* busca_binaria(int cod, FILE *arq, int tam);

void insertion_sort_disco(FILE *arq, int tam);

void selection_sort_disco(FILE *arq, int tam);

void insertion_sort_memoria(FILE *arq, int tam);

void criaParticao(int numeroDeParticoes);

void printParticaoCodFuncionario(FILE *file, char nomeParticao[]);

int sizeFile(FILE *file, int contSizeFile);

void particionaArquivo(FILE *file, int numeroDeParticoes, int sizeFile);

int calcularNumeroParticoes(int numRegistros, int numRegistrosPorParticao);

#endif //FUNCIONARIOS_FUNCIONARIO_H
