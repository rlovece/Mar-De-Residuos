#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "estilo.h"
#include "residuos.h"
#include "estilo.h"
#include "menus.h"

#define ARCHIVO_RESIDUOS "Residuos.bin"

#define N 100
#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

///Implementacion Funciones nodoResiduos

NodoResiduo* bajarResiduosArchivo(NodoResiduo* listaResiduos)
{
    FILE* pArchivo = fopen(ARCHIVO_RESIDUOS,"rb");
    Residuo residuo;

    if(pArchivo != NULL)
    {
        while(fread(&residuo,sizeof(Residuo),1,pArchivo) > 0)
        {
            listaResiduos = agregarAlFinalNodoResiduo(listaResiduos,crearNodoResiduo(residuo));
        }

        fclose(pArchivo);
    }
    else
    {
        printf("\nNo se pudo abrir el archivo Residuos\n");
    }

    return listaResiduos;
}
NodoResiduo* inicListaResiduos()
{
    return NULL;
}
NodoResiduo* crearNodoResiduo(Residuo residuo)
{
    NodoResiduo* nuevoNodo = malloc(sizeof(NodoResiduo));

    nuevoNodo->dato = residuo;
    nuevoNodo->anterior = NULL;
    nuevoNodo->siguiente = NULL;

    return nuevoNodo;
}
Residuo crearUnResiduo(char nombreResiduo[],int nuevoId) ///recibe el id
{
    Residuo residuo;
    char opcion;

    residuo.id = nuevoId;

    strcpy(residuo.nombre,nombreResiduo);

    mostrarCursor();

    printf("Desea ingresar comentarios? s/n ");
    fflush(stdin);
    scanf("%c",&opcion);

    if(opcion == 's' || opcion == 'S')
    {
        printf("\n[Maximo 500 caracteres]\n");
        fflush(stdin);
        gets(residuo.comentarios);
    }
    else
    {
        strcpy(residuo.comentarios,"-");
    }

    residuo.bajaResiduo = 1;  ///1 alta, 0 baja

    ocultarCursor();

    return residuo;
}
NodoResiduo* cargarUnResiduo(NodoResiduo* listaResiduos)
{
    char nombreResiduo[40];

    mostrarCursor();
    gotoxy (5,3);
    printf("Ingrese el nombre del residuo:  ");
    fflush(stdin);
    gets(nombreResiduo);
    ocultarCursor();

    NodoResiduo* nodoBuscado = validarResiduo(listaResiduos,nombreResiduo);

    if(nodoBuscado == NULL)
    {
        int nuevoId = ultimoIdCargado(listaResiduos) + 1;

        listaResiduos = agregarAlFinalNodoResiduo(listaResiduos,crearNodoResiduo(crearUnResiduo(nombreResiduo,nuevoId)));
    }
    else
    {
        gotoxy (5,6);
        Color (RED, BLACK);
        printf("El nombre ingresado ya existe:\n");
        Color (BLACK, WHITE);
        mostrarUnResiduo(nodoBuscado->dato,8);
    }

    return listaResiduos;
}

NodoResiduo* agregarAlFinalNodoResiduo(NodoResiduo* listaResiduos,NodoResiduo* nuevoNodo)
{
    if(listaResiduos == NULL)
    {
        listaResiduos = nuevoNodo;
    }
    else
    {
        NodoResiduo* ultimoNodo = buscarUltimoNodoResiduo(listaResiduos);

        ultimoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimoNodo;
    }

    return listaResiduos;
}

NodoResiduo* buscarUltimoNodoResiduo(NodoResiduo* listaResiduos)
{
    NodoResiduo* iterador = listaResiduos;

    if(iterador != NULL)
    {
        while(iterador->siguiente != NULL)
        {
            iterador = iterador->siguiente;

        }
    }

    return iterador;
}
void mostrarUnResiduo(Residuo residuo,int mostrarId)
{
    if(residuo.bajaResiduo == 1)
    {
        int y=10;

        if(mostrarId)
        {
            gotoxy(30,y);printf("Id: %i",residuo.id);
        }
        gotoxy(40,y);Color(CYAN,BLACK);
        printf("%s",residuo.nombre);Color(BLACK,WHITE);
        if(residuo.comentarios[0] != '-')
        {
            gotoxy(55,y);
            printf("%c %s",26,residuo.comentarios);
        }
    }
}

void mostrarUnResiduoACiudadano (Residuo residuo, int yResiduo)
{
    if(residuo.bajaResiduo == 1)
    {
        gotoxy(5,yResiduo);
        printf("| %i    ",residuo.id);
        gotoxy(13, yResiduo);
        printf("| %s",residuo.nombre);
        gotoxy(32, yResiduo);
        printf("|\n");

    }
}
void mostrarResiduosACiudadano (NodoResiduo* iterador, int yResiduo)
{
    if(iterador != NULL)
    {
        mostrarUnResiduoACiudadano (iterador->dato, yResiduo);
        yResiduo++;
        mostrarResiduosACiudadano(iterador->siguiente, yResiduo);
    }
}

void mostrarResiduos(NodoResiduo* iterador,int mostrarId)
{
    if(iterador != NULL)
    {
        if(iterador->dato.bajaResiduo)
        {
            system("cls");
            mostrarUnResiduo(iterador->dato,mostrarId);
        }

        gotoxy(30,20);printf("%c Siguiente",16);getch();
        mostrarResiduos(iterador->siguiente,mostrarId);



    }
}
void guardarResiduos(NodoResiduo* listaResiduos)
{
    FILE* pArchivo = fopen(ARCHIVO_RESIDUOS,"wb");
    NodoResiduo* iterador = listaResiduos;

    if(pArchivo != NULL)
    {
        while(iterador != NULL)
        {
            fwrite(&(iterador->dato),sizeof(Residuo),1,pArchivo);

            iterador = iterador->siguiente;
        }

        fclose(pArchivo);
    }
    else
    {
        printf("\nNo se pudo abrir el archivo Residuos para escritura\n");
    }
}


int ultimoIdCargado(NodoResiduo* listaResiduos)
{
    NodoResiduo* iterador = listaResiduos;
    int ultimoId=0;

    if(iterador != NULL)
    {
        while(iterador->siguiente != NULL)
        {
            iterador = iterador->siguiente;
        }
        ultimoId = iterador->dato.id;
    }

    return ultimoId;
}

NodoResiduo* validarResiduo(NodoResiduo* listaResiduos,char nombreResiduo[])
{
    NodoResiduo* iterador = listaResiduos;

    while( iterador != NULL && (strcmpi(iterador->dato.nombre,nombreResiduo) != 0) )
    {
        iterador = iterador->siguiente;
    }

    return iterador; ///me devuelve el puntero al nodo con el dato o
    /// NULL si no encontro el dato
}

NodoResiduo* modificarDatosResiduo(NodoResiduo* listaResiduos)
{
    char nombreResiduo[50];
    NodoResiduo* nodoBuscado;

    system("cls");

    char icono;
    int x, y, teclaMov, ingresoSubmenu,salir;
    x = 30;
    y = 13;
    ingresoSubmenu = 1;
    salir=0;
    icono = 16;

    gotoxy(0,0);

    gotoxy(30,10);
    printf("Ingrese el ombre del residuo que desea modificar: ");
    gotoxy(30,12);
    mostrarCursor();
    fflush(stdin);
    gets(nombreResiduo);
    ocultarCursor();

    nodoBuscado = validarResiduo(listaResiduos,nombreResiduo);

    if(nodoBuscado != NULL)
    {
        ///codigo para seleccionar conflechas y pulsar enter

        do
        {
            ocultarCursor();
            system("cls");
//            mostrarUnResiduo(nodoBuscado->dato,4);

            menuModificarDatosResiduo();



            gotoxy(30, 13);
            printf("%c", icono);

            ingresoSubmenu = 1;
            salir = 0;
            do
            {
                teclaMov = getch();

                if (teclaMov == UP && y>13)
                {

                    gotoxy(x, y);
                    printf(" ");
                    y--;
                    gotoxy(x, y);
                    printf("%c", icono);
                    ingresoSubmenu--;

                }

                else if (teclaMov == DOWN && y<14)
                {
                    gotoxy(x, y);
                    printf(" ");
                    y++;
                    gotoxy(x, y);
                    printf("%c", icono);
                    ingresoSubmenu++;
                }

                ///codigo para que al pulñsar eenterse limpie la pantalla y salga sólo
                //la opcion elegida
                if (teclaMov == ENTER)
                {
                    system("cls");

                    switch (ingresoSubmenu)
                    {
                    case 1:

                        gotoxy(30,10);
                        printf("Ingrese el nuevo nombre: ");
                        gotoxy(30,12);
                        mostrarCursor();
                        fflush(stdin);
                        gets(nodoBuscado->dato.nombre);

                        salir = 1;
                        x = 30;
                        y = 13;
                        system("cls");
                        break;

                    case 2:

                        gotoxy(30,10);
                        printf("Ingrese los nuevos comentarios: ");
                        gotoxy(30,12);
                        mostrarCursor();
                        fflush(stdin);
                        gets(nodoBuscado->dato.comentarios);

                        salir = 1;
                        x = 30;
                        y = 13;
                        system("cls");

                        break;
                    }
                }
            }
            while(teclaMov !=ESC && salir != 1);
        } //codigo para salir
        while (teclaMov !=ESC);


    }
    else
    {
        system("cls");
        Color(RED,BLACK);
        gotoxy(30,10);printf("El residuo ingresado no se encuentra en la lista");
        Color(BLACK,WHITE);
        gotoxy(30,27);system("pause");
    }

    return listaResiduos;
}

void menuModificarDatosResiduo()
{
    int x=30,y=10;

    gotoxy(x,y);
    printf("--------------------------------------------------");
    y++;
    gotoxy(x,y);
    printf("             %cDesea modificar algun dato? ",168);
    y++;
    gotoxy(x,y);
    printf("--------------------------------------------------");
    y++;
    gotoxy(x,y);
    printf("\t     Nombre");
    y++;
    gotoxy(x,y);
    printf("\t     Comentarios");
    y++;
    gotoxy(x,y);
    printf("--------------------------------------------------");
    y+=2;
    gotoxy(x,y);
    printf("\tPara salir presione la tecla Esc\n\n");
}

Residuo buscarResiduoPorId(NodoResiduo* listaResiduos,int id)
{
    Residuo residuoBuscado;
    NodoResiduo* iterador = listaResiduos;

    residuoBuscado.id = 0;

    while(iterador != NULL && iterador->dato.id != id)
    {
        iterador = iterador->siguiente;
    }

    if(iterador!=NULL)
    {
        residuoBuscado = iterador->dato;
    }

    return residuoBuscado;
}

int buscarIdResiduo(NodoResiduo* listaResiduos,char nombre[])
{
    NodoResiduo* iterador = listaResiduos;
    int id=0;

    while(iterador != NULL && strcmpi(iterador->dato.nombre,nombre) != 0)
    {
        iterador = iterador->siguiente;
    }

    if(iterador != NULL)
    {
        id = iterador->dato.id;
    }

    return id;
}

NodoResiduo* darDeBajaResiduo(NodoResiduo* listaResiduos)
{
    char nombre[30];
    NodoResiduo* nodoBuscadoResiduo;

    gotoxy(30,10);printf("Ingrese el nombre del residuo:  ");
    gotoxy(30,12); mostrarCursor();
    fflush(stdin);
    gets(nombre);

    ocultarCursor();

    nodoBuscadoResiduo = validarResiduo(listaResiduos,nombre);

    if(nodoBuscadoResiduo != NULL)
    {
        nodoBuscadoResiduo->dato.bajaResiduo = 0; ///lo doy de baja
        gotoxy(30,10);printf("Baja exitosa!");
        gotoxy(30,27);system("pause");
    }
    else
    {
        system("cls");
        Color(RED,BLACK);
        gotoxy(30,10);printf("El residuo ingresado no se encuentra en la lista");
        Color(BLACK,WHITE);
        gotoxy(30,27);system("pause");
    }

    return listaResiduos;
}

void menuResiduos()
{
    gotoxy(30,4);
    printf("--------------------------------------------------");
    gotoxy(30,5);
    printf("             GRACIAS POR SER PARTE ");
    gotoxy(30,6);
    printf("--------------------------------------------------");
    gotoxy(30,7);
    printf("\t     Ver residuos");
    gotoxy(30,8);
    printf("\t     Agregar residuo");
    gotoxy(30,9);
    printf("\t     Modificar residuo");
    gotoxy(30,10);
    printf("\t     Dar de baja residuo");
    gotoxy(30,11);
    printf("--------------------------------------------------\n");
    gotoxy(30,14);
    printf("\tPara salir presione la tecla Esc\n\n");

}
