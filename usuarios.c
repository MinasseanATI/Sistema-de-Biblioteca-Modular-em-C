#include <stdio.h>
#include <string.h>
#include <time.h>
#include "usuarios.h"
#include "utils.h"

struct CadastroUsuarios listaUsuarios[MAX_USUARIOS];
int totalUsuarios = 0;

void cadastrarUsuario() {
    if (totalUsuarios >= MAX_USUARIOS) {
        printf("\n[ERRO] Limite maximo de usuarios atingido!\n");
        return;
    }

    printf("\n---------------------------------------------\n");
    printf("              CADASTRAR USUARIO              \n");
    printf("---------------------------------------------\n");

    int proximaMatricula = totalUsuarios + 1;
    printf("Matricula gerada automaticamente: %d\n", proximaMatricula);

    char tempNome[100];
    char tempCurso[50];
    char tempTelefone[15];

    while (1) {
        printf("Digite o nome completo: ");
        fgets(tempNome, sizeof(tempNome), stdin);
        tempNome[strcspn(tempNome, "\n")] = '\0';
        
        if (strlen(tempNome) > 0) {
            break; 
        }
        
        printf("\n[ERRO] O nome nao pode estar vazio! Tente novamente.\n\n");
    }

    printf("Digite o curso: ");
    fgets(tempCurso, sizeof(tempCurso), stdin);
    tempCurso[strcspn(tempCurso, "\n")] = '\0';

    while (1) {
        printf("Digite o telefone (somente numeros, com DDD e 9º digito, ex: 47999998888): ");
        fgets(tempTelefone, sizeof(tempTelefone), stdin);
        tempTelefone[strcspn(tempTelefone, "\n")] = '\0';  
        
        if (strlen(tempTelefone) == 11) {
            break; 
        }
        
        printf("\n[ERRO] Telefone invalido! Deve conter exatamente 11 digitos (apenas numeros). Tente novamente.\n\n");
    }

    listaUsuarios[totalUsuarios].idmatricula = proximaMatricula;
    strcpy(listaUsuarios[totalUsuarios].nome, tempNome);
    strcpy(listaUsuarios[totalUsuarios].curso, tempCurso);
    strcpy(listaUsuarios[totalUsuarios].telefone, tempTelefone);

    time_t t = time(NULL);
    listaUsuarios[totalUsuarios].dataCadastro = *localtime(&t);

    totalUsuarios++;
    printf("\n[SUCESSO] Usuario cadastrado com sucesso!\n");
}

void listarUsuarios() {
    if (totalUsuarios == 0) {
        printf("\n[AVISO] Nenhum usuario cadastrado no sistema.\n");
        return;
    }

    printf("\n---------------------------------------------\n");
    printf("              LISTA DE USUARIOS              \n");
    printf("---------------------------------------------\n");
    
    int i; 
    for (i = 0; i < totalUsuarios; i++) {
        printf("Matricula: %d\n", listaUsuarios[i].idmatricula);
        printf("Nome     : %s\n", listaUsuarios[i].nome);
        printf("Curso    : %s\n", listaUsuarios[i].curso);
        printf("Telefone : %s\n", listaUsuarios[i].telefone);
        
        
        printf("Cadastro : %02d/%02d/%d\n", 
            listaUsuarios[i].dataCadastro.tm_mday, 
            listaUsuarios[i].dataCadastro.tm_mon + 1, 
            listaUsuarios[i].dataCadastro.tm_year + 1900);
        
        printf("---------------------------------------------\n");
    }
}

void pesquisarUsuarios() {
    if (totalUsuarios == 0) {
        printf("\n[AVISO] Nenhum usuario cadastrado para realizar a pesquisa.\n");
        return;
    }

    int opcao;
    
    
    while (1) {
        printf("\n---------------------------------------------\n");
        printf("              PESQUISAR USUARIO              \n");
        printf("---------------------------------------------\n");
        printf("[1] Pesquisar por Matricula (ID)\n");
        printf("[2] Pesquisar por Nome\n");
        printf("[0] Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); 
            printf("\n[ERRO] Entrada invalida! Digite um numero.\n");
            continue; 
        }
        while (getchar() != '\n'); 

        if (opcao == 1) {
            int idBusca;
            printf("Digite o numero da matricula: ");
            scanf("%d", &idBusca);
            while (getchar() != '\n');

            int encontrado = 0;
            int i;
            for (i = 0; i < totalUsuarios; i++) {
                if (listaUsuarios[i].idmatricula == idBusca) {
                    printf("\n--- Usuario Encontrado ---\n");
                    printf("Matrícula: %d\n", listaUsuarios[i].idmatricula);
                    printf("Nome     : %s\n", listaUsuarios[i].nome);
                    printf("Curso    : %s\n", listaUsuarios[i].curso);
                    printf("Telefone : %s\n", listaUsuarios[i].telefone);
                    printf("Cadastro : %02d/%02d/%d\n", 
                        listaUsuarios[i].dataCadastro.tm_mday, 
                        listaUsuarios[i].dataCadastro.tm_mon + 1, 
                        listaUsuarios[i].dataCadastro.tm_year + 1900);
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                printf("\n[AVISO] Nenhum usuario encontrado com a matricula %d.\n", idBusca);
            }
            break; 

        } else if (opcao == 2) {
            char nomeBusca[100];
            printf("Digite o nome (ou parte dele) para buscar: ");
            fgets(nomeBusca, sizeof(nomeBusca), stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

            int encontrado = 0;
            int i;
            for (i = 0; i < totalUsuarios; i++) {
                if (strstr(listaUsuarios[i].nome, nomeBusca) != NULL) {
                    printf("\n--- Usuário Encontrado ---\n");
                    printf("Matrícula: %d\n", listaUsuarios[i].idmatricula);
                    printf("Nome     : %s\n", listaUsuarios[i].nome);
                    printf("Curso    : %s\n", listaUsuarios[i].curso);
                    printf("Telefone : %s\n", listaUsuarios[i].telefone);
                    printf("Cadastro : %02d/%02d/%d\n", 
                        listaUsuarios[i].dataCadastro.tm_mday, 
                        listaUsuarios[i].dataCadastro.tm_mon + 1, 
                        listaUsuarios[i].dataCadastro.tm_year + 1900);
                    printf("---------------------------------------------\n");
                    encontrado = 1;
                }
            }
            if (!encontrado) {
                printf("\n[AVISO] Nenhum usuario encontrado com o nome contendo '%s'.\n", nomeBusca);
            }
            break; 

        } else if (opcao == 0) {
            return; 
        } else {
            printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
        }
    }
}
void editarUsuarios() {
    int matBusca;
    int i;
    int encontrado;
    int opcao;
    char novoBuffer[100];
    char tempTelefone[15];

    if (totalUsuarios == 0) {
        printf("\n[AVISO] Nenhum usuario cadastrado para editar.\n");
        return;
    }

    encontrado = 0;
    printf("\n---------------------------------------------\n");
    printf("                EDITAR USUARIO               \n");
    printf("---------------------------------------------\n");

    printf("Digite a matricula do usuario que deseja editar: ");
    if (scanf("%d", &matBusca) == 1) {
        limparBuffer();

        for (i = 0; i < totalUsuarios; i++) {
            if (listaUsuarios[i].idmatricula == matBusca) {
                encontrado = 1;
                printf("\n--- Usuario Encontrado [Matricula: %d] ---\n", matBusca);
                printf("Nome Atual    : %s\n", listaUsuarios[i].nome);
                printf("Curso Atual   : %s\n", listaUsuarios[i].curso);
                printf("Telefone Atual: %s\n", listaUsuarios[i].telefone);
                printf("-------------------------------------------\n");

                printf("Escolha o que deseja alterar:\n");
                printf(" [1] Alterar Nome\n");
                printf(" [2] Alterar Curso\n");
                printf(" [3] Alterar Telefone\n");
                printf(" [0] Cancelar\n");
                printf("Opcao: ");

                if (scanf("%d", &opcao) == 1) {
                    limparBuffer();

                    switch (opcao) {
                        case 1:
                            printf("Digite o novo Nome: ");
                            fgets(novoBuffer, sizeof(novoBuffer), stdin);
                            novoBuffer[strcspn(novoBuffer, "\n")] = '\0';
                            if (strlen(novoBuffer) > 0) {
                                strcpy(listaUsuarios[i].nome, novoBuffer);
                                printf("\n[SUCESSO] Nome atualizado com sucesso!\n");
                            }
                            break;

                        case 2:
                            printf("Digite o novo Curso: ");
                            fgets(novoBuffer, sizeof(novoBuffer), stdin);
                            novoBuffer[strcspn(novoBuffer, "\n")] = '\0';
                            if (strlen(novoBuffer) > 0) {
                                strcpy(listaUsuarios[i].curso, novoBuffer);
                                printf("\n[SUCESSO] Curso atualizado com sucesso!\n");
                            }
                            break;

                        case 3:
                            while (1) {
                                printf("Digite o novo Telefone (11 digitos, apenas numeros): ");
                                fgets(tempTelefone, sizeof(tempTelefone), stdin);
                                tempTelefone[strcspn(tempTelefone, "\n")] = '\0';

                                if (strlen(tempTelefone) == 11) {
                                    strcpy(listaUsuarios[i].telefone, tempTelefone);
                                    printf("\n[SUCESSO] Telefone atualizado com sucesso!\n");
                                    break;
                                }
                                printf("\n[ERRO] Telefone invalido! Deve conter exatamente 11 digitos.\n");
                            }
                            break;

                        case 0:
                            printf("\nEdicao cancelada.\n");
                            break;

                        default:
                            printf("\n[ERRO] Opçao invalida!\n");
                    }
                } else {
                    limparBuffer();
                    printf("\n[ERRO] Opcao invalida!\n");
                }
                break;
            }
        }

        if (!encontrado) {
            printf("\n[ERRO] Matricula %d nao encontrada.\n", matBusca);
        }
    } else {
        limparBuffer();
        printf("\n[ERRO] Entrada invalida!\n");
    }
}
