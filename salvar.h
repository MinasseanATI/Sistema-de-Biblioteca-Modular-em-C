#ifndef SALVAR_H
#define SALVAR_H

// Funções para salvar individualmente cada módulo (para o salvar automático)
void salvarUsuarios();
void salvarLivros();
void salvarEmprestimos();

// Funções gerais de orquestração (chamadas no MainMapa.c)
void salvarTodosOsDados();
void carregarTodosOsDados();
void realizarBackup();

#endif
