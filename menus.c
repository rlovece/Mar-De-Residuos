#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "estilo.h"
#include "menus.h"
#include "empresas.h"
#include "noticias.h"
#include "preguntasFrecuentes.h"
#include "residuos.h"
#include "residuosEmpresa.h"
#include "Ciudadado.h"
#include "Transacciones.h"
#include "pthread.h"

#define N 100
#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

int ejecutar;

///Todo

Todo inicTodo ()
{
    Todo todo;
    todo.arbolCiudadanos = inicArbolCiudadanos();
    todo.arbolEmpresa = inicArbolEmpresa ();
    todo.listaNoticias = inicListaNoticias();
    todo.listaPreguntasFrecuentes = inicListaPreguntasFrecuentes();
    todo.listaResiduosEmpresa = inicListaResiduosEmpresa();
    todo.listaTransacciones = inicListaTransaciones ();
    todo.listaResiduos = inicListaResiduos ();
    return todo;
}

Todo bajarTodo (Todo todo)
{
    todo.arbolCiudadanos =  bajarCiudadanosArchivo (todo.arbolCiudadanos);
    todo.arbolEmpresa = bajarEmpresasArchivo (todo.arbolEmpresa);
    todo.listaNoticias = bajarNoticiasArchivo (todo.listaNoticias);
    todo.listaPreguntasFrecuentes = bajarPreguntasFrecuentesArchivo (todo.listaPreguntasFrecuentes);
    todo.listaResiduosEmpresa = bajarResiduosEmpresaArchivo (todo.listaResiduosEmpresa);
    todo.listaTransacciones = bajarTransaccionesArchivo (todo.listaTransacciones);
    todo.listaResiduos = bajarResiduosArchivo (todo.listaResiduos);
    bajarAdminArchivo(&todo.administrador);
    return todo;
}

void guardarTodo (Todo todo)
{
    guardarEmpresas(todo.arbolEmpresa);
    guardarResiduos(todo.listaResiduos);
    guardarResiduosEmpresa(todo.listaResiduosEmpresa);
    guardarPreguntasFrecuentes(todo.listaPreguntasFrecuentes);
    guardarNoticias(todo.listaNoticias);
    guardarCiudadanos (todo.arbolCiudadanos);
    guardarTransacciones (todo.listaTransacciones);
}



void menuPrincipal ()
{

    /// MENU
    gotoxy(30,16);
    printf("--------------------------------------------------");
    gotoxy(30,17);
    printf("             BIENVENIDO A MARDERESIDUOS ");
    gotoxy(30,18);
    printf("--------------------------------------------------");
    gotoxy(30,19);
    printf("\t     Login");
    gotoxy(30,20);
    printf("\t     Registro");
    gotoxy(30,21);
    printf("\t     Preguntas Frecuentes");
    gotoxy(30,22);
    printf("--------------------------------------------------");
    gotoxy(30,27);
    printf("\tPara salir presione la tecla Esc\n\n");

}

void subProgramaMenuPrincipal (Todo* todo)
{
    system("cls");

    char icono;
    int x, y, teclaMov, ingresoSubmenu,salir;
    x = 30;
    y = 19;
    ingresoSubmenu = 1;
    salir=0;
    icono = 16;

    gotoxy(0,0);

    ///codigo para seleccionar conflechas y pulsar enter
    do
    {
        cabecera();
        ///MENU
        menuPrincipal();

        gotoxy(30, 19);
        printf("%c", icono);

        ingresoSubmenu = 1;
        salir = 0;
        do
        {
            teclaMov = getch();

            if (teclaMov == UP && y>19)
            {
                gotoxy(x, y);
                printf(" ");
                y--;
                gotoxy(x, y);
                printf("%c", icono);
                ingresoSubmenu--;

            }

            else if (teclaMov == DOWN && y<21)
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
                case 1:/// Login
                    subprogramaMenuLogin (todo);

                    salir = 1;
                    x = 30;
                    y = 19;
                    system("cls");
                    break;

                case 2:/// Registro
                    subprogramaMenuRegistro(todo);

                    salir = 1;
                    x = 30;
                    y = 19;
                    system("cls");

                    break;

                case 3:///Preguntas Frecuentes
                    mostrarPreguntasFrecuentes(todo->listaPreguntasFrecuentes,0);

                    salir = 1;
                    x = 30;
                    y = 19;
                    system("cls");

                    break;
                }
            }
        }
        while(teclaMov !=ESC && salir != 1);
    } //codigo para salir
    while (teclaMov !=ESC);

}

void menuLogin ()
{
    gotoxy(30,10);
    printf("--------------------------------------------------");
    gotoxy(30,11);
    printf("             BIENVENIDO NUEVAMENTE ");
    gotoxy(30,12);
    printf("--------------------------------------------------");
    gotoxy(30,13);
    printf("\t     Iniciar sesion Ciudadano");
    gotoxy(30,14);
    printf("\t     Iniciar sesion Empresa");
    gotoxy(30,15);
    printf("\t     Iniciar sesion Administrador");
    gotoxy(30,16);
    printf("--------------------------------------------------");
    gotoxy(30,19);
    printf("\tPara salir presione la tecla Esc\n\n");

}

void subprogramaMenuLogin (Todo* todo)
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

    do
    {
        menuLogin();

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
                case 1:/// Ciudadano
                    subprogramaLoginCiudadano (todo);

                    salir = 1;
                    x = 30;
                    y = 13;
                    gotoxy(2,20);
                    system("pause");
                    system("cls");
                    break;

                case 2:/// Empresa
                    subprogramaLoginEmpresa(todo);

                    salir = 1;
                    x = 30;
                    y = 13;
                    gotoxy(2,20);
                    system("pause");
                    system("cls");

                    break;

                case 3:///      Admin

                    if(logInAdmin(todo->administrador))
                    {
                        subprogramaMenuAdmin(todo);
                    }

                    salir = 1;
                    x = 30;
                    y = 13;
                    gotoxy(2,20);
                    system("pause");
                    system("cls");

                    break;
                }
            }
        }
        while(teclaMov !=ESC && salir != 1);
    } //codigo para salir
    while (teclaMov !=ESC);
}

void menuRegistro ()
{
    gotoxy(30,4);
    printf("--------------------------------------------------");
    gotoxy(30,5);
    printf("             GRACIAS POR SER PARTE ");
    gotoxy(30,6);
    printf("--------------------------------------------------");
    gotoxy(30,7);
    printf("\t     Registro para Ciudadados");
    gotoxy(30,8);
    printf("\t     Registro para Empresas");
    gotoxy(30,9);
    printf("--------------------------------------------------");
    gotoxy(30,12);
    printf("\tPara salir presione la tecla Esc\n\n");

}

void subprogramaMenuRegistro(Todo* todo)
{
    system("cls");

    Ciudadano ciudadano;
    char icono;
    int x, y, teclaMov, ingresoSubmenu,salir,dni;
    x=30;
    y=7;
    ingresoSubmenu = 1;
    salir=0;
    icono = 16;

    ///codigo para seleccionar conflechas y pulsar enter

    do
    {
        menuRegistro();

        gotoxy(30, 7);
        printf("%c", icono);

        ingresoSubmenu = 1;
        salir = 0;
        do
        {
            teclaMov = getch();

            if (teclaMov == UP && y>7)
            {
                gotoxy(x, y);
                printf(" ");
                y--;
                gotoxy(x, y);
                printf("%c", icono);
                ingresoSubmenu--;

            }

            else if (teclaMov == DOWN && y<8)
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
                case 1:/// registro Ciudadano
                    printf("\nIngrese su DNI: ");
                    mostrarCursor();
                    scanf("%i",&dni);
                    ocultarCursor();
                    if(validarCiudadano(todo->arbolCiudadanos,dni) == 0)
                    {
                        ciudadano = cargarUnCiudadano(dni);
                        todo->arbolCiudadanos = insertar(todo->arbolCiudadanos,ciudadano);
                    }
                    else
                    {
                        printf("\nEl DNI ingresado ya se encuentra registrado\n");
                    }

                    salir = 1;
                    x = 30;
                    y = 7;
                    gotoxy(2,30);
                    system("pause");
                    system("cls");
                    break;

                case 2:/// registro Empresa

                    todo->arbolEmpresa = cargarUnaEmpresa(todo->arbolEmpresa);

                    salir = 1;
                    x = 30;
                    y = 7;
                    gotoxy(2,30);
                    system("pause");
                    system("cls");

                    break;
                }
            }
        }
        while(teclaMov !=ESC && salir != 1);
    } //codigo para salir
    while (teclaMov !=ESC);
}

///empresas

void subprogramaLoginEmpresa (Todo* todo)
{
    int cuit;
    gotoxy(50,10);
    printf ("CUIT:   ");
    mostrarCursor();
    Color(WHITE,BLACK);
    scanf ("%i", &cuit);
    Color(BLACK,WHITE);
    ocultarCursor();
    if (logInEmpresa(todo->arbolEmpresa,cuit))
    {

        subprogramaMenuEmpresas(todo,cuit);
    }
}


void subprogramaMenuEmpresas(Todo* todo, int cuit)
{
    char respuesta;

    system("cls");

    char icono;
    int x, y, teclaMov, ingresoSubmenu,salir;
    x = 30;
    y = 8;
    ingresoSubmenu = 1;
    salir=0;
    icono = 16;

    gotoxy(0,0);

    ///codigo para seleccionar conflechas y pulsar enter
    do
    {
        menuEmpresas();

        gotoxy(30, 8);
        printf("%c", icono);

        ingresoSubmenu = 1;
        salir = 0;
        do
        {
            teclaMov = getch();

            if (teclaMov == UP && y>8)
            {
                gotoxy(x, y);
                printf(" ");
                y--;
                gotoxy(x, y);
                printf("%c", icono);
                ingresoSubmenu--;
            }

            else if (teclaMov == DOWN && y<16)
            {
                gotoxy(x, y);
                printf(" ");
                y++;
                gotoxy(x, y);
                printf("%c", icono);
                ingresoSubmenu++;
            }
            ///codigo para que al pulsar enterse limpie la pantalla y salga sólo
            //la opcion elegida
            if (teclaMov == ENTER)
            {
                system("cls");

                switch (ingresoSubmenu)
                {

                case 1:///modificar datos
                    (todo->arbolEmpresa) = modificarDatosEmpresa(todo->arbolEmpresa,cuit);

                    salir = 1;
                    x = 30;
                    y = 8;
                    gotoxy(2,27);

                    system("cls");

                    break;

                case 2:///ver residuos
                    mostrarResiduosEmpresa(todo->listaResiduosEmpresa,todo->listaResiduos,cuit);

                    salir = 1;
                    x = 30;
                    y = 8;
                    gotoxy(2,27);

                    system("cls");

                    break;

                case 3:///agregar residuos
                    (todo->listaResiduosEmpresa) = subprogramaCrearUnResiduoEmpresa(todo->listaResiduosEmpresa,todo->listaResiduos,cuit);

                    salir = 1;
                    x = 30;
                    y = 8;
                    gotoxy(2,27);
                    system("cls");

                    break;

                case 4:///eliminar residuo con el que trabaja
                    (todo->listaResiduosEmpresa) = subprogramaDarDeBajaResiduoEmpresa(todo->listaResiduosEmpresa,todo->listaResiduos,cuit); ///no los elimina !!!

                    salir = 1;
                    x = 30;
                    y = 8;
                    gotoxy(2,27);
                    system("pause");
                    system("cls");

                    break;

                case 5:///ingresar nuevo residuo al sistema
                    (todo->listaResiduos) = cargarUnResiduo(todo->listaResiduos);


                    salir = 1;
                    x = 30;
                    y = 8;
                    gotoxy(2,27);
                    system("pause");
                    system("cls");

                    break;

                case 6:///ver retiros pendientes
                    mostrarRetirosPendientes(todo->listaTransacciones,todo->listaResiduos,cuit);

                    salir = 1;
                    x = 30;
                    y = 8;
                    gotoxy(2,27);
                    system("cls");

                    break;

                case 7:///ver retiros realizados
                    mostrarRetirosRealizados(todo->listaTransacciones,todo->listaResiduos,cuit);

                    salir = 1;
                    x = 30;
                    y = 8;
                    gotoxy(2,27);
                    system("pause");
                    system("cls");

                    break;

                case 8:///marcar realizados
                    (todo->listaTransacciones) = marcarRetirosRealizados(todo->listaTransacciones,cuit);

                    salir = 1;
                    x = 30;
                    y = 8;
                    gotoxy(2,27);

                    system("cls");

                    break;

                case 9:///dar de baja
                    gotoxy(30,10);
                    printf("Esta seguro? s\n ");
                    gotoxy(30,12);
                    mostrarCursor();
                    fflush(stdin);
                    scanf("%c",&respuesta);
                    if(respuesta == 's' || respuesta == 'S')
                    {
                        (todo->arbolEmpresa) = darDeBajaEmpresa(todo->arbolEmpresa,cuit);
                    }

                    salir = 1;
                    x = 30;
                    y = 8;

                    ocultarCursor();

                    gotoxy(2,27);
                    system("pause");
                    teclaMov =ESC;
                    break;
                }
            }
        }
        while(teclaMov !=ESC && salir != 1);
    } //codigo para salir
    while (teclaMov !=ESC);

    guardarTodo(*todo);
}

void subprogramaLoginCiudadano (Todo* todo)
{
    int DNI;
    gotoxy(50,10);
    printf ("DNI:  ");
    mostrarCursor();
    Color(WHITE,BLACK);
    scanf ("%i", &DNI);
    Color(BLACK,WHITE);
    ocultarCursor();
    if (loginCiudadano(todo->arbolCiudadanos,DNI))
    {
        subprogramaMenuCiudadano(todo, DNI);
    }
}

void subprogramaMenuCiudadano(Todo* todo, int DNI)
{
    int auxIdResiduo, auxIdEmpresa, auxIdTrans;
    Transaccion nuevaTrans;
    nodoCiudadano* nodoBuscado = inicArbolCiudadanos ();
    char correcto = 'n';

    system("cls");

    char icono, respuesta;
    int x, y, teclaMov, ingresoSubmenu,salir;
    x = 5;
    y = 7;
    ingresoSubmenu = 1;
    salir=0;
    icono = 16;
    gotoxy(0,0);

    pthread_t hilo;

    ejecutar = 1;

    ///codigo para seleccionar conflechas y pulsar enter

    do
    {
        menuCiudadano();
        pthread_create(&hilo,NULL,mostrarSeccionNoticias,todo->listaNoticias);

        gotoxy(5, 7);
        printf("%c", icono);

        ingresoSubmenu = 1;
        salir = 0;
        do
        {
            teclaMov = getch();


            if (teclaMov == UP && y>7)
            {

                gotoxy(x, y);
                printf(" ");
                y--;
                gotoxy(x, y);
                printf("%c", icono);
                ingresoSubmenu--;

            }

            else if (teclaMov == DOWN && y<10)
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
                case 1:///verificar datos
                    ejecutar = 0;

                    nodoBuscado = buscarCiudadano (todo->arbolCiudadanos, DNI);
                    nodoBuscado->dato = modificarCiudadano (nodoBuscado->dato);

                    salir = 1;
                    x = 5;
                    y = 7;



                    gotoxy(2,27);
                    system("pause");
                    system("cls");

                    ejecutar = 1;
                    break;

                case 2:///coordinar transaccion


                    ejecutar = 0;

                    system("cls");
                    gotoxy(5,2);
                    printf("| ID    ");
                    gotoxy(13, 2);
                    printf("| NOMBRE");
                    gotoxy(32, 2);
                    printf("|\n");
                    gotoxy(5,3);
                    printf("-----------------------------");
                    mostrarResiduosACiudadano (todo->listaResiduos, 4);

                    printf ("\n Ingrese el ID del residuo que tiene para entregar: ");
                    mostrarCursor();
                    scanf ("%i", &auxIdResiduo);

                    while (auxIdResiduo> ultimoIdCargado(todo->listaResiduos))
                    {
                        Color (BLACK, RED);
                        printf ("\n VALOR INVALIDO\n");
                        Color (BLACK, WHITE);
                        printf ("\n Ingrese el ID del residuo que tiene para entregar: ");
                        scanf ("%i", auxIdResiduo);
                    }

                    system ("cls");
                    printf ("\n       EMPRESAS QUE TRABAJAN CON ESE MATERIAL\n");
                    gotoxy(2,3);
                    printf("-------------------------------------------------------");
                    gotoxy (2, 4);
                    printf("| CUIT  ");
                    gotoxy (10, 4);
                    printf("| NOMBRE / DIRECCION / HORARIO");
                    gotoxy(48,4);
                    printf("| Retira?");
                    gotoxy(57,4);
                    printf("|");
                    gotoxy(2,5);
                    printf("-------------------------------------------------------");
                    mostrarEmpresasACiudadano (todo,auxIdResiduo, 6);


                    printf ("\n Ingrese el CUIT de la empresa que desee: \n");
                    scanf ("%i", &auxIdEmpresa);

                    nuevaTrans = crearUnaTransaccion (ultimoIdCargadoTransaccion(todo->listaTransacciones)+1, auxIdResiduo, DNI, auxIdEmpresa);

                    mostrarUnaTransaccion(nuevaTrans, todo->listaResiduos);

                    printf ("\n\n Los datos son correctos? s/n");
                    fflush(stdin);
                    scanf("%c", &correcto);
                    ocultarCursor();

                    if(correcto == 's' || correcto == 'S')
                    {
                        todo->listaTransacciones = agregarAlFinalNodoTransaccion (todo->listaTransacciones, crearNodoTransaccion(nuevaTrans));
                    }

                    salir = 1;
                    x = 5;
                    y = 7;
                    gotoxy(2,27);

                    system("pause");
                    system("cls");
                    ejecutar = 1;
                    break;

                case 3:///ver transacciones pedientes
                    ejecutar = 0;
                    mostrarTransaccionesPendientesCiudadano(todo, DNI);
                    printf ("\n\n >>> Desea modificar alguna transaccion? s/n");
                    fflush(stdin);
                    mostrarCursor();
                    scanf("%c",&respuesta);
                    ocultarCursor();
                    if(respuesta == 's' || respuesta == 'S')
                    {
                        printf ("\n >>> Ingrese el ID de la transaccion que desa modificar s/n");
                        fflush(stdin);
                        scanf("%i",&auxIdTrans);
                        todo->listaTransacciones = modificarTransacccionCiudadano (todo, auxIdTrans, DNI);

                    }


                    salir = 1;
                    x = 5;
                    y = 7;
                    gotoxy(2,27);
                    system("pause");
                    system("cls");

                    ejecutar = 1;
                    break;

                case 4:///dar de baja
                    ejecutar = 0;
                    printf("Esta seguro? s\n ");
                    fflush(stdin);
                    mostrarCursor();
                    scanf("%c",&respuesta);
                    if(respuesta == 's' || respuesta == 'S')
                    {
                        (todo->arbolCiudadanos) = darDeBajaCiudadano (todo->arbolCiudadanos, DNI);
                        teclaMov = ESC;
                    }
                    guardarCiudadanos(todo->arbolCiudadanos);
                    ocultarCursor();

                    ejecutar = 1;
                    salir = 1;
                    x = 5;
                    y = 7;
                    gotoxy(2,27);
                    system("cls");

                    break;
                }
            }
        }
        while(teclaMov !=ESC && salir != 1);
    } //codigo para salir
    while (teclaMov !=ESC);

    ejecutar=0;

    guardarTodo(*todo);

}

void mostrarEmpresasACiudadano (Todo* todo,int IDResiduo, int yEmpresa)
{
    NodoResiduosEmpresa* iterador = todo->listaResiduosEmpresa;
    NodoArbolEmpresa* auxNodoEmpresa = inicArbolEmpresa ();

    while(iterador != NULL)
    {
        if(iterador->dato.bajaResiduoEmpresa == 1 && iterador->dato.idResiduo == IDResiduo)
        {
            auxNodoEmpresa = validarEmpresa(todo->arbolEmpresa, iterador->dato.CUIT);

            if(auxNodoEmpresa->dato.bajaEmpresa==1)
            {
                mostrarUnaEmpresaACiudadano (auxNodoEmpresa->dato, yEmpresa);
                yEmpresa = yEmpresa +4;
            }
        }

        iterador = iterador->siguiente;
    }
}



nodoTransaccion* modificarTransacccionCiudadano (Todo* todo, int IdTransaccion, int DNI)
{
    char respuesta;

    /// PARA MOVER FLECHA
    char icono;
    int x, y, teclaMov, ingresoSubmenu,salir;
    x = 5;
    y = 14;
    ingresoSubmenu = 1;
    salir=0;
    icono = 16;
    gotoxy(0,0); /// FIN MOVER

    nodoTransaccion* auxTrans = inicListaTransaciones ();
    auxTrans = buscarTransaccion (todo->listaTransacciones, IdTransaccion);

    if(auxTrans)
    {
        if (DNI == auxTrans->dato.DNI)
        {
            do
            {
                system ("cls");
                mostrarUnaTransaccion (auxTrans->dato, todo->listaResiduos);

                menuModificarTransaccionParaCiudadano ();

                gotoxy(5, 15);
                printf("%c", icono);

                ingresoSubmenu = 1;
                salir = 0;

                gotoxy (5, 13);

                do
                {
                    teclaMov = getch();

                    if (teclaMov == UP && y>14)
                    {

                        gotoxy(x, y);
                        printf(" ");
                        y--;
                        gotoxy(x, y);
                        printf("%c", icono);
                        ingresoSubmenu--;

                    }

                    else if (teclaMov == DOWN && y<17)
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
                        switch (ingresoSubmenu)
                        {
                        case 1:

                            gotoxy (5, 25);
                            printf("Ingrese nueva cantidad: ");
                            mostrarCursor();
                            fflush(stdin);
                            scanf("%i", &(auxTrans->dato.cantidad));
                            ocultarCursor();

                            salir = 1;
                            x = 5;
                            y = 14;
                            gotoxy(2,27);
                            system("pause");
                            system("cls");

                            break;

                        case 2:
                            gotoxy (5, 25);
                            printf("Ingrese nueva fecha: ");
                            mostrarCursor();
                            auxTrans->dato.fechaEntrega = cargarFecha ();
                            ocultarCursor();

                            salir = 1;
                            x = 5;
                            y = 14;
                            gotoxy(2,27);
                            system("pause");
                            system("cls");
                            break;

                        case 3:
                            gotoxy (5, 25);
                            printf("\n Ingrese nuevo comentario / horarios: ");
                            mostrarCursor();
                            fflush(stdin);
                            gets(auxTrans->dato.horariosDeRetiro);
                            ocultarCursor();

                            salir = 1;
                            x = 5;
                            y = 14;
                            gotoxy(2,27);
                            system("pause");
                            system("cls");
                            break;

                        case 4:
                            gotoxy (5, 25);
                            printf("\n Esta seguro que desea cancelar la entrega? s/n ");
                            fflush(stdin);
                            mostrarCursor();
                            scanf("%c",&respuesta);
                            if(respuesta == 's' || respuesta == 'S')
                            {
                                auxTrans->dato.estado =0; /// 0 es estado cancelado
                            }
                            ocultarCursor();
                            salir = 1;
                            x = 5;
                            y = 14;
                            gotoxy(2,27);
                            system("pause");
                            system("cls");

                        case 0:
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
            printf (" \n El Id ingresado no corresponde a una transaccion suya. \n\n");
        }
    }
    else
    {
         printf (" \n El Id ingresado no existe. \n\n");
    }

    return auxTrans;

}


void menuModificarTransaccionParaCiudadano ()
{

    printf("\n  --------------------------------------------------");
    printf("\n         Que dato desea modificar? ");
    printf("\n  --------------------------------------------------");
    printf("\n\t       Cantidad");
    printf("\n\t       Fecha");
    printf("\n\t       Comentarios / Horarios");
    printf("\n\t       Cancelar Transaccion");
    printf("\n  --------------------------------------------------\n");
    printf("\n\n\tPara salir presione la tecla Esc\n\n");
}







NodoResiduo* subprogramaMenuResiduos(NodoResiduo* listaResiduo)
{

    system("cls");

    char icono;
    int x, y, teclaMov, ingresoSubmenu,salir;
    x = 30;
    y = 7;
    ingresoSubmenu = 1;
    salir=0;
    icono = 16;

    gotoxy(0,0);

    ///codigo para seleccionar conflechas y pulsar enter

    do
    {
        ///MENU
        menuResiduos();


        gotoxy(30, 7);
        printf("%c", icono);

        ingresoSubmenu = 1;
        salir = 0;
        do
        {
            teclaMov = getch();

            if (teclaMov == UP && y>7)
            {

                gotoxy(x, y);
                printf(" ");
                y--;
                gotoxy(x, y);
                printf("%c", icono);
                ingresoSubmenu--;

            }

            else if (teclaMov == DOWN && y<10)
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
                case 1:///ver residuos
                    mostrarResiduos(listaResiduo,1);

                    salir = 1;
                    x = 30;
                    y = 7;

                    gotoxy(2,27);
                    system("pause");
                    system("cls");
                    break;

                case 2:///agregar residuo
                    listaResiduo = cargarUnResiduo(listaResiduo);

                    salir = 1;
                    x = 30;
                    y = 7;
                    system("cls");

                    break;

                case 3:///modificar residuo
                    listaResiduo = modificarDatosResiduo(listaResiduo);


                    salir = 1;
                    x = 30;
                    y = 7;
                    system("cls");

                    break;

                case 4:
                    ///dar de baja
                    listaResiduo = darDeBajaResiduo(listaResiduo);

                    salir = 1;
                    x = 30;
                    y = 7;
                    system("cls");
                    break;


                }
            }
        }
        while(teclaMov !=ESC && salir != 1);
    } //codigo para salir
    while (teclaMov !=ESC);

    return listaResiduo;
}

void menuAdmin()
{

    gotoxy(30,4);
    printf("--------------------------------------------------");
    gotoxy(30,5);
    printf("             GRACIAS POR SER PARTE ");
    gotoxy(30,6);
    printf("--------------------------------------------------");
    gotoxy(30,7);
    printf("\t     Ver Preguntas Frecuentes");
    gotoxy(30,8);
    printf("\t     Modificar preguntas frecuentes");
    gotoxy(30,9);
    printf("\t     Agregar pregunta");
    gotoxy(30,10);
    printf("\t     Eliminar pregunta");
    gotoxy(30,11);
    printf("\t     Ver Noticias");
    gotoxy(30,12);
    printf("\t     Modificar noticias");
    gotoxy(30,13);
    printf("\t     Agregar noticia");
    gotoxy(30,14);
    printf("\t     Eliminar noticia");
    gotoxy(30,15);
    printf("\t     Ver ciudadanos");
    gotoxy(30,16);
    printf("\t     Dar de baja ciudadano");
    gotoxy(30,17);
    printf("\t     Ver empresas");
    gotoxy(30,18);
    printf("\t     Dar de baja empresa");
    gotoxy(30,19);
    printf("\t     Gestionar residuos");
    gotoxy(30,20);
    printf("\t     Ver transacciones anuladas");
    gotoxy(30,21);
    printf("\t     Ver transacciones pendientes");
    gotoxy(30,22);
    printf("\t     Ver transacciones realizadas");
    gotoxy(30,23);
    printf("--------------------------------------------------\n");
    gotoxy(30,25);
    printf("\tPara salir presione la tecla Esc\n\n");

}

void subprogramaMenuAdmin(Todo* todo)
{
    int opcion,dni,cuit,idPregunta,idNoticia;
    PreguntaFrecuente pregunta;
    Noticia noticia;
    celda arreglo[3];
    system("cls");

    inicADL(arreglo);
    cargarADL(arreglo);

    char icono, correrPrograma;
    int x, y, teclaMov, ingresoSubmenu,salir;
    x = 30;
    y = 7;
    ingresoSubmenu = 1;
    salir=0;
    icono = 16;

    gotoxy(0,0);

    ///codigo para seleccionar conflechas y pulsar enter

    do
    {
        menuAdmin();

        gotoxy(30, 7);
        printf("%c", icono);

        ingresoSubmenu = 1;
        salir = 0;
        do
        {
            teclaMov = getch();

            if (teclaMov == UP && y>7)
            {

                gotoxy(x, y);
                printf(" ");
                y--;
                gotoxy(x, y);
                printf("%c", icono);
                ingresoSubmenu--;

            }

            else if (teclaMov == DOWN && y<22)
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
                    mostrarPreguntasFrecuentes(todo->listaPreguntasFrecuentes,1); /// mostrarId = 1 para que mueste el id de las preguntas

                    salir = 1;
                    x = 30;
                    y = 7;

                    gotoxy(2,27);
                    system("pause");
                    system("cls");
                    break;

                case 2: ///modificar preguntas frecuentes
                    gotoxy(30,10);
                    printf("Ingrese el id de la pregunta que desea modificar:");
                    gotoxy(30,12);
                    mostrarCursor();
                    scanf("%i",&idPregunta);
                    todo->listaPreguntasFrecuentes = modificarDatosPreguntaFrecuente(todo->listaPreguntasFrecuentes,idPregunta);
                    ocultarCursor();

                    salir = 1;
                    x = 30;
                    y = 7;
                    gotoxy(2,27);
                    system("pause");
                    system("cls");


                    break;

                case 3:///agregar pregunta
                    idPregunta = ultimoIdCargadoPreguntaFrecuente(todo->listaPreguntasFrecuentes) + 1;
                    pregunta = crearUnaPreguntaFrecuente(idPregunta);
                    todo->listaPreguntasFrecuentes = agregarAlFinalNodoPreguntaFrecuente(todo->listaPreguntasFrecuentes,crearNodoPreguntaFrecuente(pregunta));


                    salir = 1;
                    x = 30;
                    y = 7;
                    gotoxy(2,27);
                    system("pause");
                    system("cls");

                    break;

                case 4:///eliminar pregunta
                    gotoxy(30,10);
                    printf("Ingrese el id de la pregunta que desea eliminar:  ");
                    gotoxy(30,12);
                    mostrarCursor();
                    scanf("%i",&idPregunta);
                    ocultarCursor();

                    todo->listaPreguntasFrecuentes = darDeBajaPreguntaFrecuente(todo->listaPreguntasFrecuentes,idPregunta);


                    salir = 1;
                    x = 30;
                    y = 7;
                    gotoxy(2,27);
                    system("pause");
                    system("cls");

                    break;

                case 5:///ver noticias
                    mostrarNoticias(todo->listaNoticias,1); ///que muestre el id de las noticias


                    salir = 1;
                    x = 30;
                    y = 7;
                    gotoxy(2,27);
                    system("pause");
                    system("cls");

                    break;

                case 6:///modificar noticias
                    gotoxy(30,10);
                    printf("Ingrese el id de la noticia que desea modificar:  ");
                    gotoxy(30,12);
                    mostrarCursor();
                    scanf("%i",&idNoticia);
                    ocultarCursor();
                    (todo->listaNoticias) = modificarDatosNoticia(todo->listaNoticias,idNoticia);


                    salir = 1;
                    x = 30;
                    y = 7;
                    gotoxy(2,27);
                    system("pause");
                    system("cls");

                    break;

                case 7:    ///agregar noticias
                    idNoticia = ultimoIdCargadoNoticia(todo->listaNoticias) + 1;
                    noticia = crearUnaNoticia(idNoticia);
                    (todo->listaNoticias) = agregarAlFinalNodoNoticia(todo->listaNoticias,crearNodoNoticia(noticia));

                    salir = 1;
                    x = 30;
                    y = 7;
                    gotoxy(2,27);
                    system("pause");
                    system("cls");

                    break;

                case 8:///eliminar noticias
                    gotoxy(30,10);
                    printf("Ingrese el id de la noticia que desea eliminar:  ");
                    gotoxy(30,12);
                    mostrarCursor();
                    scanf("%i",&idNoticia);
                    ocultarCursor();
                    (todo->listaNoticias) = darDeBajaNoticia(todo->listaNoticias,idNoticia);

                    salir = 1;
                    x = 30;
                    y =7;
                    gotoxy(2,27);
                    system("pause");
                    system("cls");

                    break;

                case 9:///ver ciudadanos
                    mostrarArbolCiudadanos(todo->arbolCiudadanos);

                    salir = 1;
                    x = 30;
                    y = 7;
                    printf("\n");
                    system("pause");
                    system("cls");

                    break;

                case 10:///dar de baja ciudadano
                    gotoxy(30,10);
                    printf("Ingrese el DNI del ciudadano que desea dar de baja:  ");
                    gotoxy(30,12);
                    mostrarCursor();
                    scanf("%i",&dni);
                    ocultarCursor();

                    (todo->arbolCiudadanos) = darDeBajaCiudadano(todo->arbolCiudadanos,dni);

                    salir = 1;
                    x = 30;
                    y = 7;
                    gotoxy(2,27);
                    system("pause");
                    system("cls");

                    break;

                case 11:///ver empresas
                    mostrarEmpresas(todo->arbolEmpresa);

                    salir = 1;
                    x = 30;
                    y = 7;

                    printf("\n");

                    system("pause");
                    system("cls");
                    break;

                case 12:
                    ///dar de baja empresa
                    gotoxy(30,10);
                    printf("Ingrese el CUIT de la empresa que quiere dar de baja:  ");
                    gotoxy(30,12);
                    mostrarCursor();
                    scanf("%i",&cuit);
                    ocultarCursor();

                    (todo->arbolEmpresa) = darDeBajaEmpresa(todo->arbolEmpresa,cuit);
                    salir = 1;
                    x = 30;
                    y = 7;

                    gotoxy(2,27);
                    system("pause");
                    system("cls");
                    break;

                case 13:  ///gestionar residuos
                    (todo->listaResiduos) = subprogramaMenuResiduos(todo->listaResiduos);
                    salir = 1;
                    x = 30;
                    y = 7;

                    gotoxy(2,27);
                    system("pause");
                    system("cls");
                    break;

                case 14: ///ver transacciones anuladas
                    mostrarADLSegunEstado(arreglo,0,todo->listaResiduos);
                    salir = 1;
                    x = 30;
                    y = 7;
                    gotoxy(2,27);
                    system("pause");
                    system("cls");
                    break;

                case 15:  ///ver trans pendientes
                    mostrarADLSegunEstado(arreglo,1,todo->listaResiduos);
                    salir = 1;
                    x = 30;
                    y = 7;
                    gotoxy(2,27);
                    system("pause");
                    system("cls");
                    break;

                case 16: ///ver trans realizadas
                    mostrarADLSegunEstado(arreglo,2,todo->listaResiduos);
                    salir = 1;
                    x = 30;
                    y = 7;
                    gotoxy(2,27);
                    system("pause");
                    system("cls");
                    break;

                }
            }
        }
        while(teclaMov !=ESC && salir != 1);
    } //codigo para salir
    while (teclaMov !=ESC);

    borrarADL(arreglo);
    guardarTodo(*todo);
}

void borrarADL(celda arreglo[])
{

    for(int i=0 ; i<3 ; i++)
    {
        arreglo[i].lista = borrarListaTransacciones(arreglo[i].lista);
    }
}


void mostrarTransaccionesPendientesCiudadano (Todo* todo,  int DNI)
{
    nodoTransaccion* iterador = todo->listaTransacciones;
    while (iterador!= NULL)
    {
        if (iterador->dato.DNI == DNI && iterador->dato.estado==1)
        {
            mostrarUnaTransaccion(iterador->dato, todo->listaResiduos);
        }
        iterador = iterador->sig;
    }
}


void cargarADL(celda arreglo[])
{
    FILE* pArchivo = fopen("Transacciones.bin","rb");
    Transaccion registro;

    if(pArchivo)
    {
        while( fread(&registro,sizeof(Transaccion),1,pArchivo) > 0)
        {
            if(registro.estado == 0) ///cancelado
            {
                arreglo[0].lista = agregarAlFinalNodoTransaccion(arreglo[0].lista,crearNodoTransaccion(registro));

            }
            else if(registro.estado == 1) ///pendiente
            {
                arreglo[1].lista = agregarAlFinalNodoTransaccion(arreglo[1].lista,crearNodoTransaccion(registro));
            }
            else ///entregado
            {
                arreglo[2].lista = agregarAlFinalNodoTransaccion(arreglo[2].lista,crearNodoTransaccion(registro));
            }
        }

        fclose(pArchivo);
    }
}
void inicADL(celda arreglo[])
{
    for(int i=0 ; i<3 ; i++)
    {
        arreglo[i].lista = inicListaTransaciones();
    }
}

void mostrarADLSegunEstado(celda arreglo[],int estado,NodoResiduo* listaResiduos)
{
    nodoTransaccion* iterador;

    if(estado == 0)
    {
        iterador = arreglo[0].lista;
    }
    else if(estado == 1)
    {
        iterador = arreglo[1].lista;
    }
    else
    {
        iterador = arreglo[2].lista;
    }

    while(iterador != NULL)
    {
        mostrarUnaTransaccion(iterador->dato,listaResiduos);
        iterador = iterador->sig;
    }
}


void bajarAdminArchivo(Admin* administrador)
{
    FILE* pArchivo = fopen("Administrador.bin","rb");

    if(pArchivo)
    {
        fread(administrador,sizeof(Admin),1,pArchivo);

        fclose(pArchivo);
    }
}
int logInAdmin(Admin administrador)
{
    int esCorrecto=0,i=0;
    char usuario[60],pass[30],caracter;

    mostrarCursor();
    gotoxy(48,10);
    printf("Usuario:  ");
    fflush(stdin);
    Color(WHITE,BLACK);
    gets(usuario);
    Color(BLACK,WHITE);

    gotoxy(45,12);
    printf("Contrase%ca:  ",164);
    Color(WHITE,BLACK);
    fflush(stdin);
    Color(WHITE,BLACK);

    while(caracter=getch())
    {
        if(caracter==13)
        {
            pass[i]='\0';
            break;
        }
        else if(caracter==8)
        {
            if(i>0)
            {
                i--;
                printf("\b \b");
            }

        }
        else
        {
            printf("*");
            pass[i] = caracter;
            i++;
        }
    }


    Color(BLACK,WHITE);

    ocultarCursor();

    gotoxy(50,19);
    printf("CARGANDO...");

    Color(BLUE,WHITE);
    for(int i=10; i<110; i++)
    {
        gotoxy(i,20);
        printf("%c",176);

    }
    Color(CYAN,CYAN);
    for(int i=10; i<110; i++)
    {
        gotoxy(i,20);
        printf("%c",219);
        Sleep(30);
    }
    Color(BLACK,WHITE);

    if( strcmpi(administrador.usuario,usuario) == 0  && strcmpi(administrador.password,pass) == 0)
    {
        esCorrecto = 1;
    }
    else
    {
        Color(RED,BLACK);
        gotoxy(45,22);
        printf("Usuario o Contrase%ca incorrecta\n",164);
        Color(BLACK,WHITE);
    }

    return esCorrecto;
}
void crearArchivoAdmin()
{
    FILE* pArchivo = fopen("Administrador.bin","wb");
    Admin administrador;

    strcpy(administrador.usuario,"mar");
    strcpy(administrador.password,"2022");

    if(pArchivo)
    {
        fwrite(&administrador,sizeof(Admin),1,pArchivo);

        fclose(pArchivo);
    }

}

void mostrarSeccionNoticias(NodoNoticia* listaNoticias)
{
    NodoNoticia* iterador = listaNoticias;


    while(iterador != NULL && ejecutar)
    {

        mostrarUnaNoticia(iterador->dato,0);
        Sleep(20000);

        if(iterador->siguiente == NULL)  ///para que vuelva a empezar
        {
            iterador = listaNoticias;
        }
        else
        {
            iterador = iterador->siguiente;
        }
    }
}
