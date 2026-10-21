#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "utils.h"
#include "livros.h"
#include "usuarios.h"
#include "emprestimos.h"
#include "salvar.h"
#include "relatorios.h"

void inicializarSistema() {
    totalLivros = 0;
    totalUsuarios = 0;
    totalEmprestimos = 0;
}

int main() {
	setlocale(LC_ALL, "Portuguese");
    int opcao;
    int subOpcao;
    
    inicializarSistema();
    
    do {
        printf("\n=============================================\n");
        printf("     SISTEMA DE GERENCIAMENTO DE BIBLIOTECA  \n");
        printf("=============================================\n");
        printf(" [1] Gerenciar Livros\n");
        printf(" [2] Gerenciar Usuarios\n");
        printf(" [3] Gerenciar Emprestimos\n");
        printf(" [4] Relatorios\n"); 
        printf(" [0] Sair do Sistema\n");
        printf("---------------------------------------------\n");
        printf(" Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("\n[ERRO] Caractere invalido! Digite apenas numeros.\n");
            limparBuffer(); 
            opcao = -1;  
        } else {
            limparBuffer(); 
        }
        
        switch(opcao) {
            case 1:
                do {
                    printf("\n---------------------------------------------\n");
                    printf("               GESTAO DE LIVROS                \n");
                    printf("---------------------------------------------\n");
                    printf(" [1] Cadastrar um livro?\n");
                    printf(" [2] Ver livros disponiveis?\n");
                    printf(" [3] Pesquisar algum livro (Id, Autor ou Titulo)?\n");
					printf(" [4] Editar algum livro (Id, Autor ou Titulo)?\n");
                    printf(" [0] Retornar ao Menu Principal\n");
                    printf("---------------------------------------------\n");
                    printf(" Escolha uma opcao: ");
                    
                    if (scanf("%d", &subOpcao) != 1) {
                        printf("\n[ERRO] Caractere inválido! Digite apenas numeros.\n");
                        limparBuffer(); 
                        subOpcao = -1;  
                    } else {
                        limparBuffer(); 
                    }
                    
                    switch(subOpcao) {
                        case 1:
                            cadastrarLivro();
                            break;
                        case 2:
                            listarLivros();
                            break;
                        case 3:
                            pesquisarLivros(); 
                            break;
                        case 4:
                            editarLivros();
                            salvarLivros();
                            break;
                        case 0:
                            printf("\nRetornando ao menu principal...\n");
                            break;
                        default:
                            if (subOpcao != -1) {
                                printf("\n[ERRO] Opcao inválida! Tente novamente.\n");    
                            }
                    }
                } while(subOpcao != 0);
                break;

            case 2:
                do {
                    printf("\n---------------------------------------------\n");
                    printf("              GESTAO DE USUARIOS             \n");
                    printf("---------------------------------------------\n");
                    printf(" [1] Cadastrar um Usuario\n");
                    printf(" [2] Ver Usuarios\n");
                    printf(" [3] Pesquiar Usuario\n");
                    printf(" [4] Editar Usuario\n");
                    printf(" [0] Retornar ao Menu Principal\n");
                    printf("---------------------------------------------\n");
                    printf(" Escolha uma opcao: ");

                    if (scanf("%d", &subOpcao) != 1) {
                        printf("\n[ERRO] Caractere inválido! Digite apenas numeros.\n");
                        limparBuffer();
                        subOpcao = -1;
                    } else {
                        limparBuffer();
                    }

                    switch(subOpcao) {
                        case 1:
                            cadastrarUsuario();
                            break;
                        case 2:
                            listarUsuarios();
                            break;
                        case 3 :
                        	pesquisarUsuarios();
                        	break;
                        case 4:
                        	editarUsuarios();
                        	salvarUsuarios();
                        	break;
                        case 0:
                            printf("\nRetornando ao menu principal...\n");
                            break;
                        default:
                            if (subOpcao != -1) {
                                printf("\n[ERRO] Opcao inválida! Tente novamente.\n");
                            }
                    }
                } while(subOpcao != 0);
                break;

            case 3:
                do {
                    printf("\n---------------------------------------------\n");
                    printf("            GESTAO DE EMPRESTIMOS            \n");
                    printf("---------------------------------------------\n");
                    printf(" [1] Cadastrar um Emprestimos\n");
                    printf(" [2] Ver Status de Emprestimos\n");
                    printf(" [3] Renovar Emprestimos\n");
                    printf(" [4] Devolver um Livros\n");
                    printf(" [0] Retornar ao Menu Principal\n");
                    printf("---------------------------------------------\n");
                    printf(" Escolha uma opcao: ");

                    if (scanf("%d", &subOpcao) != 1) {
                        printf("\n[ERRO] Caractere inválido! Digite apenas numeros.\n");
                        limparBuffer();
                        subOpcao = -1;
                    } else {
                        limparBuffer();
                    }

                    switch(subOpcao) {
                        case 1:
                            cadastrarEmprestimos();
                            break;
                        case 2:
                            listarEmprestimos();
                            break;
                        case 3:
                        	renovarEmprestimos();
                            break;
                        case 4:
                            devolverLivros();
                            break;
                        case 0:
                            printf("\nRetornando ao menu principal...\n");
                            break;
                        default:
                            if (subOpcao != -1) {
                                printf("\n[ERRO] Opcao inválida! Tente novamente.\n");
                            }
                    }
                } while(subOpcao != 0);
                break;

            case 4:
                do {
                    printf("\n---------------------------------------------\n");
                    printf("                 RELATORIOS                  \n");
                    printf("---------------------------------------------\n");
                    printf(" [1] Livros mais emprestados\n");
                    printf(" [2] Usuarios com emprestimos em atraso\n");
                    printf(" [0] Retornar ao Menu Principal\n");
                    printf("---------------------------------------------\n");
                    printf(" Escolha uma opcao: ");

                    if (scanf("%d", &subOpcao) != 1) {
                        printf("\n[ERRO] Caractere inválido! Digite apenas numeros.\n");
                        limparBuffer();
                        subOpcao = -1;
                    } else {
                        limparBuffer();
                    }

                    switch(subOpcao) {
                        case 1:
                           relatorioLivrosMaisEmprestados();
                            break;
                        case 2:
                            relatorioUsuariosEmAtraso();
                            break;
                        case 0:
                            printf("\nRetornando ao menu principal...\n");
                            break;
                        default:
                            if (subOpcao != -1) {
                                printf("\n[ERRO] Opcao inválida! Tente novamente.\n");
                            }
                    }
                } while(subOpcao != 0);
                break;

            case 0:
                printf("Encerrando o sistema...\n");
                break;

            default:
                if(opcao != -1){ 
                    printf("\n[ERRO] Opcao inválida! Tente novamente.\n");
                }
        }
    } while (opcao != 0);

    return 0;
}
