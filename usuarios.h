#ifndef USUARIOS_H
#define USUARIOS_H

#include <time.h>
#include "utils.h"

struct CadastroUsuarios {
    int idmatricula;
    char nome[100];
    char curso[50];
    char telefone[15];
    struct tm dataCadastro;
};

extern struct CadastroUsuarios listaUsuarios[MAX_USUARIOS];
extern int totalUsuarios;

void cadastrarUsuario();
void listarUsuarios();
void pesquisarUsuarios();
void editarUsuarios();

#endif
