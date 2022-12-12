#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include "preguntasFrecuentes.h"
#include "noticias.h"
#include "empresas.h"
#include "residuos.h"
#include "residuosEmpresa.h"
#include "Ciudadado.h"
#include "Transacciones.h"

///Estructura Admin
typedef struct
{
    char usuario[60];
    char password[30];

} Admin;

typedef struct
{
    struct _NodoArbolEmpresa* arbolEmpresa;
    struct _NodoResiduo* listaResiduos;
    struct _NodoPreguntaFrecuente* listaPreguntasFrecuentes;
    struct _NodoNoticia* listaNoticias;
    struct _nodoCiudadano* arbolCiudadanos;
    struct _nodoTransaccion* listaTransacciones;
    struct _NodoResiduosEmpresa* listaResiduosEmpresa;
    Admin administrador;
} Todo;

typedef struct
{
    struct _NodoTransaccion* lista;
}celda;

///Todo
Todo inicTodo ();
Todo bajarTodo (Todo todo);
void guardarTodo (Todo todo);

void subProgramaMenuPrincipal (Todo* todo);
void subprogramaMenuLogin (Todo* todo);
void menuLogin ();

void subprogramaMenuRegistro(Todo* todo);
void menuRegistro();

///empresas
void subprogramaLoginEmpresa(Todo* todo);
void subprogramaMenuEmpresas(Todo*,int);

///preguntas frecuentes
void subprogramaMenuPreguntasFrecuentes (NodoPreguntaFrecuente*);

///noticias
void mostrarSeccionNoticias(NodoNoticia*);

///ciudadanos
void subprogramaLoginCiudadano(Todo* todo);

///transacciones
void mostrarTransaccionesPendientesCiudadano(Todo* todo,int DNI);
nodoTransaccion* modificarTransacccionCiudadano (Todo* todo, int IdTransaccion, int DNI);

///admin
void menuAdmin();
void subprogramaMenuAdmin(Todo*);
void subprogramaLoginAdmin (Todo*);

void cargarADL(celda[]);
void inicADL(celda[]);
void mostrarADLSegunEstado(celda[],int,NodoResiduo*);
void borrarADL(celda[]);

void bajarAdminArchivo(Admin*);
int logInAdmin(Admin);
void crearArchivoAdmin();


#endif // MENUS_H_INCLUDED
