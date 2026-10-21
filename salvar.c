#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "salvar.h"
#include "usuarios.h"
#include "livros.h"
#include "emprestimos.h"

// --- 1. SALVAR USUÁRIOS (txt) ---
void salvarUsuarios() {
    FILE *arq = fopen("usuarios.txt", "w");
    if (arq == NULL) {
        printf("\n[ERRO] Não foi possível abrir 'usuarios.txt' para escrita.\n");
        return;
    }

    int i;
    // Escreve a quantidade total na primeira linha
    fprintf(arq, "%d\n", totalUsuarios);

    for (i = 0; i < totalUsuarios; i++) {
        fprintf(arq, "%d;%s;%s;%s;%d;%d;%d\n",
            listaUsuarios[i].idmatricula,
            listaUsuarios[i].nome,
            listaUsuarios[i].curso,
            listaUsuarios[i].telefone,
            listaUsuarios[i].dataCadastro.tm_mday,
            listaUsuarios[i].dataCadastro.tm_mon,
            listaUsuarios[i].dataCadastro.tm_year);
    }

    fclose(arq);
}

// --- 2. SALVAR LIVROS (txt) ---
void salvarLivros() {
    FILE *arq = fopen("livros.txt", "w");
    if (arq == NULL) {
        printf("\n[ERRO] Não foi possível abrir 'livros.txt' para escrita.\n");
        return;
    }

    int i;
    fprintf(arq, "%d\n", totalLivros);

    for (i = 0; i < totalLivros; i++) {
        fprintf(arq, "%s;%s;%s;%d;%d;%d\n",
            listaLivros[i].titulo,
            listaLivros[i].autor,
            listaLivros[i].editora,
            listaLivros[i].anoPublicado,
            listaLivros[i].exemplares,
            listaLivros[i].status ? 1 : 0);
    }

    fclose(arq);
}

// --- 3. SALVAR EMPRÉSTIMOS (txt) ---
void salvarEmprestimos() {
    FILE *arq = fopen("emprestimos.txt", "w");
    if (arq == NULL) {
        printf("\n[ERRO] Não foi possível abrir 'emprestimos.txt' para escrita.\n");
        return;
    }

    int i;
    fprintf(arq, "%d\n", totalEmprestimos);

    for (i = 0; i < totalEmprestimos; i++) {
        fprintf(arq, "%d;%d;%d;%d;%d;%d;%d;%d\n",
            listaEmprestimos[i].idEmprestimo,
            listaEmprestimos[i].idmatricula,
            listaEmprestimos[i].idLivros,
            listaEmprestimos[i].dataEmpprestimo.tm_mday,
            listaEmprestimos[i].dataEmpprestimo.tm_mon,
            listaEmprestimos[i].dataEmpprestimo.tm_year,
            listaEmprestimos[i].dataPrevista,
            listaEmprestimos[i].status ? 1 : 0);
    }

    fclose(arq);
}

// --- 4. BACKUP AUTOMÁTICO ---
void realizarBackup() {
    // Copia o conteúdo dos arquivos principais para cópias de segurança (.bak)
    char ch;
    FILE *origem, *destino;

    // Backup Usuários
    origem = fopen("usuarios.txt", "r");
    if (origem != NULL) {
        destino = fopen("usuarios_backup.bak", "w");
        while ((ch = fgetc(origem)) != EOF) fputc(ch, destino);
        fclose(origem);
        fclose(destino);
    }

    // Backup Livros
    origem = fopen("livros.txt", "r");
    if (origem != NULL) {
        destino = fopen("livros_backup.bak", "w");
        while ((ch = fgetc(origem)) != EOF) fputc(ch, destino);
        fclose(origem);
        fclose(destino);
    }

    // Backup Empréstimos
    origem = fopen("emprestimos.txt", "r");
    if (origem != NULL) {
        destino = fopen("emprestimos_backup.bak", "w");
        while ((ch = fgetc(origem)) != EOF) fputc(ch, destino);
        fclose(origem);
        fclose(destino);
    }
}

// --- 5. ORQUESTRADOR DE SALVAMENTO ---
void salvarTodosOsDados() {
    realizarBackup(); // Cria o backup antes de regravar os arquivos oficiais
    salvarUsuarios();
    salvarLivros();
    salvarEmprestimos();
}

// --- 6. CARREGAR DADOS DOS ARQUIVOS (Inicialização) ---
void carregarTodosOsDados() {
    FILE *arq;
    int i, statusInt;

    // Carregar Usuários
    arq = fopen("usuarios.txt", "r");
    if (arq != NULL) {
        if (fscanf(arq, "%d\n", &totalUsuarios) == 1) {
            for (i = 0; i < totalUsuarios; i++) {
                fscanf(arq, "%d;%99[^;];%49[^;];%14[^;];%d;%d;%d\n",
                    &listaUsuarios[i].idmatricula,
                    listaUsuarios[i].nome,
                    listaUsuarios[i].curso,
                    listaUsuarios[i].telefone,
                    &listaUsuarios[i].dataCadastro.tm_mday,
                    &listaUsuarios[i].dataCadastro.tm_mon,
                    &listaUsuarios[i].dataCadastro.tm_year);
            }
        }
        fclose(arq);
    }

    // Carregar Livros
    arq = fopen("livros.txt", "r");
    if (arq != NULL) {
        if (fscanf(arq, "%d\n", &totalLivros) == 1) {
            for (i = 0; i < totalLivros; i++) {
                fscanf(arq, "%99[^;];%99[^;];%49[^;];%d;%d;%d\n",
                    listaLivros[i].titulo,
                    listaLivros[i].autor,
                    listaLivros[i].editora,
                    &listaLivros[i].anoPublicado,
                    &listaLivros[i].exemplares,
                    &statusInt);
                listaLivros[i].status = (statusInt == 1);
            }
        }
        fclose(arq);
    }

    // Carregar Empréstimos
    arq = fopen("emprestimos.txt", "r");
    if (arq != NULL) {
        if (fscanf(arq, "%d\n", &totalEmprestimos) == 1) {
            for (i = 0; i < totalEmprestimos; i++) {
                fscanf(arq, "%d;%d;%d;%d;%d;%d;%d;%d\n",
                    &listaEmprestimos[i].idEmprestimo,
                    &listaEmprestimos[i].idmatricula,
                    &listaEmprestimos[i].idLivros,
                    &listaEmprestimos[i].dataEmpprestimo.tm_mday,
                    &listaEmprestimos[i].dataEmpprestimo.tm_mon,
                    &listaEmprestimos[i].dataEmpprestimo.tm_year,
                    &listaEmprestimos[i].dataPrevista,
                    &statusInt);
                listaEmprestimos[i].status = (statusInt == 1);
            }
        }
        fclose(arq);
    }
}
