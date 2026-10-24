#ifndef LIVROS_H
#define LIVROS_H

#include <stdbool.h>
#include "utils.h"

struct CadastroLivros {
    int idLivro;
    char titulo[100];
    char autor[80];
    char editora[60];
    int anoPublicado;
    int exemplares;
    bool status;
};


extern struct CadastroLivros listaLivros[MAX_LIVROS];
extern int totalLivros;

void cadastrarLivro();
void listarLivros();
void pesquisarLivros();
void editarLivros();


#endif
