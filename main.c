#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <locale.h>

#include "functions.h"

#define MAX_PACIENTES 100
#define MAX_LINE_SIZE 1024
#define MAX_CHAR 8

int loginMedico(const char *cpf_medico, const char *senha){
    FILE *arq;
    char linha[MAX_LINE_SIZE];
    int encontrado = 0;

    arq = fopen("medico.csv", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    while (fgets(linha, sizeof(linha), arq) != NULL) {
        char *token = strtok(linha, ",");
        if (strcmp(token, cpf_medico) == 0) {
            token = strtok(NULL, ",");
            if (token != NULL) {
                encontrado = 1;
                break;
            }
        }
    }

    fclose(arq);

    if (encontrado) {
        printf("Bem-vindo!\n");
        return 1;
    } else {
        return 0;
    }
}


int main() {
        Medico medico[1];
        Relatorio relatorio[1];
        Paciente pacientes[MAX_PACIENTES];
        FILE * arq;
        int totalPacientes = 0;
        int opcao,c, encontrado = 0;
        char cpf_medico[12], senha[8], linha[MAX_LINE_SIZE];
        setbuf(stdin,NULL);
        do {
                //Criação dos menus
                printf("");
                printf("1 - Entrar\n");
                printf("2 - Cadastrar\n");
                printf("3 - Sair\n");
                printf("Opcao: ");
                scanf("%d", & opcao);
                while((c = getchar()) != '\n' && c != EOF);
                switch (opcao) {
                //Caso 1: Entrar, leva direto ao menu principal caso o login esteja correto
                case 1:
                        printf("CPF: ");
                        fgets(cpf_medico, sizeof(cpf_medico), stdin);
                        printf("Senha: ");
                        fgets(senha,sizeof(senha),stdin);
                        // Removendo o caractere de nova linha do final do CPF
                        cpf_medico[strcspn(cpf_medico, "\n")] = '\0';
                        if(loginMedico(cpf_medico,senha) == 0){
                            printf("Senha ou CPF incorretos!\n");
                            printf("Fechando o programa... \n");
                            return 0;
                        }

                        printf("1 - Menu Pacientes\n");
                        setlocale(LC_ALL, "Portuguese");
                        printf("2 - Menu Relatórios\n");
                        printf("3 - Sair\n");
                        printf("Opcao: ");
                        scanf(" %d", &opcao);
                        while((c = getchar()) != '\n' && c != EOF);
                        switch (opcao) {
                        case 1:
                            //caso 1: Menu de Pacientes
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
                                        printf("Insira os dados para cadastrar o paciente: ");
                                        cadastrarPaciente(pacientes, & totalPacientes, arq);
                                        break;
                                case 2:
                                        setlocale(LC_ALL,"Portuguese");
                                        printf("EXIBIÇÃO DE PACIENTES: \n");
                                        exibirPacientes(pacientes, totalPacientes, arq);
                                        break;
                                case 3:
                                        printf("PESQUISA DE PACIENTES: \n");
                                        pesquisarPaciente(pacientes, totalPacientes, arq);
                                        break;
                                case 4:
                                        setlocale(LC_ALL,"Portuguese");
                                        printf("EDIÇÃO DE PACIENTES");
                                        editar_paciente(pacientes, arq, totalPacientes);
                                        break;
                                case 5:
                                        setlocale(LC_ALL,"Portuguese");
                                        printf("EXCLUSÃO DE PACIENTES\n");
                                        deletar_paciente(pacientes, arq);
                                case 6:
                                        break;
                                }
                        case 2:
                            //Caso 2: Menu de relatórios
                                printf("1 - Cadastrar Relatorio\n");
                                printf("2 - Exibir Relatorio\n");
                                printf("3 - Editar Relatorio\n");
                                printf("4 - Excluir Relatorio\n");
                                printf("5 - Sair\n");

                                scanf("%d", & opcao);
                                switch (opcao) {
                                case 1:
                                        setlocale(LC_ALL,"Portuguese");
                                        printf("Você está no menu de cadastro de Relatório: \n");
                                        cadastrar_relatorio(relatorio, arq);
                                        break;
                                case 2:
                                        setlocale(LC_ALL,"Portuguese");
                                        printf("Você está no exibição de Relatório: \n");
                                        exibir_relatorio(relatorio, arq);
                                        break;
                                case 3:
                                        setlocale(LC_ALL,"Portuguese");
                                        printf("Você está no menu de edição de relatórios: \n");
                                        editar_relatorio(relatorio, arq);
                                        break;
                                case 4:
                                        setlocale(LC_ALL,"Portuguese");
                                        printf("Você está no menu de edição de relatórios: \n");
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
