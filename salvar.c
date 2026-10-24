#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "salvar.h"
#include "usuarios.h"
#include "livros.h"
#include "emprestimos.h"

void salvarUsuarios() {
    FILE *arq = fopen("usuarios.txt", "w");
    if (arq == NULL) {
        printf("\n[ERRO] Nao foi possivel abrir 'usuarios.txt' para escrita.\n");
        return;
    }

    int i;
    
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


void salvarLivros() {
    FILE *arq = fopen("livros.txt", "w");
    if (arq == NULL) {
        printf("\n[ERRO] Nao foi possivel abrir 'livros.txt' para escrita.\n");
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

void salvarEmprestimos() {
    FILE *arq = fopen("emprestimos.txt", "w");
    if (arq == NULL) {
        printf("\n[ERRO] Nao foi possivel abrir 'emprestimos.txt' para escrita.\n");
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


void realizarBackup() {
    int ch; 
    FILE *origem, *destino;

    origem = fopen("usuarios.txt", "r");
    if (origem != NULL) {
        destino = fopen("usuarios_backup.bak", "w");
        if (destino != NULL) {
            while ((ch = fgetc(origem)) != EOF) {
                fputc(ch, destino);
            }
            fclose(destino);
        }
        fclose(origem);
    }

    origem = fopen("livros.txt", "r");
    if (origem != NULL) {
        destino = fopen("livros_backup.bak", "w");
        if (destino != NULL) {
            while ((ch = fgetc(origem)) != EOF) {
                fputc(ch, destino);
            }
            fclose(destino);
        }
        fclose(origem);
    }

    origem = fopen("emprestimos.txt", "r");
    if (origem != NULL) {
        destino = fopen("emprestimos_backup.bak", "w");
        if (destino != NULL) {
            while ((ch = fgetc(origem)) != EOF) {
                fputc(ch, destino);
            }
            fclose(destino);
        }
        fclose(origem);
    }
}

void carregarTodosOsDados() {
    FILE *arq;
    int i, statusInt;
    char linha[300]; 
    
// Carrega os usuarios
    arq = fopen("usuarios.txt", "r");
    if (arq != NULL) {
        if (fgets(linha, sizeof(linha), arq) != NULL) {
            sscanf(linha, "%d", &totalUsuarios);
            for (i = 0; i < totalUsuarios; i++) {
                if (fgets(linha, sizeof(linha), arq) != NULL) {
                    linha[strcspn(linha, "\n")] = 0;
                    
                    sscanf(linha, "%d;%99[^;];%49[^;];%14[^;];%d;%d;%d",
                        &listaUsuarios[i].idmatricula,
                        listaUsuarios[i].nome,
                        listaUsuarios[i].curso,
                        listaUsuarios[i].telefone,
                        &listaUsuarios[i].dataCadastro.tm_mday,
                        &listaUsuarios[i].dataCadastro.tm_mon,
                        &listaUsuarios[i].dataCadastro.tm_year);
                }
            }
        }
        fclose(arq);
    }
    
// Carrega os livros
    arq = fopen("livros.txt", "r");
    if (arq != NULL) {
        if (fgets(linha, sizeof(linha), arq) != NULL) {
            sscanf(linha, "%d", &totalLivros);
            for (i = 0; i < totalLivros; i++) {
                if (fgets(linha, sizeof(linha), arq) != NULL) {
                    linha[strcspn(linha, "\n")] = 0;

                    sscanf(linha, "%99[^;];%99[^;];%49[^;];%d;%d;%d",
                        listaLivros[i].titulo,
                        listaLivros[i].autor,
                        listaLivros[i].editora,
                        &listaLivros[i].anoPublicado,
                        &listaLivros[i].exemplares,
                        &statusInt);
                    listaLivros[i].status = (statusInt == 1);
                }
            }
        }
        fclose(arq);
    }
    
// Carrega os emprestimos
    arq = fopen("emprestimos.txt", "r");
    if (arq != NULL) {
        if (fgets(linha, sizeof(linha), arq) != NULL) {
            sscanf(linha, "%d", &totalEmprestimos);
            for (i = 0; i < totalEmprestimos; i++) {
                if (fgets(linha, sizeof(linha), arq) != NULL) {
                    linha[strcspn(linha, "\n")] = 0;

                    sscanf(linha, "%d;%d;%d;%d;%d;%d;%d;%d",
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
        }
        fclose(arq);
    }
}
