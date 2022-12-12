#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "estilo.h"
#include "fecha.h"
#include "preguntasFrecuentes.h"
#include "menus.h"

#define ARCHIVO_PREGUNTAS_FRECUENTES "PreguntasFrecuentes.bin"

#define N 100
#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

NodoPreguntaFrecuente* bajarPreguntasFrecuentesArchivo(NodoPreguntaFrecuente* listaPreguntasFrecuentes)
{
    FILE* pArchivo = fopen(ARCHIVO_PREGUNTAS_FRECUENTES,"rb");
    PreguntaFrecuente pregunta;

    if(pArchivo != NULL)
    {
        while( fread(&pregunta,sizeof(PreguntaFrecuente),1,pArchivo) > 0)
        {
            listaPreguntasFrecuentes = agregarAlFinalNodoPreguntaFrecuente(listaPreguntasFrecuentes,crearNodoPreguntaFrecuente(pregunta));
        }

        fclose(pArchivo);
    }
    else
    {
        printf("\nNo se pude abrir el archivo Preguntas Frecuentes\n");
    }

    return listaPreguntasFrecuentes;
}

NodoPreguntaFrecuente* agregarAlFinalNodoPreguntaFrecuente(NodoPreguntaFrecuente* listaPreguntasFrecuentes,NodoPreguntaFrecuente* nuevoNodo)
{
    if(listaPreguntasFrecuentes == NULL)
    {
        listaPreguntasFrecuentes = nuevoNodo;
    }
    else
    {
        NodoPreguntaFrecuente* ultimoNodo;
        ultimoNodo = buscarUltimoNodoPreguntaFrecuente(listaPreguntasFrecuentes);

        ultimoNodo->siguiente = nuevoNodo;
    }

    return listaPreguntasFrecuentes;
}
NodoPreguntaFrecuente* buscarUltimoNodoPreguntaFrecuente(NodoPreguntaFrecuente* iterador)
{
    if(iterador != NULL)
    {
        while(iterador->siguiente != NULL)
        {
            iterador = iterador->siguiente;
        }
    }

    return iterador;
}
NodoPreguntaFrecuente* inicListaPreguntasFrecuentes()
{
    return NULL;
}
NodoPreguntaFrecuente* crearNodoPreguntaFrecuente(PreguntaFrecuente pregunta)
{
    NodoPreguntaFrecuente* nuevoNodo = malloc(sizeof(NodoPreguntaFrecuente));

    nuevoNodo->dato = pregunta;
    nuevoNodo->siguiente = NULL;

    return nuevoNodo;
}
PreguntaFrecuente crearUnaPreguntaFrecuente(int id)
{
    PreguntaFrecuente pregunta;

    pregunta.idPregunta = id;

    mostrarCursor();

    printf("\nIngrese la pregunta:  ");
    fflush(stdin);
    gets(pregunta.pregunta);

    printf("\nIngrese la respuesta:  ");
    fflush(stdin);
    gets(pregunta.respuesta);

    pregunta.bajaPregunta = 1;

    ocultarCursor();

    return pregunta;

}

int ultimoIdCargadoPreguntaFrecuente(NodoPreguntaFrecuente* listaPreguntasFrecuentes)
{
    NodoPreguntaFrecuente* iterador = listaPreguntasFrecuentes;
    int ultimoId=0;

    if(iterador != NULL)
    {
        while(iterador->siguiente != NULL)
        {
            iterador = iterador->siguiente;
        }
        ultimoId = iterador->dato.idPregunta;
    }

    return ultimoId;
}

void mostrarUnaPreguntaFrecuente(PreguntaFrecuente pregunta,int mostrarId)
{
    if(pregunta.bajaPregunta == 1)
    {
        if(mostrarId) ///si es 1 muestra el id
        {
            gotoxy(15,10);
            printf("Id: %i",pregunta.idPregunta);
        }

        gotoxy(15,11);
        Color(CYAN,BLACK);
        printf("%s",pregunta.pregunta);
        Color(BLACK,WHITE);
        //gotoxy(30,17);Color(BLACK,WHITE);printf("\n%s\n\n",pregunta.respuesta);

        int i=0,y=13,x0=15,validosRespuesta;

        validosRespuesta = strlen(pregunta.respuesta);

        ///cuerpo


        for(int j=100 ; j <= 1000 ; j+=100) ///muestro 10 renglones de 100 caracteres
        {
            gotoxy(x0,y);
            while(i<j && i < validosRespuesta)
            {
                printf("%c",pregunta.respuesta[i]);
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
    }
}

void mostrarPreguntasFrecuentes(NodoPreguntaFrecuente* listaPreguntasFrecuentes,int mostrarId)  ///variable para ver como mostrar las preguntas
{
    NodoPreguntaFrecuente* iterador = listaPreguntasFrecuentes;

    while(iterador != NULL)
    {
        system("cls");
        if(iterador->dato.bajaPregunta)
        {
            mostrarUnaPreguntaFrecuente(iterador->dato,mostrarId);

            gotoxy(15,24);
            printf("%c Siguiente",16);
            getch();
        }



        iterador = iterador->siguiente;
    }
}

void guardarPreguntasFrecuentes(NodoPreguntaFrecuente* listaPreguntasFrecuentes)
{
    FILE* pArchivo = fopen(ARCHIVO_PREGUNTAS_FRECUENTES,"wb");
    NodoPreguntaFrecuente* iterador = listaPreguntasFrecuentes;

    if(pArchivo != NULL)
    {
        while(iterador != NULL)
        {
            fwrite(&(iterador->dato),sizeof(PreguntaFrecuente),1,pArchivo);

            iterador = iterador->siguiente;
        }

        fclose(pArchivo);
    }
    else
    {
        printf("\nNo se pudo abrir el archivo Preguntas Frecuentes para su escritura");
    }

}

NodoPreguntaFrecuente* modificarDatosPreguntaFrecuente(NodoPreguntaFrecuente* listaPreguntasFrecuentes,int id) ///modifica segun el id
{
    NodoPreguntaFrecuente* nodoBuscado;
    char icono;
    int x, y, teclaMov, ingresoSubmenu,salir;
    x = 30;
    y = 13;
    ingresoSubmenu = 1;
    salir=0;
    icono = 16;

    gotoxy(0,0);

    system("cls");
    ///codigo para seleccionar conflechas y pulsar enter

    nodoBuscado = validarPreguntaFrecuente(listaPreguntasFrecuentes,id);

    if(nodoBuscado != NULL)
    {
        do
        {
            ocultarCursor();
            menuModificarDatosPreguntaFrecuente();


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
                        gotoxy(30,10);printf("Ingrese la nueva pregunta:  ");
                        gotoxy(30,12);mostrarCursor();
                        fflush(stdin);
                        gets(nodoBuscado->dato.pregunta);
                        ocultarCursor();

                        salir = 1;
                        x = 30;
                        y = 13;
                        system("cls");
                        break;

                    case 2:
                        gotoxy(30,10);printf("Ingrese la nueva respuesta:  ");
                        gotoxy(30,12); mostrarCursor();
                        fflush(stdin);
                        gets(nodoBuscado->dato.respuesta);
                        ocultarCursor();

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
        printf("\nEl id ingresado no existe");
    }








    return listaPreguntasFrecuentes;
}

void menuModificarDatosPreguntaFrecuente()
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
    printf("\t     Pregunta");
    y++;
    gotoxy(x,y);
    printf("\t     Respuesta");
    y++;
    gotoxy(x,y);
    printf("--------------------------------------------------");
    y+=2;
    gotoxy(x,y);
    printf("\tPara salir presione la tecla Esc\n\n");
}

NodoPreguntaFrecuente* darDeBajaPreguntaFrecuente(NodoPreguntaFrecuente* listaPreguntasFrecuentes,int id)
{
    NodoPreguntaFrecuente* nodoBuscado;
    nodoBuscado = validarPreguntaFrecuente(listaPreguntasFrecuentes,id);

    if(nodoBuscado != NULL)
    {
        nodoBuscado->dato.bajaPregunta = 0;
    }
    else
    {
        printf("\nEl id ingreado no existe");
    }

    return listaPreguntasFrecuentes;

}

NodoPreguntaFrecuente* validarPreguntaFrecuente(NodoPreguntaFrecuente* listaPreguntasFrecuentes,int id)
{
    NodoPreguntaFrecuente* iterador = listaPreguntasFrecuentes;

    if(iterador != NULL && iterador->dato.idPregunta != id)
    {
        iterador = iterador->siguiente;
    }

    return iterador;

}


