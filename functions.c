#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAX_PACIENTES 100
#define MAX_LINE_SIZE 1024


//função para verificar se duas senhas são iguais
int verificaSenha(char *senha1,char *senha2){
    if(strcmp(senha1,senha2) == 0 ){
        return 1;
    }else{
        //caso sejam diferentes, é solicitado que o usuário digite as senhas
        setlocale(LC_ALL,"Portuguese");
        printf("Senhas não compativeis\n");
        printf("Senha: ");
        scanf("%s",senha1);
        printf("Digite novamenta a senha: ");
        scanf("%s", senha2);
        //Chama a função novamente para verificar as novas senhas inseridas
        verificaSenha(senha1,senha2);
    }
}

//função para cadastrar os médicos
void cadastraMedicos(Medico *medico, FILE *arq){
//posteriomente usar o fgets para poder ler de forma mais segura!
    char senha1[8];
    char senha2[8];
    if(arq = fopen("medico.csv","a")){
        system("CLS");
        printf("CPF: ");
        fgets(medico->cpf_medico, sizeof(medico->cpf_medico), stdin);
        printf("Nome: ");
        fgets(medico->nome, sizeof(medico->nome), stdin);
        printf("Telefone: ");
        fgets(medico->telefone, sizeof(medico->telefone),stdin);
        setlocale(LC_ALL, "Portuguese");
        printf("Endereço: ");
        fgets(medico->endereco, sizeof(medico->endereco),stdin);
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
    if(arq = fopen("medico.csv","r")){
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
            printf("Senha ou usuários inválidos!\n");
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
        fgets(pacientes->cpf,sizeof(pacientes->cpf),stdin);
        printf("Nome: ");
        fgets(pacientes->nome,sizeof(pacientes->nome),stdin);
        printf("Telefone: ");
        fgets(pacientes->telefone, sizeof(pacientes->telefone),stdin);
        printf("Endereco: ");
        fgets(pacientes->endereco,sizeof(pacientes->endereco),stdin);
        printf("Sexo: ");
        fgets(pacientes->sexo,sizeof(pacientes->sexo),stdin);
        printf("Data de Nascimento: ");
        fgets(pacientes->data_nascimento,sizeof(pacientes->data_nascimento),stdin);
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
       printf("Não foi possível abrir o arquivo\n");
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
    char cpf_cliente[12];

    //Lê o CPF a ser excluido
    setlocale(LC_ALL,"Portuguese");
    printf("CPF: ");
    fgets(cpf_cliente, sizeof(cpf_cliente), stdin);

    //Abre o arquivo original em modo leitura
    FILE* arquivoOriginal = fopen("paciente.csv", "r");
    if(arquivoOriginal == NULL){
        printf("Erro ao abri o arquivo.\n");
        return 1;
    }

    //Abre o arquivo temporário em modo escrita
    FILE* arquivoTemporario = fopen("temp.csv", "w");
    if(arquivoTemporario == NULL){
        setlocale(LC_ALL,"Portuguese");
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(arquivoOriginal);
        return 1;
    }

    char linha[MAX_LINE_SIZE];
    int contadorLinhas = 0;
    int linhaExcluida = 0;

    // Lê as linhas do arquivo original e as copia para o arquivo temporário
    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL) {
        if (!linhaExcluida && strstr(linha, cpf_cliente) != NULL) {
            // Encontrou a linha a ser excluída
            linhaExcluida = 1;
            contadorLinhas = 0;
        }

        if (!linhaExcluida || contadorLinhas > 5) {
            // Copia a linha para o arquivo temporário
            fputs(linha, arquivoTemporario);
        }

        if (linhaExcluida) {
            contadorLinhas++;
            if (contadorLinhas > 5) {
                // Reinicia o processo de cópia
                linhaExcluida = 0;
            }
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);
    remove("paciente.csv");
    rename("temp.csv","paciente.csv");



}
void editar_paciente(Paciente *pacientes, FILE *arq, int totalPacientes){
    char cpf_paciente[12];



    printf("CPF: ");
    fgets(cpf_paciente,sizeof(cpf_paciente),stdin);
    setlocale(LC_ALL,"Portuguese");
    printf("CPF: ");
    fgets(cpf_paciente, sizeof(cpf_paciente), stdin);

    //Abre o arquivo original em modo leitura
    FILE* arquivoOriginal = fopen("paciente.csv", "r");
    if(arquivoOriginal == NULL){
        printf("Erro ao abri o arquivo.\n");
        return 1;
    }

    //Abre o arquivo temporário em modo escrita
    FILE* arquivoTemporario = fopen("temp.csv", "w");
    if(arquivoTemporario == NULL){
        setlocale(LC_ALL,"Portuguese");
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(arquivoOriginal);
        return 1;
    }

    char linha[MAX_LINE_SIZE];
    int contadorLinhas = 0;
    int linhaExcluida = 0;

    // Lê as linhas do arquivo original e as copia para o arquivo temporário
    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL) {
        if (!linhaExcluida && strstr(linha, cpf_paciente) != NULL) {
            // Encontrou a linha a ser excluída
            linhaExcluida = 1;
            contadorLinhas = 0;
        }

        if (!linhaExcluida || contadorLinhas > 5) {
            // Copia a linha para o arquivo temporário
            fputs(linha, arquivoTemporario);
        }

        if (linhaExcluida) {
            contadorLinhas++;
            if (contadorLinhas > 5) {
                // Reinicia o processo de cópia
                linhaExcluida = 0;
            }
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);
    remove("paciente.csv");
    rename("temp.csv","paciente.csv");
    setlocale(LC_ALL,"Portuguese");
    printf("Dados para a edição:\n");
    arq = fopen("paciente.csv","a");
    if(!arq == NULL){
        system("CLS");
        printf("CPF: ");
        fgets(pacientes->cpf,sizeof(pacientes->cpf),stdin);
        printf("Nome: ");
        fgets(pacientes->nome,sizeof(pacientes->nome),stdin);
        printf("Telefone: ");
        fgets(pacientes->telefone, sizeof(pacientes->telefone),stdin);
        printf("Endereco: ");
        fgets(pacientes->endereco,sizeof(pacientes->endereco),stdin);
        printf("Sexo: ");
        fgets(pacientes->sexo,sizeof(pacientes->sexo),stdin);
        printf("Data de Nascimento: ");
        fgets(pacientes->data_nascimento,sizeof(pacientes->data_nascimento),stdin);
        (*totalPacientes)++;
        printf("Paciente cadastrado com sucesso!\n");
        fprintf(arq, "%s,%s,%s,%s,%s,%s\n", pacientes[*totalPacientes - 1].cpf, pacientes[*totalPacientes - 1].nome,
                pacientes[*totalPacientes - 1].telefone, pacientes[*totalPacientes - 1].endereco, pacientes[*totalPacientes - 1].sexo,
                pacientes[*totalPacientes - 1].data_nascimento);
        fclose(arq);
    }
    printf("Dados atualizados com sucesso! \n");

}
void cadastrar_relatorio(Relatorio *relatorio, FILE *arq){

    if (arq = fopen("relatorio.csv", "a")){

        system("CLS");
        printf("CPF do Paciente: \n");
        fgets(relatorio->cpf_paciente,sizeof(relatorio->cpf_paciente),stdin);
        printf("Data de Nascimento: \n");
        fgets(relatorio->data,sizeof(relatorio->data),stdin);
        printf("Causa: \n");
        fgets(relatorio->causa,sizeof(relatorio->causa),stdin);
        printf("Sintomas: \n");
        fgets(relatorio->sintoma,sizeof(relatorio->sintoma),stdin);
        printf("Medicamentos: \n");
        fgets(relatorio->medicamentos,sizeof(relatorio->medicamentos),stdin);

        fprintf(arq,"%s,%s,%s,%s,%s\n",relatorio->cpf_paciente,relatorio->data,relatorio->causa,relatorio->sintoma,relatorio->medicamentos);

        fclose(arq);
    }
}

void exibir_relatorio(Relatorio *relatorio, FILE *arq){
    char cpf_paciente_busca[12], linha[MAX_LINE_SIZE];
    arq = fopen("relatorio.csv","r");
    if(arq == NULL){
        printf("Impossivel abrir o relatório do paciente"\n);
        return;
    }
    printf("CPF do Paciente que deseja buscar o relatório: ");
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


}
void deletar_relatorio(Relatorio *relatorio, FILE *arq){
    char cpf_cliente[12];

    //Lê o CPF a ser excluido
    setlocale(LC_ALL,"Portuguese");
    printf("CPF: \n");
    fgets(cpf_cliente, sizeof(cpf_cliente), stdin);

    //Abre o arquivo original em modo leitura
    FILE* arquivoOriginal = fopen("relatorio.csv", "r");
    if(arquivoOriginal == NULL){
        printf("Erro ao abri o arquivo.\n");
        return 1;
    }

    //Abre o arquivo temporário em modo escrita
    FILE* arquivoTemporario = fopen("temp.csv", "w");
    if(arquivoTemporario == NULL){
        setlocale(LC_ALL,"Portuguese");
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(arquivoOriginal);
        return 1;
    }

    char linha[MAX_LINE];
    int contadorLinhas = 0;
    int linhaExcluida = 0;

    // Lê as linhas do arquivo original e as copia para o arquivo temporário
    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL) {
        if (!linhaExcluida && strstr(linha, cpf_cliente) != NULL) {
            // Encontrou a linha a ser excluída
            linhaExcluida = 1;
            contadorLinhas = 0;
        }

        if (!linhaExcluida || contadorLinhas > 5) {
            // Copia a linha para o arquivo temporário
            fputs(linha, arquivoTemporario);
        }

        if (linhaExcluida) {
            contadorLinhas++;
            if (contadorLinhas > 5) {
                // Reinicia o processo de cópia
                linhaExcluida = 0;
            }
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);
    remove("relatorio.csv");
    rename("temp.csv","relatorio.csv");
}
