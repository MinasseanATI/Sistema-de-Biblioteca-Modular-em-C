#include <stdio.h>
#include "utils.h"
// Funcao de limpeza de Buffer
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
