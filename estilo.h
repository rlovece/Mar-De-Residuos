#ifndef ESTILO_H_INCLUDED
#define ESTILO_H_INCLUDED

void gotoxy (int x, int y);
void Color(int Background, int Text);
void ocultarCursor();
void mostrarCursor();
void cabecera();


enum Colors { // Listado de colores (La letra "L" al inicio, indica que es un color más claro que su antecesor).
 BLACK = 0,
 BLUE = 1,
 GREEN = 2,
 CYAN = 3,
 RED = 4,
 MAGENTA = 5,
 BROWN = 6,
 LGREY = 7,
 DGREY = 8,
 LBLUE = 9,
 LGREEN = 10,
 LCYAN = 11,
 LRED = 12,
 LMAGENTA = 13,
 YELLOW = 14,
 WHITE = 15
};

#endif // ESTILO_H_INCLUDED
