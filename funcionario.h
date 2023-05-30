//
// Created by Vanessa Braganholo on 16/09/2018.
//

#ifndef FUNCIONARIOS_FUNCIONARIO_H
#define FUNCIONARIOS_FUNCIONARIO_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Funcionario
{
    int cod;
    char nome[50];
    char cpf[12];
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

void le_funcionarios_e_imprime(FILE *in);

void cria_e_salva(FILE *out);

void gerarNome(int contador, char *nome);

int gerarNumeroAleatorio(int min, int max);

void gerarCPF(char *cpf);

void gerarDataNascimento(char *dataNascimento);

void busca_sequencial(FILE *in);

void busca_binaria(FILE *arq, int tam);

int tamanho_registro();

int tamanho_arquivo(FILE *arq);

#endif //FUNCIONARIOS_FUNCIONARIO_H

