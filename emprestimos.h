#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H
#define PRAZO_DEVOLUCAO_DIAS 7

#include <stdbool.h>
#include <time.h>
#include "utils.h"

struct SistemaEmprestimo {
    int idEmprestimo;
    int idmatricula;
    int idLivros;
    struct tm dataEmpprestimo;
    int dataPrevista;
    bool status;
};

extern struct SistemaEmprestimo listaEmprestimos[MAX_EMPRESTIMOS];
extern int totalEmprestimos;

void cadastrarEmprestimos();
void listarEmprestimos();
void devolverLivros();
void renovarEmprestimos();

#endif
