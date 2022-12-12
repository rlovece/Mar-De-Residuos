#ifndef CIUDADADO_H_INCLUDED
#define CIUDADADO_H_INCLUDED

#define ARCHIVO_CIUDADANOS "Ciudadanos.bin"
#include "fecha.h"

typedef struct
{
    int DNICiudadano;
    char nombreYApellido[30];
    char password[10];
    char telefono[10];
    int bajaCiudadano;
    char email[40];
    char direccion[40];
    fecha fechaNacimiento;
} Ciudadano;

typedef struct _nodoCiudadano
{
    Ciudadano dato;
    struct _nodoCiudadano* izq;
    struct _nodoCiudadano* der;
} nodoCiudadano;


Ciudadano cargarUnCiudadano (int DNI);
void mostrarCiudadano(Ciudadano aMostrar);
void unCiudadanoAlArchivo (FILE* archi, Ciudadano nuevo);
nodoCiudadano* inicArbolCiudadanos ();
nodoCiudadano* crearNodoCiudadano (Ciudadano dato);
nodoCiudadano * insertar (nodoCiudadano* arbol, Ciudadano dato);
nodoCiudadano* buscarCiudadano (nodoCiudadano* arbol, int DNI);
int validarCiudadano (nodoCiudadano* arbol, int DNI);
nodoCiudadano* bajarCiudadanosArchivo (nodoCiudadano* arbolCiudadanos);
void guardarCiudadanos (nodoCiudadano* arbolCiudano);
void guardarArbolCiudadano (nodoCiudadano* arbolCiudadano,FILE* pArchivo);
int loginCiudadano (nodoCiudadano* arbolCiudadanos, int DNI);
int passwordCiudadanoCorrecta(nodoCiudadano* nodoBuscado, char pass[]);
void mostrarCiudadanos (nodoCiudadano* arbolCiudadanos);
void menuModificarCiudadano ();
nodoCiudadano* darDeBajaCiudadano (nodoCiudadano* arbolCiudadanos, int DNI);
nodoCiudadano* darDeAltaCiudadano (nodoCiudadano* arbolCiudadanos, int DNI);
Ciudadano modificarCiudadano (Ciudadano aModificar);
void menuCiudadano ();
#endif // CIUDADADO_H_INCLUDED
