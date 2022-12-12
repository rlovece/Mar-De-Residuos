#ifndef RESIDUOS_H_INCLUDED
#define RESIDUOS_H_INCLUDED

///Estructura Residuo

typedef struct
{
    int id;
    char nombre[50];
    char comentarios[500];
    int bajaResiduo;  ///1 alta, 0 baja
}Residuo;

typedef struct _NodoResiduo
{
    Residuo	dato;
    struct _NodoResiduo* anterior;
    struct _NodoResiduo* siguiente;
}NodoResiduo;

///Prototipado Funciones Residuo
NodoResiduo* bajarResiduosArchivo(NodoResiduo*);
NodoResiduo* inicListaResiduos();
NodoResiduo* crearNodoResiduo(Residuo);
Residuo crearUnResiduo(char[],int); ///recibe el nombre y el Id
NodoResiduo* cargarUnResiduo(NodoResiduo*);
NodoResiduo* agregarAlFinalNodoResiduo(NodoResiduo*,NodoResiduo*);
NodoResiduo* buscarUltimoNodoResiduo(NodoResiduo*);
void mostrarUnResiduo(Residuo,int);
void mostrarResiduos(NodoResiduo*,int);
void guardarResiduos(NodoResiduo*);
//void guardarArbolEmpresa(NodoArbolEmpresa*,FILE*); ///guardo preOrder
NodoResiduo* validarResiduo(NodoResiduo*,char[]);
int ultimoIdCargado(NodoResiduo*);
NodoResiduo* modificarDatosResiduo(NodoResiduo*);
void menuModificarDatosResiduo();
Residuo buscarResiduoPorId(NodoResiduo*,int);
int buscarIdResiduo(NodoResiduo*,char[]);
NodoResiduo* darDeBajaResiduo(NodoResiduo*);
void menuResiduos();

void mostrarUnResiduoACiudadano (Residuo residuo, int yResiduo);
void mostrarResiduosACiudadano (NodoResiduo* iterador, int yResiduo);

#endif // RESIDUOS_H_INCLUDED
