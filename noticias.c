#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "estilo.h"
#include "noticias.h"
#include "fecha.h"
#include "menus.h"

#define ARCHIVO_NOTICIAS "Noticias.bin"

#define N 100
#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

NodoNoticia* bajarNoticiasArchivo(NodoNoticia* listaNoticias)
{
    FILE* pArchivo = fopen(ARCHIVO_NOTICIAS,"rb");
    Noticia noticia;

    if(pArchivo != NULL)
    {
        while( fread(&noticia,sizeof(Noticia),1,pArchivo) > 0)
        {
            listaNoticias = agregarAlFinalNodoNoticia(listaNoticias,crearNodoNoticia(noticia));
        }

        fclose(pArchivo);
    }
    else
    {
        printf("\nNo se pudo abrir el archivo Noticias\n");
    }

    return listaNoticias;

}
NodoNoticia* agregarAlFinalNodoNoticia(NodoNoticia* listaNoticias,NodoNoticia* nuevoNodo)
{
    if(listaNoticias == NULL)
    {
        listaNoticias = nuevoNodo;
    }
    else
    {
        NodoNoticia* ultimoNodo = buscarUltimoNodoNoticia(listaNoticias);

        ultimoNodo->siguiente = nuevoNodo;
    }

    return listaNoticias;
}

NodoNoticia* buscarUltimoNodoNoticia(NodoNoticia* listaNoticias)
{
    NodoNoticia* iterador = listaNoticias;

    if(iterador != NULL )
    {
        while(iterador->siguiente != NULL)
        {
            iterador = iterador->siguiente;
        }
    }

    return iterador;
}

NodoNoticia* inicListaNoticias()
{
    return NULL;
}

NodoNoticia* crearNodoNoticia(Noticia noticia)
{
    NodoNoticia* nuevoNodo = malloc(sizeof(NodoNoticia));

    nuevoNodo->dato = noticia;
    nuevoNodo->siguiente = NULL;

    return nuevoNodo;
}

Noticia crearUnaNoticia(int id)
{
    Noticia noticia;

    noticia.idNoticia = id;

    mostrarCursor();
    noticia.fechaNoticia = cargarFecha();

    printf("\nIngrese el titulo:  ");
    fflush(stdin);
    gets(noticia.titulo);

    printf("\nIngrese la noticia: ");
    fflush(stdin);
    gets(noticia.cuerpo);

    noticia.bajaNoticia = 1;

    ocultarCursor();

    return noticia;
}

int ultimoIdCargadoNoticia(NodoNoticia* listaNoticias)
{
    int ultimoId=0;
    NodoNoticia* iterador = buscarUltimoNodoNoticia(listaNoticias);

    if(iterador != NULL)
    {
        ultimoId = iterador->dato.idNoticia;
    }

    return ultimoId;
}

void mostrarUnaNoticia(Noticia noticia,int mostrarId)
{
    int i=0,y=8,x0=70,validosTitulo,validosCuerpo;

    validosTitulo = strlen(noticia.titulo);
    validosCuerpo = strlen(noticia.cuerpo);

    if(noticia.bajaNoticia)
    {

        if(mostrarId)
        {
            gotoxy(x0,y-2);
            printf("Id: %i",noticia.idNoticia);
        }

        ///titulo


        for(int j=30 ; j <= 60 ; j+=30) ///muestro 2 renglones de 30 caracteres
        {
            gotoxy(x0+7,y);
            while(i<j && i<validosTitulo)
            {
                Color(CYAN,BLACK);
                printf("%c",noticia.titulo[i]);
                i++;
            }

            while(i<j)
            {
                Color(BLACK,WHITE);
                printf(" ");
                i++;
            }

            y++;
        }

        ///fecha

        y++;

        Color(BLACK,WHITE);
        gotoxy(x0+16,y); //Color(BLUE,BLACK);
        mostrarFecha(noticia.fechaNoticia);

        ///cuerpo
        i=0;
        y+=2;

        for(int j=45 ; j <=225 ; j+=45) ///muestro 5 renglones de 30 caracteres
        {
            gotoxy(x0,y);
            while(i<j && i < validosCuerpo)
            {
                //Color(BLUE,BLACK);
                printf("%c",noticia.cuerpo[i]);
                i++;
            }
            while(i<j)
            {
                Color(BLACK,WHITE);
                printf(" ");
                i++;
            }

            y++;
        }
        gotoxy (2,30);

        Color(BLACK, WHITE);

    }


}

void mostrarNoticias(NodoNoticia* listaNoticias,int mostrarId) ///int para mostrar o no el id de la noticia
{
    NodoNoticia* iterador = listaNoticias;

    while(iterador != NULL)
    {

        system("cls");

        Color(BLUE,WHITE);
        gotoxy(70,4);
        printf("VISTA MODO CIUDADANO");
        Color(BLACK,WHITE);
        if(iterador->dato.bajaNoticia)
        {
            mostrarUnaNoticia(iterador->dato,mostrarId);

            gotoxy(90,24);
            printf("%c Siguiente\n",16);
            getch();
        }

        iterador = iterador->siguiente;
    }

}

void guardarNoticias(NodoNoticia* listaNoticias)
{
    FILE* pArchivo = fopen(ARCHIVO_NOTICIAS,"wb");
    NodoNoticia* iterador = listaNoticias;

    if(pArchivo != NULL)
    {
        while(iterador != NULL)
        {
            fwrite( &(iterador->dato),sizeof(Noticia),1,pArchivo);

            iterador = iterador->siguiente;
        }

        fclose(pArchivo);
    }
    else
    {
        printf("\nNo se pudo abrir el archivo Noticias para su escritura\n");
    }
}

NodoNoticia* modificarDatosNoticia(NodoNoticia* listaNoticias,int id) ///modifica segun el id
{
    system("cls");

char icono;
int x, y, teclaMov, ingresoSubmenu,salir;
x = 30;
y = 13;
ingresoSubmenu = 1;
salir=0;
icono = 16;

gotoxy(0,0);


///codigo para seleccionar conflechas y pulsar enter
    NodoNoticia* nodoBuscado = validarNoticia(listaNoticias,id);

    if(nodoBuscado != NULL)
    {
        do
        {
            menuModificarDatosNoticia();


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

                else if (teclaMov == DOWN && y<15)
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
                    case 1:///cambiar titulo
                        gotoxy(30,10);printf("Ingrese el nuevo titulo:");
                        gotoxy(30,12);
                        mostrarCursor();
                        fflush(stdin);
                        gets(nodoBuscado->dato.titulo);
                        ocultarCursor();

                        salir = 1;
                        x = 30;
                        y = 13;
                        system("cls");
                        break;

                    case 2:///cambiar fecha
                        gotoxy(30,10);printf("Ingrese la nueva fecha:\n\n");
                        mostrarCursor();
                        nodoBuscado->dato.fechaNoticia = cargarFecha();
                        ocultarCursor();

                        salir = 1;
                        x = 30;
                        y = 13;
                        system("cls");


                        break;

                    case 3:///cambiar cuerpo
                        gotoxy(30,10);printf("Ingrese el nuevo cuerpo:");
                        gotoxy(30,12);mostrarCursor();
                        fflush(stdin);
                        gets(nodoBuscado->dato.cuerpo);
                        ocultarCursor();
                        break;

                    }


                    salir = 1;
                    x = 30;
                    y = 13;
                    system("cls");

                    break;



                }
            }while(teclaMov !=ESC && salir != 1);
     //codigo para salir
    }while (teclaMov !=ESC);

}
else
{
    printf("\nEl id ingresado no existe");
}





return listaNoticias;
}

void menuModificarDatosNoticia()
{
    int x=30,y=10;

    gotoxy(x,y);
    printf("--------------------------------------------------");
    y++;
    gotoxy(x,y);
    printf("\t     ¿Desea modificar algún dato?");
    y++;
    gotoxy(x,y);
    printf("--------------------------------------------------");
    y++;
    gotoxy(x,y);
    printf("\t     Modificar titulo");
    y++;
    gotoxy(x,y);
    printf("\t     Modificar fecha");
    y++;
    gotoxy(x,y);
    printf("\t     Modificar cuerpo");
    y++;
    gotoxy(x,y);
    printf("--------------------------------------------------");
    y+=2;
    gotoxy(x,y);
    printf("\tPara salir presione la tecla Esc\n\n");

}

NodoNoticia* darDeBajaNoticia(NodoNoticia* listaNoticias,int id)
{
    NodoNoticia* nodoBuscado = validarNoticia(listaNoticias,id);

    if(nodoBuscado != NULL)
    {
        nodoBuscado->dato.bajaNoticia = 0;
    }


    return listaNoticias;
}

NodoNoticia* validarNoticia(NodoNoticia* listaNoticias,int id)
{
    NodoNoticia* iterador = listaNoticias;

    while(iterador != NULL && iterador->dato.idNoticia != id)
    {
        iterador = iterador->siguiente;
    }

    return iterador;
}
