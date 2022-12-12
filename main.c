#include <stdio.h>
#include <stdlib.h>
#include "Ciudadado.h"
#include "menus.h"
#include "empresas.h"
#include "noticias.h"
#include "estilo.h"

void subprogramaFIN ();

int main()
{
    Todo todo;
    todo = inicTodo();
    todo = bajarTodo (todo);

    ocultarCursor();
    subProgramaMenuPrincipal(&todo);

    guardarTodo(todo);

    return 0;
}


