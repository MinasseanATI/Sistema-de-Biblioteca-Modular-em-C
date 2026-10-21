#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "emprestimos.h"
#include "usuarios.h" 
#include "livros.h"   
#include "utils.h"

struct SistemaEmprestimo listaEmprestimos[MAX_EMPRESTIMOS];
int totalEmprestimos = 0;

// Função auxiliar para calcular a data prevista de devolução
struct tm calcularDataDevolucao(struct tm dataInicio, int diasAdicionais) {
    time_t tempoEmSegundos = mktime(&dataInicio);
    tempoEmSegundos += (diasAdicionais * 24 * 60 * 60); // Soma os dias em segundos
    return *localtime(&tempoEmSegundos);
}

void cadastrarEmprestimos() {
    int i; 
    int tempMatricula, tempIdLivro;
    int usuarioEncontrado;
    int indiceLivro;
    int indiceLivroReal;
    time_t t;

    if (totalEmprestimos >= MAX_EMPRESTIMOS) {
        printf("\n[ERRO] Limite máximo de empréstimos atingido!\n");
        return;
    }

    if (totalUsuarios == 0) {
        printf("\n[AVISO] Não há usuários cadastrados para realizar um empréstimo.\n");
        return;
    }

    if (totalLivros == 0) {
        printf("\n[AVISO] Não há livros cadastrados para realizar um empréstimo.\n");
        return;
    }

    printf("\n---------------------------------------------\n");
    printf("            REALIZAR EMPRÉSTIMO              \n");
    printf("---------------------------------------------\n");

    // --- VALIDAÇÃO DA MATRÍCULA DO USUÁRIO ---
    while (1) {
        printf("Digite a matrícula do usuário: ");
        if (scanf("%d", &tempMatricula) == 1) {
            while (getchar() != '\n'); 
            
            usuarioEncontrado = 0;
            for (i = 0; i < totalUsuarios; i++) {
                if (listaUsuarios[i].idmatricula == tempMatricula) {
                    usuarioEncontrado = 1;
                    break;
                }
            }
            if (usuarioEncontrado) {
                break; 
            }
            printf("\n[ERRO] Matrícula não encontrada no sistema. Tente novamente.\n\n");
        } else {
            while (getchar() != '\n');
            printf("\n[ERRO] Entrada inválida! Digite um número.\n\n");
        }
    }
    
    // --- VALIDAÇÃO DO ID DO LIVRO E DISPONIBILIDADE ---
    while (1) {
        printf("Digite o ID do livro: ");
        if (scanf("%d", &tempIdLivro) == 1) {
            while (getchar() != '\n'); 
            
            indiceLivro = tempIdLivro - 1; 
            
            if (indiceLivro >= 0 && indiceLivro < totalLivros) {
                if (listaLivros[indiceLivro].status == true && listaLivros[indiceLivro].exemplares > 0) {
                    break; 
                } else {
                    printf("\n[ERRO] Livro indisponível ou sem exemplares no momento. Escolha outro.\n\n");
                }
            } else {
                printf("\n[ERRO] ID de livro não encontrado. Tente novamente.\n\n");
            }
        } else {
            while (getchar() != '\n');
            printf("\n[ERRO] Entrada inválida! Digite um número.\n\n");
        }
    }
    
    // --- EFETIVANDO O EMPRÉSTIMO ---
    indiceLivroReal = tempIdLivro - 1;

    listaEmprestimos[totalEmprestimos].idEmprestimo = totalEmprestimos + 1;
    listaEmprestimos[totalEmprestimos].idmatricula = tempMatricula;
    listaEmprestimos[totalEmprestimos].idLivros = tempIdLivro;
    
    t = time(NULL);
    listaEmprestimos[totalEmprestimos].dataEmpprestimo = *localtime(&t);
    listaEmprestimos[totalEmprestimos].dataPrevista = PRAZO_DEVOLUCAO_DIAS; 
    listaEmprestimos[totalEmprestimos].status = true; 

    // Atualiza o estoque do livro
    listaLivros[indiceLivroReal].exemplares--;
    if (listaLivros[indiceLivroReal].exemplares == 0) {
        listaLivros[indiceLivroReal].status = false; 
    }

    totalEmprestimos++;
    printf("\n[SUCESSO] Empréstimo registrado com sucesso!\n");
}
void listarEmprestimos() {
    int i;
    time_t tempoAtual;
    struct tm dataDev;
    time_t tempoPrevisto;
    double segundosDiferenca;
    int diasRestantes;

    if (totalEmprestimos == 0) {
        printf("\n[AVISO] Nenhum empréstimo registrado no sistema.\n");
        return;
    }

    printf("\n---------------------------------------------\n");
    printf("            LISTA DE EMPRÉSTIMOS             \n");
    printf("---------------------------------------------\n");
    
    tempoAtual = time(NULL);

    for (i = 0; i < totalEmprestimos; i++) {
        dataDev = calcularDataDevolucao(listaEmprestimos[i].dataEmpprestimo, listaEmprestimos[i].dataPrevista);

        printf("ID Empréstimo : %d\n", listaEmprestimos[i].idEmprestimo);
        printf("Matrícula Usu.: %d\n", listaEmprestimos[i].idmatricula);
        printf("ID do Livro   : %d\n", listaEmprestimos[i].idLivros);
        
        printf("Data Emprést. : %02d/%02d/%d\n", 
            listaEmprestimos[i].dataEmpprestimo.tm_mday, 
            listaEmprestimos[i].dataEmpprestimo.tm_mon + 1, 
            listaEmprestimos[i].dataEmpprestimo.tm_year + 1900);
            
        printf("Data Prev. Dev: %02d/%02d/%d\n", 
            dataDev.tm_mday, 
            dataDev.tm_mon + 1, 
            dataDev.tm_year + 1900);

        if (listaEmprestimos[i].status) { 
            tempoPrevisto = mktime(&dataDev);
            segundosDiferenca = difftime(tempoPrevisto, tempoAtual);
            diasRestantes = (int)(segundosDiferenca / (24 * 3600));

            if (diasRestantes > 0) {
                printf("Status        : Ativo (%d dia(s) restante(s))\n", diasRestantes);
            } else if (diasRestantes == 0) {
                printf("Status        : Ativo (Vence HOJE!)\n");
            } else {
                printf("Status        : Ativo (EM ATRASO por %d dia(s)!)\n", -diasRestantes);
            }
        } else {
            printf("Status        : Finalizado (Devolvido)\n");
        }

        printf("---------------------------------------------\n");
    }
}

// --- LÓGICA DE DEVOLUÇÃO DE LIVROS ---
void devolverLivros() {
    int idEmpBusca;
    int i;
    int encontrado;
    int indiceLivro;

    if (totalEmprestimos == 0) {
        printf("\n[AVISO] Nenhum empréstimo registrado para realizar devolução.\n");
        return;
    }

    printf("\n---------------------------------------------\n");
    printf("              DEVOLUÇÃO DE LIVRO             \n");
    printf("---------------------------------------------\n");

    while (1) {
        printf("Digite o ID do Empréstimo a ser devolvido: ");
        if (scanf("%d", &idEmpBusca) == 1) {
            while (getchar() != '\n');

            encontrado = 0;
            for (i = 0; i < totalEmprestimos; i++) {
                if (listaEmprestimos[i].idEmprestimo == idEmpBusca) {
                    encontrado = 1;

                    if (!listaEmprestimos[i].status) {
                        printf("\n[AVISO] Este empréstimo já consta como DEVOLVIDO!\n");
                        return;
                    }

                    listaEmprestimos[i].status = false;

                    indiceLivro = listaEmprestimos[i].idLivros - 1;
                    listaLivros[indiceLivro].exemplares++;
                    listaLivros[indiceLivro].status = true; 

                    printf("\n[SUCESSO] Livro '%s' devolvido com sucesso!\n", listaLivros[indiceLivro].titulo);
                    return;
                }
            }

            if (!encontrado) {
                printf("\n[ERRO] Empréstimo com ID %d não foi encontrado. Tente novamente.\n\n", idEmpBusca);
            }
        } else {
            while (getchar() != '\n');
            printf("\n[ERRO] Entrada inválida! Digite um número.\n\n");
        }
    }
}

// --- LÓGICA DE RENOVAÇÃO DE EMPRÉSTIMO ---
void renovarEmprestimos() {
    int idEmpBusca;
    int i;
    int encontrado;
    struct tm dataDev;

    if (totalEmprestimos == 0) {
        printf("\n[AVISO] Nenhum empréstimo registrado para renovação.\n");
        return;
    }

    printf("\n---------------------------------------------\n");
    printf("             RENOVAR EMPRÉSTIMO              \n");
    printf("---------------------------------------------\n");

    while (1) {
        printf("Digite o ID do Empréstimo para renovação: ");
        if (scanf("%d", &idEmpBusca) == 1) {
            while (getchar() != '\n');

            encontrado = 0;
            for (i = 0; i < totalEmprestimos; i++) {
                if (listaEmprestimos[i].idEmprestimo == idEmpBusca) {
                    encontrado = 1;

                    if (!listaEmprestimos[i].status) {
                        printf("\n[ERRO] Não é possível renovar um empréstimo que já foi devolvido!\n");
                        return;
                    }

                    listaEmprestimos[i].dataPrevista += 7;

                    dataDev = calcularDataDevolucao(listaEmprestimos[i].dataEmpprestimo, listaEmprestimos[i].dataPrevista);

                    printf("\n[SUCESSO] Empréstimo renovado com sucesso por mais 7 dias!\n");
                    printf("Nova Data Prevista de Devolução: %02d/%02d/%d\n",
                        dataDev.tm_mday,
                        dataDev.tm_mon + 1,
                        dataDev.tm_year + 1900);
                    return;
                }
            }

            if (!encontrado) {
                printf("\n[ERRO] Empréstimo com ID %d não foi encontrado. Tente novamente.\n\n", idEmpBusca);
            }
        } else {
            while (getchar() != '\n');
            printf("\n[ERRO] Entrada inválida! Digite um número.\n\n");
        }
    }
}
