#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "relatorios.h"
#include "emprestimos.h"
#include "usuarios.h"
#include "livros.h"
#include "utils.h"

// --- RELATÓRIO 1: LIVROS MAIS EMPRESTADOS ---
void relatorioLivrosMaisEmprestados() {
    int i;
    int contadorEmprestimos[MAX_LIVROS];
    int maxEmprestimos;
    int idLivroAtual;
    int temEmprestimos;

    if (totalLivros == 0) {
        printf("\n[AVISO] Nenhum livro cadastrado no sistema.\n");
        return;
    }

    if (totalEmprestimos == 0) {
        printf("\n[AVISO] Nenhum empréstimo registrado para gerar estatísticas.\n");
        return;
    }

    // Inicializa a contagem de cada livro com 0
    for (i = 0; i < totalLivros; i++) {
        contadorEmprestimos[i] = 0;
    }

    // Conta quantas vezes cada ID de livro aparece no histórico de empréstimos
    temEmprestimos = 0;
    for (i = 0; i < totalEmprestimos; i++) {
        idLivroAtual = listaEmprestimos[i].idLivros;
        if (idLivroAtual >= 1 && idLivroAtual <= totalLivros) {
            contadorEmprestimos[idLivroAtual - 1]++;
            temEmprestimos = 1;
        }
    }

    printf("\n---------------------------------------------\n");
    printf("     RELATÓRIO: LIVROS MAIS EMPRESTADOS      \n");
    printf("---------------------------------------------\n");

    // Exibe a lista ordenada do mais emprestado para o menos emprestado
    for (maxEmprestimos = totalEmprestimos; maxEmprestimos > 0; maxEmprestimos--) {
        for (i = 0; i < totalLivros; i++) {
            if (contadorEmprestimos[i] == maxEmprestimos) {
                printf("ID Livro   : %d\n", i + 1);
                printf("Título     : %s\n", listaLivros[i].titulo);
                printf("Autor      : %s\n", listaLivros[i].autor);
                printf("Empréstimos: %d vez(es)\n", contadorEmprestimos[i]);
                printf("---------------------------------------------\n");
            }
        }
    }
}

// --- RELATÓRIO 2: USUÁRIOS COM EMPRÉSTIMOS EM ATRASO ---
void relatorioUsuariosEmAtraso() {
    int i;
    int j;
    int atrasadosEncontrados;
    time_t tempoAtual;
    struct tm dataEmp;
    time_t tempoEmprestimo;
    time_t tempoPrevisto;
    double segundosDiferenca;
    int diasRestantes;
    int idUsuario;
    int idLivro;
    int idxUsuario;
    int idxLivro;

    if (totalEmprestimos == 0) {
        printf("\n[AVISO] Nenhum empréstimo registrado no sistema.\n");
        return;
    }

    printf("\n---------------------------------------------\n");
    printf("  RELATÓRIO: USUÁRIOS COM EMPRÉSTIMOS EM ATRASO\n");
    printf("---------------------------------------------\n");

    tempoAtual = time(NULL);
    atrasadosEncontrados = 0;

    for (i = 0; i < totalEmprestimos; i++) {
        if (listaEmprestimos[i].status) { // Se o empréstimo estiver ATIVO
            // Copia a data do empréstimo para manipulação
            dataEmp = listaEmprestimos[i].dataEmpprestimo;
            tempoEmprestimo = mktime(&dataEmp);
            
            // Soma os dias de prazo (dataPrevista) convertidos em segundos (dias * 24 * 3600)
            tempoPrevisto = tempoEmprestimo + ((long)listaEmprestimos[i].dataPrevista * 86400);
            
            segundosDiferenca = difftime(tempoPrevisto, tempoAtual);
            diasRestantes = (int)(segundosDiferenca / 86400);

            // Se o prazo for negativo, está em atraso
            if (diasRestantes < 0) {
                atrasadosEncontrados = 1;
                idUsuario = listaEmprestimos[i].idmatricula;
                idLivro = listaEmprestimos[i].idLivros;

                idxUsuario = -1;
                for (j = 0; j < totalUsuarios; j++) {
                    if (listaUsuarios[j].idmatricula == idUsuario) {
                        idxUsuario = j;
                        break;
                    }
                }

                idxLivro = idLivro - 1;

                printf("ID Empréstimo : %d\n", listaEmprestimos[i].idEmprestimo);
                printf("Matrícula Usu.: %d\n", idUsuario);
                if (idxUsuario != -1) {
                    printf("Nome Usuário  : %s\n", listaUsuarios[idxUsuario].nome);
                    printf("Telefone      : %s\n", listaUsuarios[idxUsuario].telefone);
                }
                if (idxLivro >= 0 && idxLivro < totalLivros) {
                    printf("Livro Pendente: %s\n", listaLivros[idxLivro].titulo);
                }
                printf("Dias de Atraso: %d dia(s)\n", -diasRestantes);
                printf("---------------------------------------------\n");
            }
        }
    }

    if (!atrasadosEncontrados) {
        printf("\n[PARABÉNS] Não há nenhum empréstimo em atraso no momento!\n");
        printf("---------------------------------------------\n");
    }
}
