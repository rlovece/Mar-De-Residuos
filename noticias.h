#ifndef NOTICIAS_H_INCLUDED
#define NOTICIAS_H_INCLUDED

#include "fecha.h"

typedef struct
{
    int idNoticia;
    fecha fechaNoticia; /// DD/MM/AAAA
    char titulo[60];
    char cuerpo[500];
    int bajaNoticia; ///1 alta 0 baja
}Noticia;

typedef struct _NodoNoticia
{
    Noticia dato;
    struct _NodoNoticia* siguiente;
}NodoNoticia;


///Prototipado Funciones Noticias

NodoNoticia* bajarNoticiasArchivo(NodoNoticia*);
NodoNoticia* agregarAlFinalNodoNoticia(NodoNoticia*,NodoNoticia*);
NodoNoticia* buscarUltimoNodoNoticia(NodoNoticia*);
NodoNoticia* inicListaNoticias();
NodoNoticia* crearNodoNoticia(Noticia);
Noticia crearUnaNoticia(int);
int ultimoIdCargadoNoticia(NodoNoticia*);
void mostrarUnaNoticia(Noticia,int);
void mostrarNoticias(NodoNoticia*,int); ///int para mostrar o no el id de la noticia
void guardarNoticias(NodoNoticia*);
NodoNoticia* modificarDatosNoticia(NodoNoticia*,int); ///modifica segun el id
void menuModificarDatosNoticia();
NodoNoticia* darDeBajaNoticia(NodoNoticia*,int);
NodoNoticia* validarNoticia(NodoNoticia*,int);

void mostrarSeccionNoticias(NodoNoticia*);

#endif // NOTICIAS_H_INCLUDED
