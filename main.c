#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <locale.h>

#include "functions.h"

#define MAX_PACIENTES 100
#define MAX_LINE_SIZE 1024
#define MAX_CHAR 8

int main() {
        Medico medico[1];
        Relatorio relatorio[1];
        Paciente pacientes[MAX_PACIENTES];
        FILE * arq;
        int totalPacientes = 0;
        int opcao;
        char crm[MAX_CHAR], senha[MAX_CHAR];

        do {
                printf("");
                printf("1 - Entrar\n");
                printf("2 - Cadastrar\n");
                printf("3 - Sair\n");
                printf("Opcao: ");
                scanf("%d", & opcao);
                switch (opcao) {
                case 1:
                        loginMedico(medico, arq);
                        printf("1 - Menu Pacientes\n");
                        setlocale(LC_ALL, "Portuguese");
                        printf("2 - Menu Relatórios\n");
                        printf("3 - Sair\n");
                        printf("Opcao: ");
                        scanf("%d", & opcao);
                        switch (opcao) {
                        case 1:
                                system("CLS");
                                printf("1 - Cadastrar Paciente\n");
                                printf("2 - Exibir Paciente\n");
                                printf("3 - Pesquisar paciente\n");
                                printf("4 - Editar Paciente\n ");
                                printf("5 - Excluir Paciente\n ");
                                printf("6 - Sair\n");
                                scanf("%d", & opcao);
                                switch (opcao) {
                                case 1:
                                        cadastrarPaciente(pacientes, & totalPacientes, arq);
                                        break;
                                case 2:
                                        exibirPacientes(pacientes, totalPacientes, arq);
                                        break;
                                case 3:
                                        pesquisarPaciente(pacientes, totalPacientes, arq);
                                        break;
                                case 4:
                                        editar_paciente(pacientes, arq);
                                        break;
                                case 5:
                                        deletar_paciente(pacientes, arq);
                                case 6:
                                        break;
                                }
                        case 2:
                                printf("1 - Cadastrar Relatorio\n");
                                printf("2 - Exibir Relatorio\n");
                                printf("3 - Editar Relatorio\n ");
                                printf("4 - Excluir Relatorio\n ");
                                printf("5 - Voltar\n");
                                scanf("%d", & opcao);
                                switch (opcao) {
                                case 1:
                                        cadastrar_relatorio(relatorio, arq);
                                        break;
                                case 2:
                                        exibir_relatorio(relatorio, arq);
                                        break;
                                case 3:
                                        editar_relatorio(relatorio, arq);
                                        break;
                                case 4:
                                        deletar_relatorio(relatorio, arq);
                                        break;
                                case 5:
                                        break;
                                }
                        case 3:
                                printf("Saindo do programa...\n");
                                break;
                        default:
                                printf("Opcao invalida\n");
                        }

                        break;
                case 2:
                        cadastraMedicos(medico, arq);
                        break;
                case 3:
                        printf("Fechando o sistema\n");
                        break;

                }
        } while (opcao != 3);

        return 0;
}
