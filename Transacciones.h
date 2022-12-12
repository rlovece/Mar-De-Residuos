#ifndef TRANSACCIONES_H_INCLUDED
#define TRANSACCIONES_H_INCLUDED
#include "fecha.h"
#include "residuos.h"
#define ARCHIVO_TRANSACCIONES "Transacciones.bin"

typedef struct
{
    int	idTransaccion;
    int	CUIT;
    int	DNI;
    int	idResiduo;
    int	cantidad;
    char horariosDeRetiro[50];
    fecha fechaEntrega;
    int	estado;
} Transaccion;

typedef struct _NodoTransaccion
{
    Transaccion dato;
    struct NodoTransaccion* sig;
} nodoTransaccion;

nodoTransaccion* bajarTransaccionesArchivo(nodoTransaccion* listaTransacciones);
nodoTransaccion* agregarAlFinalNodoTransaccion(nodoTransaccion* listaTransacciones, nodoTransaccion* nuevoNodo);
nodoTransaccion* buscarUltimoNodoTransaccion (nodoTransaccion* listaTransaccciones);
nodoTransaccion* inicListaTransaciones();
nodoTransaccion* crearNodoTransaccion(Transaccion nuevaTrans);
Transaccion crearUnaTransaccion(int id, int idResiduo, int DNICiudadano, int CUITEmpresa);
int ultimoIdCargadoTransaccion(nodoTransaccion* listaTransacciones);
void guardarTransacciones (nodoTransaccion* listaTransacciones);
nodoTransaccion* buscarTransaccion (nodoTransaccion* listaTrans, int IdTransaccion);
nodoTransaccion* borrarListaTransacciones(nodoTransaccion*);
void mostrarUnaTransaccion (Transaccion aMostrar, NodoResiduo*);

void mostrarRetirosRealizados(nodoTransaccion*,NodoResiduo*,int);
void mostrarRetirosPendientes(nodoTransaccion*,NodoResiduo*,int);
nodoTransaccion* marcarRetirosRealizados(nodoTransaccion*,int);
#endif // TRANSACCIONES_H_INCLUDED
