#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAX_PACIENTES 100
#define MAX_LINE_SIZE 1024

void cadastrarPaciente(Paciente *pacientes, int *totalPacientes, FILE *arq) {
    if (*totalPacientes == MAX_PACIENTES) {
        printf("Nao e possivel cadastrar mais pacientes\n");
        return;
    }
    if (arq = fopen("paciente.csv", "a")) {
        system("CLS");
        printf("CPF: ");
        scanf("%s", pacientes[*totalPacientes].cpf);
        printf("Nome: ");
        scanf("%s", pacientes[*totalPacientes].nome);
        printf("Telefone: ");
        scanf("%s", pacientes[*totalPacientes].telefone);
        printf("Endereco: ");
        scanf("%s", pacientes[*totalPacientes].endereco);
        printf("Sexo: ");
        scanf("%s", pacientes[*totalPacientes].sexo);
        printf("Data de Nascimento: ");
        scanf("%s", pacientes[*totalPacientes].data_nascimento);
        (*totalPacientes)++;
        printf("Paciente cadastrado com sucesso!\n");
        fprintf(arq, "%s,%s,%s,%s,%s,%s\n", pacientes[*totalPacientes - 1].cpf, pacientes[*totalPacientes - 1].nome,
                pacientes[*totalPacientes - 1].telefone, pacientes[*totalPacientes - 1].endereco, pacientes[*totalPacientes - 1].sexo,
                pacientes[*totalPacientes - 1].data_nascimento);
        fclose(arq);
    }
}

void exibirPacientes(Paciente *pacientes, int totalPacientes, FILE *arq) {
    char linha[MAX_LINE_SIZE];
    arq = fopen("paciente.csv","r");
   if(arq == NULL){
       printf("Não foi possível abrir o arquivo");
       return;
   }
    printf("Pacientes cadastrados:\n ");
    while(fgets(linha, sizeof (linha),arq)){
        printf("%s \n",linha);
   }

}
int pesquisarPaciente(Paciente *pacientes, int totalPacientes, FILE *arq) {
    char nome[50];
    printf("Digite o nome do paciente a ser pesquisado: ");
    scanf("%s", nome);

    arq = fopen("paciente.csv", "r");
    if (arq == NULL) {
        printf("O arquivo não pode ser aberto.\n");
        return 1;
    }

    char linha[MAX_LINE_SIZE];
    while (fgets(linha, MAX_LINE_SIZE, arq) != NULL) {
        // Quebrar a linha em colunas separadas por virgula
        char *token = strtok(linha, ",");
        char paciente_nome[50];
        strcpy(paciente_nome, token);

        // Verificar se o nome do paciente corresponde ao nome procurado
        if (strcmp(paciente_nome, nome) == 0) {
            // Se sim, exibir a linha correspondente
            printf("%s", linha);
            printf("\n");
            fclose(arq);
            return 0;
        }
    }

    printf("O paciente nao foi encontrado.\n");
    fclose(arq);
    return 0;
}
void deletar_paciente(Paciente *paciente, FILE *arq){
    printf("Funcao em construcao\n");
}
void editar_paciente(Paciente *paciente, FILE *arq){
    printf("Funcao em construcao\n");
}
void cadastrar_relatorio(Relatorio *relatorio, FILE *arq){

    if (arq = fopen("relatorio.csv", "a")){

        system("CLS");
        printf("CPF do Paciente: \n");
        scanf("%s", relatorio->cpf_paciente);
        printf("Data de Nascimento: \n");
        scanf("%s", relatorio->data);
        printf("Causa: \n");
        scanf("%s",relatorio->causa);
        printf("Sintomas: \n");
        scanf("%s",relatorio->sintoma);
        printf("Medicamentos: \n");
        scanf("%s", relatorio->medicamentos);

        fprintf(arq,"%s,%s,%s,%s,%s\n",relatorio->cpf_paciente,relatorio->data,relatorio->causa,relatorio->sintoma,relatorio->medicamentos);

        fclose(arq);
    }
}

void exibir_relatorio(Relatorio *relatorio, FILE *arq){
    char cpf_paciente_busca[12], linha[MAX_LINE_SIZE];
    arq = fopen("relatorio.csv","r");
    if(arq == NULL){
        printf("Impossivel abrir o relatório do paciente");
        return;
    }
    printf("CPF do Paciente que deseja buscar o relatório");
    scanf("%s",cpf_paciente_busca);

    int encontrado;
    while(fgets(linha, sizeof (linha),arq)){
        char cpf[12];
        sscanf(linha, "%[^,]", cpf);

        // Verifica se o CPF corresponde ao buscado
        if(strcmp(cpf, cpf_paciente_busca) == 0){
            printf("%s\n", linha);
            encontrado = 1;
        }
    }
    if(!encontrado){
        printf("Nenhum relatorio encontrado para o CPF informado.\n");
    }
    fclose(arq);

}

void editar_relatorio(Relatorio *relatorio, FILE *arq){
    printf("Funcao em desenvolvimento\n");
}
void deletar_relatorio(Relatorio *relatorio, FILE *arq){
    printf("Funcao em desenvolvimento\n");
}
