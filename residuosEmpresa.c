#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "residuos.h"
//#include "empresas.h"
#include "residuosEmpresa.h"
#include "Ciudadado.h"
#include "estilo.h"

#define ARCHIVO_RESIDUOS_EMPRESAS "ResiduosEmpresa.bin"

///Implementacion Funciones ResiduosEmpresa

NodoResiduosEmpresa* bajarResiduosEmpresaArchivo(NodoResiduosEmpresa* listaResiduosEmpresa)
{
    FILE* pArchivo = fopen(ARCHIVO_RESIDUOS_EMPRESAS,"rb");
    ResiduosEmpresa residuoEmpresa;

    if(pArchivo != NULL)
    {
        while( fread(&residuoEmpresa,sizeof(ResiduosEmpresa),1,pArchivo) > 0)
        {
            listaResiduosEmpresa = agregarAlFinalNodoResiduoEmpresa(listaResiduosEmpresa,crearNodoResiduosEmpresa(residuoEmpresa));
        }

        fclose(pArchivo);

    }
    else
    {
        printf("\nNo se pudo abrir el archivo ResiduosEmpresa\n");
    }

    return listaResiduosEmpresa;

}

NodoResiduosEmpresa* agregarAlFinalNodoResiduoEmpresa(NodoResiduosEmpresa* listaResiduosEmpresa,NodoResiduosEmpresa* nuevoNodo)
{
    if(listaResiduosEmpresa == NULL)
    {
        listaResiduosEmpresa = nuevoNodo;
    }
    else
    {
        NodoResiduosEmpresa* ultimoNodo = buscarUltimoNodoResiduoEmpresa(listaResiduosEmpresa);

        ultimoNodo->siguiente = nuevoNodo;
    }

    return listaResiduosEmpresa;
}

NodoResiduosEmpresa* buscarUltimoNodoResiduoEmpresa(NodoResiduosEmpresa* listaResiduosEmpresa)
{
    NodoResiduosEmpresa* iterador = listaResiduosEmpresa;

    if(iterador != NULL)
    {
        while(iterador->siguiente != NULL)
        {
            iterador = iterador->siguiente;
        }
    }

    return iterador;
}

NodoResiduosEmpresa* inicListaResiduosEmpresa()
{
    return NULL;
}

NodoResiduosEmpresa* crearNodoResiduosEmpresa(ResiduosEmpresa residuoEmpresa)
{
    NodoResiduosEmpresa* nuevoNodo = malloc(sizeof(NodoResiduosEmpresa));

    nuevoNodo->dato = residuoEmpresa;
    nuevoNodo->siguiente = NULL;

    return nuevoNodo;
}

ResiduosEmpresa crearUnResiduoEmpresa(int idResi, int cuit)
{
    ResiduosEmpresa residuoEmpresa;

    residuoEmpresa.idResiduo = idResi;
    residuoEmpresa.CUIT = cuit;
    residuoEmpresa.bajaResiduoEmpresa = 1;

    return residuoEmpresa;
}


NodoResiduosEmpresa* subprogramaCrearUnResiduoEmpresa(NodoResiduosEmpresa* listaResiduosEmpresa, NodoResiduo* listaResiduos, int cuit)
{
    char nombreResiduo[30];
    int idResi;
    ResiduosEmpresa residuoEmpresa;

    gotoxy(15,10); printf("Ingrese el residuo que acepta:  ");
    gotoxy(15,12);mostrarCursor();
    fflush(stdin);
    gets(nombreResiduo);
    ocultarCursor();

    idResi = buscarIdResiduo(listaResiduos,nombreResiduo);

    if(idResi != 0)
    {
        residuoEmpresa = crearUnResiduoEmpresa(idResi,cuit);
        listaResiduosEmpresa = agregarAlFinalNodoResiduoEmpresa(listaResiduosEmpresa,crearNodoResiduosEmpresa(residuoEmpresa));
    }
    else
    {
        Color (RED, BLACK);
        printf("\n\t\tEl residuo ingresado no existe o se ingreso incorrectamente.\n\t\tVuelva a intentar o ingrese el nuevo residuo en el sistema\n");
        Color (BLACK, WHITE);
        gotoxy(5,18); printf("| ID    ");
            gotoxy(13, 18); printf("| NOMBRE");
            gotoxy(32, 18); printf("|\n");
            gotoxy(5,19); printf("-----------------------------");
        mostrarResiduosACiudadano (listaResiduos, 20);
    }

    printf ("\n\n");
    system ("pause");
    return listaResiduosEmpresa;

}


void mostrarResiduosEmpresa(NodoResiduosEmpresa* listaResiduosEmpresa,NodoResiduo* listaResiduos,int cuit)
{
    NodoResiduosEmpresa* iterador = listaResiduosEmpresa;
    Residuo residuo;

    while(iterador != NULL)
    {
        if(iterador->dato.bajaResiduoEmpresa == 1 && iterador->dato.CUIT == cuit) ///verifico que residuoEmpresa no este dado de baja
        {
            residuo = buscarResiduoPorId(listaResiduos,iterador->dato.idResiduo);

            if(residuo.id != 0 && residuo.bajaResiduo == 1) ///verifico que el residuo no este dado de baja
            {
                mostrarUnResiduo(residuo,0);

                gotoxy(30,20); printf("%c Siguiente",16);getch();
                system("cls");
            }
        }




        iterador = iterador->siguiente;
    }
}

void guardarResiduosEmpresa(NodoResiduosEmpresa* listaResiduosEmpresa)
{
    FILE* pArchivo = fopen(ARCHIVO_RESIDUOS_EMPRESAS,"wb");
    NodoResiduosEmpresa* iterador = listaResiduosEmpresa;

    if(pArchivo != NULL)
    {
        while(iterador != NULL)
        {
            fwrite(&(iterador->dato),sizeof(ResiduosEmpresa),1,pArchivo);

            iterador = iterador->siguiente;
        }

        fclose(pArchivo);
    }
    else
    {
        printf("\nNo se pudo abrir el archivo ResiduosEmpresa en modo escritura\n");
    }
}

NodoResiduosEmpresa* subprogramaDarDeBajaResiduoEmpresa(NodoResiduosEmpresa* listaResiduosEmpresa,NodoResiduo* listaResiduos,int cuit)
{
    char nombre[30];
    int idResi;

    gotoxy(30,10);printf("Ingrese el nombre del residuo que desea eliminar:  ");
    gotoxy(30,12); mostrarCursor();
    fflush(stdin);
    gets(nombre);
    ocultarCursor();

    idResi = buscarIdResiduo(listaResiduos,nombre);

    if(idResi != 0)
    {
        listaResiduosEmpresa = darDeBajaResiduoEmpresa(listaResiduosEmpresa,idResi,cuit);
    }

    return listaResiduosEmpresa;
}

NodoResiduosEmpresa* darDeBajaResiduoEmpresa(NodoResiduosEmpresa* listaResiduosEmpresa,int idResi, int cuit)
{
    NodoResiduosEmpresa* iterador = listaResiduosEmpresa;

    if(iterador != NULL)
    {

        while(iterador != NULL)
        {
            if(iterador->dato.idResiduo == idResi && iterador->dato.CUIT == cuit)
            {
                iterador->dato.bajaResiduoEmpresa = 0;
                gotoxy(30,10);printf("Baja exitosa!");
                gotoxy(30,27); system("pause");
            }

            iterador = iterador->siguiente;
        }


    }

    return listaResiduosEmpresa;
}
