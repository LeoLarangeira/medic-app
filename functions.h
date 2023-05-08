#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdio.h>
#define MAX_PACIENTES 100
#define MAX_LINE_SIZE 1024

typedef struct {
    char cpf[12];
    char nome[50];
    char telefone[20];
    char endereco[100];
    char sexo[10];
    char data_nascimento[11];
} Paciente;

typedef struct{
    char cpf_paciente[12];
    char data[11];
    char causa[100];
    char sintoma[100];
    char medicamentos[100];
}Relatorio;

typedef struct{
    int crm;
    char nome[50];
    char telefone[20];
    char endereco[100];
    char senha[8];
}Medico;

void cadastrarPaciente(Paciente *pacientes, int *totalPacientes, FILE *arq);
void exibirPacientes(Paciente *pacientes, int totalPacientes, FILE *arq);
int pesquisarPaciente(Paciente *pacientes, int totalPacientes, FILE *arq);
void deletar_paciente(Paciente *paciente, FILE *arq);
void editar_paciente(Paciente *paciente, FILE *arq);
void cadastrar_relatorio(Relatorio *relatorio, FILE *arq);
void exibir_relatorio(Relatorio *relatorio, FILE *arq);
void editar_relatorio(Relatorio *relatorio, FILE *arq);
void deletar_relatorio(Relatorio *relatorio, FILE *arq);

#endif // FUNCTIONS_H_INCLUDED
