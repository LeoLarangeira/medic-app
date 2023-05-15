#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAX_PACIENTES 100
#define MAX_LINE_SIZE 1024

//fun��o para verificar se duas senhas s�o iguais
int verificaSenha(char *senha1,char *senha2){
    if(strcmp(senha1,senha2) == 0 ){
        return 1;
    }else{
        //caso sejam diferentes, � solicitado que o usu�rio digite as senhas
        setlocale(LC_ALL,"Portuguese");
        printf("Senhas n�o compativeis\n");
        printf("Senha: ");
        scanf("%s",senha1);
        printf("Digite novamenta a senha: ");
        scanf("%s", senha2);
        //Chama a fun��o novamente para verificar as novas senhas inseridas
        verificaSenha(senha1,senha2);
    }
}

//fun��o para cadastrar os m�dicos
void cadastraMedicos(Medico *medico, FILE *arq){
//posteriomente usar o fgets para poder ler de forma mais segura!
    char senha1[8];
    char senha2[8];
    if(arq = fopen("medico.csv","a")){
        system("CLS");
        printf("CPF: ");
        scanf("%s", medico->cpf_medico);
        printf("Nome: ");
        scanf("%s", medico->nome);
        printf("Telefone: ");
        scanf("%s", medico->telefone);
        setlocale(LC_ALL, "Portuguese");
        printf("Endere�o: ");
        scanf("%s", medico->telefone);
        printf("Senha: ");
        scanf("%s", &senha1);
        printf("Vamos verificar novamente a senha: \n");
        printf("Digite novamente a senha: ");
        scanf("%s",&senha2);
        if(verificaSenha(senha1,senha2) == 1){
            strcpy(medico->senha, senha1);
            fprintf(arq,"%s,%s,%s,%s,%s",medico->cpf_medico,medico->senha,medico->nome,medico->telefone,medico->endereco);
            printf("Medico cadastrado com sucesso\n");
            fclose(arq);
        }

    }

}
void loginMedico(Medico *medico, FILE *arq){
    char cpf_medico[12], senha[8];
    int encontrado = 0;
    if(arq == fopen("medico.csv","r")){
        printf("CPF: ");
        scanf("%s", cpf_medico);
        printf("Senha: ");
        scanf("%s", senha);
        while(fscanf(arq,"%[^,],%[^,],%[^,],%[^,],%[^\n]",medico->cpf_medico,medico->senha,medico->nome,medico->telefone,medico->endereco) != EOF){
            if(strcmp(medico->cpf_medico, cpf_medico) == 0 && strcmp(medico->senha, senha) == 0){
                encontrado = 1;
                break;
            }
        }
        if(encontrado){
            printf("Bem-vindo: %c", medico->nome);
        }else{
            setlocale(LC_ALL,"Portuguese");
            printf("Senha ou usu�rios inv�lidos!");
        }
        fclose(arq);
    }else{
        printf("Erro ao abrir o arquivo!\n");
    }

}
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
       printf("N�o foi poss�vel abrir o arquivo");
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
        printf("O arquivo n�o pode ser aberto.\n");
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
    //isso aqui com banco de dados seria muito mais facil e pratico viu, vou mentir n�o.
    int opcao;
    setlocale(LC_ALL,"Portuguese");
    printf("Voc� est� no menu de edi��o de dados de pacientes: ");

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
        printf("Impossivel abrir o relat�rio do paciente");
        return;
    }
    printf("CPF do Paciente que deseja buscar o relat�rio");
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
