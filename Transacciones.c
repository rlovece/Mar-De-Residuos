#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "estilo.h"
#include "fecha.h"
#include "Transacciones.h"
#include "Ciudadado.h"
#include "residuos.h"
#include "empresas.h"


nodoTransaccion* bajarTransaccionesArchivo(nodoTransaccion* listaTransacciones)
{
    FILE* pArchivo = fopen(ARCHIVO_TRANSACCIONES,"rb");
    Transaccion auxTrans;

    if(pArchivo != NULL)
    {
        while( fread(&auxTrans,sizeof(Transaccion),1,pArchivo) > 0)
        {
            listaTransacciones = agregarAlFinalNodoTransaccion(listaTransacciones,crearNodoTransaccion(auxTrans));
        }

        fclose(pArchivo);
    }
    return listaTransacciones;
}

nodoTransaccion* agregarAlFinalNodoTransaccion(nodoTransaccion* listaTransacciones, nodoTransaccion* nuevoNodo)
{
    if(listaTransacciones == NULL)
    {
        listaTransacciones = nuevoNodo;
    }
    else
    {
        nodoTransaccion* ultimoNodo = buscarUltimoNodoTransaccion(listaTransacciones);

        ultimoNodo->sig = nuevoNodo;
    }

    return listaTransacciones;
}

nodoTransaccion* buscarUltimoNodoTransaccion (nodoTransaccion* listaTransaccciones)
{
    nodoTransaccion* iterador = listaTransaccciones;

    if(iterador != NULL )
    {
        while(iterador->sig != NULL)
        {
            iterador = iterador->sig;
        }
    }
    return iterador;
}

nodoTransaccion* inicListaTransaciones()
{
    return NULL;
}

nodoTransaccion* crearNodoTransaccion(Transaccion nuevaTrans)
{
    nodoTransaccion* nuevoNodo = (nodoTransaccion*) malloc(sizeof(nodoTransaccion));

    nuevoNodo->dato = nuevaTrans;
    nuevoNodo->sig = NULL;

    return nuevoNodo;
}

Transaccion crearUnaTransaccion(int id, int idResiduo, int DNICiudadano, int CUITEmpresa)
{
    Transaccion nuevaTrans;

    nuevaTrans.idTransaccion = id;
    nuevaTrans.idResiduo = idResiduo;
    nuevaTrans.DNI = DNICiudadano;
    nuevaTrans.CUIT = CUITEmpresa;
    mostrarCursor();
    printf ("\nIngrese la cant de material que tiene para entregar: ");
    fflush(stdin);
    scanf("%i", &nuevaTrans.cantidad);
    printf ("\nIngrese la fecha de entrega/retiro: ");
    nuevaTrans.fechaEntrega = cargarFecha();
    printf("\nEn caso de que corresponda ingrese el horario en que se encontrará en su domicilio:  ");
    fflush(stdin);
    gets(nuevaTrans.horariosDeRetiro);
    nuevaTrans.estado = 1;

    ocultarCursor();

    return nuevaTrans;
}

int ultimoIdCargadoTransaccion(nodoTransaccion* listaTransacciones)
{
    int ultimoId=0;
    nodoTransaccion* iterador = buscarUltimoNodoTransaccion(listaTransacciones);
    if(iterador != NULL)
    {
        ultimoId = iterador->dato.idTransaccion;
    }

    return ultimoId;
}



void guardarTransacciones (nodoTransaccion* listaTransacciones)
{
    FILE* pArchivo = fopen(ARCHIVO_TRANSACCIONES, "wb");
    nodoTransaccion* iterador = listaTransacciones;

    if(pArchivo != NULL)
    {
        while(iterador != NULL)
        {
            fwrite( &(iterador->dato),sizeof(Transaccion),1,pArchivo);

            iterador = iterador->sig;
        }

        fclose(pArchivo);
    }
}

nodoTransaccion* buscarTransaccion (nodoTransaccion* listaTrans, int IdTransaccion)
{
    nodoTransaccion* rta= inicListaTransaciones();
    if(listaTrans!=NULL)
    {
        if(IdTransaccion == listaTrans->dato.idTransaccion)
        {
            rta = listaTrans;
        }
        else
        {
            rta = buscarTransaccion(listaTrans->sig, IdTransaccion);
        }
    }
    return rta;
}

nodoTransaccion* borrarListaTransacciones(nodoTransaccion* listaTransacciones)
{
    nodoTransaccion* iterador = listaTransacciones;
    nodoTransaccion* aBorrar;

    while(iterador != NULL)
    {
        aBorrar = iterador;
        iterador = iterador->sig;
        free(aBorrar);
    }

    return iterador;
}

void mostrarUnaTransaccion (Transaccion aMostrar, NodoResiduo* listaResiduos)
{
    Residuo auxResiduo;

    printf ("\n  ID: %i", aMostrar.idTransaccion);
    auxResiduo = buscarResiduoPorId (listaResiduos, aMostrar.idResiduo);
    printf ("\n  Residuo: %s", auxResiduo.nombre);
    printf ("\n  DNI Ciudadano: %i", aMostrar.DNI);
    printf ("\n  CUIT Empresa: %i", aMostrar.CUIT);
    printf ("\n  Cant de Material a Entregar: %i", aMostrar.cantidad);
    printf ("\n  Fecha de entrega/retiro: ");
    mostrarFecha(aMostrar.fechaEntrega);
    printf("\n  Comentarios: %s", aMostrar.horariosDeRetiro);
    if (aMostrar.estado==1)
    {
        printf ("\n  Estado: Pendiente de entrega");
    }
    else if (aMostrar.estado==2)
    {
        printf ("\n  Estado: Entregado");
    }
    else
    {
        printf ("\n  Estado: Cancelado");
    }
    printf("\n  ---------------------------------- \n");
}

//transacciones
/*estados 0 cancelado
1 pendiente
2 entregado*/

void mostrarRetirosRealizados(nodoTransaccion* listaTransacciones,NodoResiduo* listaResiduos,int cuit)
{
    nodoTransaccion* iterador = listaTransacciones;

    while(iterador != NULL)
    {
        if(iterador->dato.CUIT == cuit && iterador->dato.estado == 2)  ///estado = 2 -> entregado
        {
            mostrarUnaTransaccion(iterador->dato,listaResiduos);
        }

        iterador = iterador->sig;
    }
}

void mostrarRetirosPendientes(nodoTransaccion* listaTransacciones,NodoResiduo* listaResiduos,int cuit)
{
    nodoTransaccion* iterador = listaTransacciones;

    while(iterador != NULL)
    {
        if(iterador->dato.CUIT == cuit && iterador->dato.estado == 1)  ///estado = 1 -> pendiente
        {
            mostrarUnaTransaccion(iterador->dato,listaResiduos);
        }
        iterador = iterador->sig;
    }
    system ("pause");
}
nodoTransaccion* marcarRetirosRealizados(nodoTransaccion* listaTransacciones,int cuit)
{
    int idTransaccion;
    nodoTransaccion* iterador = listaTransacciones;

    gotoxy(30,10);
    printf("Ingrese el id de la transaccion ya realizada:");
    gotoxy(30,12);
    mostrarCursor();
    scanf("%i",&idTransaccion);
    ocultarCursor();

    while(iterador != NULL && iterador->dato.idTransaccion != idTransaccion)
    {
        iterador = iterador->sig;
    }

    if(iterador)
    {
        if(iterador->dato.CUIT == cuit)
        {

            if(iterador->dato.estado == 2)
            {
                gotoxy(30,14);
                Color(RED,BLACK);
                printf("La transaccion del id ingresado ya fue realizada");
                Color(BLACK,WHITE);
                getch();
            }
            else
            {
                iterador->dato.estado = 2;
                gotoxy(30,14);
                printf("Operacion exitosa!");
                getch();

            }


        }
        else
        {
            gotoxy(30,14);
            Color(RED,BLACK);
            printf("El id ingresado no pertenece a su empresa");
            Color(BLACK,WHITE);
            getch();
        }
    }
    else
    {
        gotoxy(30,14);
        Color(RED,BLACK);
        printf("El id ingresado no existe");
        Color(BLACK,WHITE);
        getch();
    }

    return listaTransacciones;
}
