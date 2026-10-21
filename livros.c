#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "livros.h"
#include "utils.h"

struct CadastroLivros listaLivros[MAX_LIVROS];
int totalLivros = 0;

void cadastrarLivro() {
    if (totalLivros >= MAX_LIVROS) {
        printf("\n[ERRO] Limite máximo de livros atingido!\n");
        return;
    }

    printf("\n---------------------------------------------\n");
    printf("              CADASTRAR LIVRO                \n");
    printf("---------------------------------------------\n");

    int proximoId = totalLivros + 1;
    printf("ID gerado automaticamente: %d\n", proximoId);

    char tempTitulo[100];
    char tempAutor[100];
    char tempEditora[50];
    int tempAno;
    int tempExemplares;

   
    while (1) {
        printf("Digite o título do livro: ");
        fgets(tempTitulo, sizeof(tempTitulo), stdin);
        tempTitulo[strcspn(tempTitulo, "\n")] = '\0';
        
        if (strlen(tempTitulo) > 0) {
            break;
        }
        printf("\n[ERRO] O título não pode estar vazio! Tente novamente.\n\n");
    }

 
    while (1) {
        printf("Digite o nome do autor: ");
        fgets(tempAutor, sizeof(tempAutor), stdin);
        tempAutor[strcspn(tempAutor, "\n")] = '\0';
        
        if (strlen(tempAutor) > 0) {
            break;
        }
        printf("\n[ERRO] O autor não pode estar vazio! Tente novamente.\n\n");
    }

    printf("Digite a editora: ");
    fgets(tempEditora, sizeof(tempEditora), stdin);
    tempEditora[strcspn(tempEditora, "\n")] = '\0';

    while (1) {
        printf("Digite o ano de publicação: ");
        if (scanf("%d", &tempAno) == 1 && tempAno > 0) {
            while (getchar() != '\n');
            break;
        }
        while (getchar() != '\n'); 
        printf("\n[ERRO] Ano inválido! Digite um número válido.\n\n");
    }

    while (1) {
        printf("Digite a quantidade de exemplares: ");
        if (scanf("%d", &tempExemplares) == 1 && tempExemplares >= 0) {
            while (getchar() != '\n'); 
            break;
        }
        while (getchar() != '\n');
        printf("\n[ERRO] Quantidade inválida! Digite um número inteiro maior ou igual a zero.\n\n");
    }

    // SALVANDO DADOS VÁLIDOS NA STRUCT OFICIAL 
    strcpy(listaLivros[totalLivros].titulo, tempTitulo);
    strcpy(listaLivros[totalLivros].autor, tempAutor);
    strcpy(listaLivros[totalLivros].editora, tempEditora);
    listaLivros[totalLivros].anoPublicado = tempAno;
    listaLivros[totalLivros].exemplares = tempExemplares;
    
    // Disponível (true) se tiver exemplares
    listaLivros[totalLivros].status = (tempExemplares > 0);

    totalLivros++;
    printf("\n[SUCESSO] Livro cadastrado com sucesso!\n");
}

void listarLivros() {
    if (totalLivros == 0) {
        printf("\n[AVISO] Nenhum livro cadastrado no sistema.\n");
        return;
    }

    printf("\n---------------------------------------------\n");
    printf("              LISTA DE LIVROS                \n");
    printf("---------------------------------------------\n");
    
    int i;
    for (i = 0; i < totalLivros; i++) {
        printf("ID Livro   : %d\n", i + 1); 
        printf("Título     : %s\n", listaLivros[i].titulo);
        printf("Autor      : %s\n", listaLivros[i].autor);
        printf("Editora    : %s\n", listaLivros[i].editora);
        printf("Ano        : %d\n", listaLivros[i].anoPublicado);
        printf("Exemplares : %d\n", listaLivros[i].exemplares);
        printf("Status     : %s\n", listaLivros[i].status ? "Disponível" : "Indisponível");
        printf("---------------------------------------------\n");
    }
}

void pesquisarLivros() {
    if (totalLivros == 0) {
        printf("\n[AVISO] Nenhum livro cadastrado para realizar a pesquisa.\n");
        return;
    }

    int opcao;
    
    while (1) {
        printf("\n---------------------------------------------\n");
        printf("               PESQUISAR LIVRO               \n");
        printf("---------------------------------------------\n");
        printf("[1] Pesquisar por ID do Livro\n");
        printf("[2] Pesquisar por Título\n");
        printf("[3] Pesquisar por Autor\n");
        printf("[0] Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); 
            printf("\n[ERRO] Entrada inválida! Digite um número.\n");
            continue;
        }
        while (getchar() != '\n'); 

        if (opcao == 1) {
            int idBusca;
            printf("Digite o ID do livro: ");
            scanf("%d", &idBusca);
            while (getchar() != '\n');

            int encontrado = 0;
            int i;
            for (i = 0; i < totalLivros; i++) {
                if ((i + 1) == idBusca) {
                    printf("\n--- Livro Encontrado ---\n");
                    printf("ID Livro   : %d\n", i + 1);
                    printf("Título     : %s\n", listaLivros[i].titulo);
                    printf("Autor      : %s\n", listaLivros[i].autor);
                    printf("Editora    : %s\n", listaLivros[i].editora);
                    printf("Ano        : %d\n", listaLivros[i].anoPublicado);
                    printf("Exemplares : %d\n", listaLivros[i].exemplares);
                    printf("Status     : %s\n", listaLivros[i].status ? "Disponível" : "Indisponível");
                    printf("---------------------------------------------\n");
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                printf("\n[AVISO] Nenhum livro encontrado com o ID %d.\n", idBusca);
            }
            break; 

        } else if (opcao == 2) {
            char tituloBusca[100];
            printf("Digite o título (ou parte dele): ");
            fgets(tituloBusca, sizeof(tituloBusca), stdin);
            tituloBusca[strcspn(tituloBusca, "\n")] = '\0';

            int encontrado = 0;
            int i;
            for (i = 0; i < totalLivros; i++) {
                if (strstr(listaLivros[i].titulo, tituloBusca) != NULL) {
                    printf("\n--- Livro Encontrado ---\n");
                    printf("ID Livro   : %d\n", i + 1);
                    printf("Título     : %s\n", listaLivros[i].titulo);
                    printf("Autor      : %s\n", listaLivros[i].autor);
                    printf("Editora    : %s\n", listaLivros[i].editora);
                    printf("Ano        : %d\n", listaLivros[i].anoPublicado);
                    printf("Exemplares : %d\n", listaLivros[i].exemplares);
                    printf("Status     : %s\n", listaLivros[i].status ? "Disponível" : "Indisponível");
                    printf("---------------------------------------------\n");
                    encontrado = 1;
                }
            }
            if (!encontrado) {
                printf("\n[AVISO] Nenhum livro encontrado com o título contendo '%s'.\n", tituloBusca);
            }
            break; 
        } else if (opcao == 3) {
            char autorBusca[100];
            printf("Digite o nome do autor (ou parte dele): ");
            fgets(autorBusca, sizeof(autorBusca), stdin);
            autorBusca[strcspn(autorBusca, "\n")] = '\0';

            int encontrado = 0;
            int i;
            for (i = 0; i < totalLivros; i++) {
                if (strstr(listaLivros[i].autor, autorBusca) != NULL) {
                    printf("\n--- Livro Encontrado ---\n");
                    printf("ID Livro   : %d\n", i + 1);
                    printf("Título     : %s\n", listaLivros[i].titulo);
                    printf("Autor      : %s\n", listaLivros[i].autor);
                    printf("Editora    : %s\n", listaLivros[i].editora);
                    printf("Ano        : %d\n", listaLivros[i].anoPublicado);
                    printf("Exemplares : %d\n", listaLivros[i].exemplares);
                    printf("Status     : %s\n", listaLivros[i].status ? "Disponível" : "Indisponível");
                    printf("---------------------------------------------\n");
                    encontrado = 1;
                }
            }
            if (!encontrado) {
                printf("\n[AVISO] Nenhum livro encontrado com o autor contendo '%s'.\n", autorBusca);
            }
            break; 

        } else if (opcao == 4) {
            return; 
        } else {
            printf("\n[ERRO] Opção inválida! Tente novamente.\n");
        }
    }
}
void editarLivros() {
    int idBusca;
    int indice;
    int opcao;
    int novoAno, novosExemplares;
    char novoBuffer[100];

    if (totalLivros == 0) {
        printf("\n[AVISO] Nenhum livro cadastrado para editar.\n");
        return;
    }

    printf("\n---------------------------------------------\n");
    printf("                EDITAR LIVRO                 \n");
    printf("---------------------------------------------\n");

    printf("Digite o ID do livro que deseja editar (1 a %d): ", totalLivros);
    if (scanf("%d", &idBusca) == 1) {
        limparBuffer();
        indice = idBusca - 1;

        if (indice < 0 || indice >= totalLivros) {
            printf("\n[ERRO] ID do livro inválido!\n");
            return;
        }

        printf("\n--- Livro Encontrado [ID: %d] ---\n", idBusca);
        printf("Título Atual   : %s\n", listaLivros[indice].titulo);
        printf("Autor Atual    : %s\n", listaLivros[indice].autor);
        printf("Editora Atual  : %s\n", listaLivros[indice].editora);
        printf("Ano Atual      : %d\n", listaLivros[indice].anoPublicado);
        printf("Exemplares     : %d\n", listaLivros[indice].exemplares);
        printf("-----------------------------------\n");

        printf("Escolha o que deseja alterar:\n");
        printf(" [1] Alterar Título\n");
        printf(" [2] Alterar Autor\n");
        printf(" [3] Alterar Editora\n");
        printf(" [4] Alterar Ano de Publicação\n");
        printf(" [5] Alterar Quantidade de Exemplares\n");
        printf(" [0] Cancelar\n");
        printf("Opção: ");

        if (scanf("%d", &opcao) == 1) {
            limparBuffer();

            switch (opcao) {
                case 1:
                    printf("Digite o novo Título: ");
                    fgets(novoBuffer, sizeof(novoBuffer), stdin);
                    novoBuffer[strcspn(novoBuffer, "\n")] = '\0';
                    if (strlen(novoBuffer) > 0) {
                        strcpy(listaLivros[indice].titulo, novoBuffer);
                        printf("\n[SUCESSO] Título atualizado com sucesso!\n");
                    }
                    break;

                case 2:
                    printf("Digite o novo Autor: ");
                    fgets(novoBuffer, sizeof(novoBuffer), stdin);
                    novoBuffer[strcspn(novoBuffer, "\n")] = '\0';
                    if (strlen(novoBuffer) > 0) {
                        strcpy(listaLivros[indice].autor, novoBuffer);
                        printf("\n[SUCESSO] Autor atualizado com sucesso!\n");
                    }
                    break;

                case 3:
                    printf("Digite a nova Editora: ");
                    fgets(novoBuffer, sizeof(novoBuffer), stdin);
                    novoBuffer[strcspn(novoBuffer, "\n")] = '\0';
                    if (strlen(novoBuffer) > 0) {
                        strcpy(listaLivros[indice].editora, novoBuffer);
                        printf("\n[SUCESSO] Editora atualizada com sucesso!\n");
                    }
                    break;

                case 4:
                    printf("Digite o novo Ano de Publicação: ");
                    if (scanf("%d", &novoAno) == 1) {
                        limparBuffer();
                        listaLivros[indice].anoPublicado = novoAno;
                        printf("\n[SUCESSO] Ano de publicação atualizado com sucesso!\n");
                    } else {
                        limparBuffer();
                        printf("\n[ERRO] Ano inválido!\n");
                    }
                    break;

                case 5:
                    printf("Digite a nova Quantidade de Exemplares: ");
                    if (scanf("%d", &novosExemplares) == 1 && novosExemplares >= 0) {
                        limparBuffer();
                        listaLivros[indice].exemplares = novosExemplares;
                        // Atualiza automaticamente a disponibilidade (status)
                        listaLivros[indice].status = (novosExemplares > 0);
                        printf("\n[SUCESSO] Quantidade de exemplares e status atualizados!\n");
                    } else {
                        limparBuffer();
                        printf("\n[ERRO] Quantidade inválida!\n");
                    }
                    break;

                case 0:
                    printf("\nEdição cancelada.\n");
                    break;

                default:
                    printf("\n[ERRO] Opção inválida!\n");
            }
        } else {
            limparBuffer();
            printf("\n[ERRO] Opção inválida!\n");
        }
    } else {
        limparBuffer();
        printf("\n[ERRO] Entrada inválida!\n");
    }
}
