#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "estilo.h"
#include "empresas.h"

#include "estilo.h"
#include "residuos.h"
#include "validaciones.h"
#include "Transacciones.h"

/// #include "residuosEmpresa.h"

#define N 100
#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

#define ARCHIVO_EMPRESAS "Empresas.bin"

///Implementacion Funciones Empresa

NodoArbolEmpresa* bajarEmpresasArchivo(NodoArbolEmpresa* arbolEmpresa)
{
    FILE* pArchivo = fopen(ARCHIVO_EMPRESAS,"rb");
    Empresa empresa;

    if(pArchivo != NULL)
    {
        while(fread(&empresa,sizeof(Empresa),1,pArchivo) > 0)
        {
            arbolEmpresa = insertarNodoArbolEmpresa(arbolEmpresa,empresa);
        }

        fclose(pArchivo);
    }
    else
    {
        printf("\nNo se pudo abrir el archivo Empresas\n");
    }

    return arbolEmpresa;
}

NodoArbolEmpresa* inicArbolEmpresa()
{
    return NULL;
}

NodoArbolEmpresa* crearNodoArbolEmpresa(Empresa empresa)
{
    NodoArbolEmpresa* nuevoNodo = malloc(sizeof(NodoArbolEmpresa));

    nuevoNodo->dato = empresa;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;

    return nuevoNodo;
}

NodoArbolEmpresa* insertarNodoArbolEmpresa(NodoArbolEmpresa* arbolEmpresa,Empresa empresa)
{
    if(arbolEmpresa == NULL)
    {
        arbolEmpresa = crearNodoArbolEmpresa(empresa);
    }
    else
    {
        if(empresa.CUIT < arbolEmpresa->dato.CUIT)
        {
            arbolEmpresa->izq = insertarNodoArbolEmpresa(arbolEmpresa->izq,empresa);
        }
        else
        {
            arbolEmpresa->der = insertarNodoArbolEmpresa(arbolEmpresa->der,empresa);
        }
    }

    return arbolEmpresa;
}
void mostrarUnaEmpresa(Empresa empresa)
{
    int x=10,y=2;
    if(empresa.bajaEmpresa == 1)
    {
        gotoxy(x,y);
        printf("CUIT: %i",empresa.CUIT);
        y++;
        gotoxy(x,y);
        printf("Nombre: %s",empresa.nombre);
        y++;
        char password[30];
        gotoxy(x,y);
        printf("Telefono: %s",empresa.telefono);
        y++;
        gotoxy(x,y);
        printf("Mail: %s",empresa.email);
        y++;
        gotoxy(x,y);
        printf("Direccion: %s",empresa.direccion);
        y++;
        gotoxy(x,y);
        printf("Pagina web: %s",empresa.paginaWeb);
        y++;
        gotoxy(x,y);
        printf("Horarios de Atencion: %s",empresa.horario);
        y++;
        gotoxy(x+2,y);
        printf("Realiza retiros: ");
        y++;
        if(empresa.retira == 1)
        {
            printf("SI");
        }
        else
        {
            printf("NO");
        }
        gotoxy(x+2,y);
        y++;
        if(empresa.esRecicladora == 1)
        {
            printf("La empresa recicla");
        }
        else
        {
            printf("La empresa acopia");
        }
        gotoxy(x,y);
        printf(">> %s\n\n",empresa.descripcion);

    }

}
void mostrarEmpresa(Empresa empresa)
{

        printf("\n-----------------------------------------------------------------------------------------------------------------\n");
        printf("CUIT: %i",empresa.CUIT);

        printf("\nNombre: %s",empresa.nombre);


        printf("\nTelefono: %s",empresa.telefono);

        printf("\nMail: %s",empresa.email);

        printf("\nDireccion: %s",empresa.direccion);

        printf("\nPagina web: %s",empresa.paginaWeb);

        printf("\nHorarios de Atencion: %s",empresa.horario);

        printf("\nRealiza retiros: ");

        if(empresa.retira == 1)
        {
            printf("SI");
        }
        else
        {
            printf("NO");
        }

        if(empresa.esRecicladora == 1)
        {
            printf("\nLa empresa recicla");
        }
        else
        {
            printf("\nLa empresa acopia");
        }

        printf("\n>> %s",empresa.descripcion);
        printf("\nEstado: ");
        if(empresa.bajaEmpresa == 1)
        {
            printf("Alta");
        }
        else
        {
            printf("Baja");
        }
        printf("\n-----------------------------------------------------------------------------------------------------------------\n");




}


void mostrarUnaEmpresaACiudadano (Empresa empresa, int yEmpresa)
{

    gotoxy (2, yEmpresa);
    printf("| %i  ",empresa.CUIT);
    gotoxy (2, yEmpresa+1);
    printf("|   ");
    gotoxy (2, yEmpresa+2);
    printf("|   ");
    gotoxy (10, yEmpresa);
    printf("| %s  ",empresa.nombre);
    gotoxy(10, yEmpresa+1);
    printf("| %s  ",empresa.direccion);
    gotoxy(10, yEmpresa+2);
    printf("| %s  ",empresa.horario);
    gotoxy(48, yEmpresa);
    if(empresa.retira == 1)
    {
        printf("|   SI  ");
    }
    else
    {
        printf("|   NO ");
    }

    gotoxy(48, yEmpresa+1);
    printf("|   ");
    gotoxy(48, yEmpresa+2);
    printf("|   ");
    gotoxy(57, yEmpresa);
    printf("|");
    gotoxy(57, yEmpresa+1);
    printf("|");
    gotoxy(57, yEmpresa+2);
    printf("|");
    gotoxy(2,yEmpresa+3);
    printf("--------------------------------------------------------");
}

void mostrarEmpresas(NodoArbolEmpresa* arbolEmpresa)	///inOrder
{
    if(arbolEmpresa != NULL)
    {
        mostrarEmpresas(arbolEmpresa->izq);
        mostrarEmpresa(arbolEmpresa->dato);
        mostrarEmpresas(arbolEmpresa->der);
    }
}
void guardarEmpresas(NodoArbolEmpresa* arbolEmpresa)
{
    FILE* pArhcivo = fopen(ARCHIVO_EMPRESAS,"wb");

    if(pArhcivo != NULL)
    {
        guardarArbolEmpresa(arbolEmpresa,pArhcivo);

        fclose(pArhcivo);
    }
    else
    {
        printf("\nNo se pudo abrir el archivo Empresas para su escritura\n");
    }
}

void guardarArbolEmpresa(NodoArbolEmpresa* arbolEmpresa,FILE* pArchivo) ///guardo preOrder
{
    if(arbolEmpresa != NULL)
    {
        fwrite(&(arbolEmpresa->dato),sizeof(Empresa),1,pArchivo);
        guardarArbolEmpresa(arbolEmpresa->izq,pArchivo);
        guardarArbolEmpresa(arbolEmpresa->der,pArchivo);
    }
}
NodoArbolEmpresa* validarEmpresa(NodoArbolEmpresa* arbolEmpresa,int cuit)
{
    NodoArbolEmpresa* nodoBuscado = inicArbolEmpresa();

    if(arbolEmpresa != NULL)
    {
        if(arbolEmpresa->dato.CUIT == cuit)
        {
            nodoBuscado = arbolEmpresa;
        }
        else
        {
            nodoBuscado = validarEmpresa(arbolEmpresa->izq,cuit);

            if(nodoBuscado== NULL)
            {
                nodoBuscado = validarEmpresa(arbolEmpresa->der,cuit);
            }
        }
    }

    return nodoBuscado;
}

Empresa crearUnaEmpresa(int cuit)
{
    char opcion;

    Empresa empresa;

    empresa.CUIT = cuit;

    mostrarCursor();

    printf("Ingrese el nombre de la empresa:  ");
    fflush(stdin);
    gets(empresa.nombre);

    printf("Ingrese una contrase%ca:  ",164);
    fflush(stdin);
    gets(empresa.password);

    printf("Ingrese el telefono:  ");
    fflush(stdin);
    gets(empresa.telefono);

    printf("Ingrese el mail de la empresa:  ");
    fflush(stdin);
    gets(empresa.email);

    printf("Ingrese la direccion:  ");
    fflush(stdin);
    gets(empresa.direccion);

    printf("Ingrese la pagina web:  ");
    fflush(stdin);
    gets(empresa.paginaWeb);

    printf("Ingrese el horario de atencion:  ");
    fflush(stdin);
    gets(empresa.horario);

    empresa.bajaEmpresa = 1;

    printf("La empresa recicla? s/n ");
    fflush(stdin);
    scanf("%c",&opcion);

    while(opcion != 'n' && opcion != 'N' && opcion != 'S' && opcion != 's')
    {
        printf("\nPor favor ingrese s/n como respuesta: ");
        fflush(stdin);
        scanf("%c",&opcion);
    }

    if(opcion == 's' || opcion == 'S')
    {
        empresa.esRecicladora = 1;
    }
    else
    {
        empresa.esRecicladora = 0;
    }

    printf("La empresa realiza retiros? s/n ");
    fflush(stdin);
    scanf("%c",&opcion);

    while(opcion != 'n' && opcion != 'N' && opcion != 'S' && opcion != 's')
    {
        printf("\nPor favor ingrese s/n como respuesta: ");
        fflush(stdin);
        scanf("%c",&opcion);
    }

    if(opcion == 's' || opcion == 'S')
    {
        empresa.retira = 1;
    }
    else
    {
        empresa.retira = 0;
    }

    printf("Desea agregar una descripcion? s/n ");
    fflush(stdin);
    scanf("%c",&opcion);

    if(opcion == 's' || opcion == 'S')
    {
        printf("\n[Maximo 100 caracteres]\n");
        fflush(stdin);
        gets(empresa.descripcion);
    }

    ocultarCursor();

    return empresa;

}

NodoArbolEmpresa* cargarUnaEmpresa(NodoArbolEmpresa* arbolEmpresa)
{
    int cuit;
    NodoArbolEmpresa* nodoBuscado = inicArbolEmpresa;

    mostrarCursor();

    printf("\nIngrese el CUIT de la empresa:  ");
    scanf("%i",&cuit);

    ocultarCursor();

//    printf("\nLlega hasta aca?");
//    system("cls");

    nodoBuscado = validarEmpresa(arbolEmpresa,cuit);

    if(nodoBuscado == NULL)  /// la empresa no existe
    {
        arbolEmpresa = insertarNodoArbolEmpresa(arbolEmpresa,crearUnaEmpresa(cuit));
    }
    else
    {
        printf("\nEl CUIT ingresado ya existe\n");
        mostrarUnaEmpresa(nodoBuscado->dato);
    }


    return arbolEmpresa;
}

NodoArbolEmpresa* modificarDatosEmpresa(NodoArbolEmpresa* arbolEmpresa,int cuit)
{
    NodoArbolEmpresa* nodoBuscado;
    char respuesta;

    nodoBuscado = validarEmpresa(arbolEmpresa,cuit);

    system("cls");

    char icono, correrPrograma;
    int x, y, teclaMov, ingresoSubmenu,salir;
    x = 10;
    y = 15;
    ingresoSubmenu = 1;
    salir=0;
    icono = 16;

    gotoxy(0,0);


    ///codigo para seleccionar conflechas y pulsar enter

    if(nodoBuscado != NULL)
    {
        do
        {

            mostrarUnaEmpresa(nodoBuscado->dato);

            menuModificarDatosEmpresa();


            gotoxy(10, 15);
            printf("%c", icono);

            ingresoSubmenu = 1;
            salir = 0;
            do
            {
                teclaMov = getch();

                if (teclaMov == UP && y>15)
                {

                    gotoxy(x, y);
                    printf(" ");
                    y--;
                    gotoxy(x, y);
                    printf("%c", icono);
                    ingresoSubmenu--;

                }

                else if (teclaMov == DOWN && y<24)
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
                        mostrarCursor();
                        printf("Ingrese el nuevo nombre: ");
                        fflush(stdin);
                        gets(nodoBuscado->dato.nombre);
                        ocultarCursor();

                        salir = 1;
                        x = 10;
                        y = 17;
                        system("cls");
                        break;

                    case 2:
                        printf("Ingrese la nueva contrase%ca: ",164);
                        mostrarCursor();
                        fflush(stdin);
                        gets(nodoBuscado->dato.password);
                        ocultarCursor();

                        salir = 1;
                        x = 10;
                        y = 17;
                        system("cls");


                        break;

                    case 3:
                        printf("Ingrese el nuevo telefono: ");
                        mostrarCursor();
                        fflush(stdin);
                        gets(nodoBuscado->dato.telefono);
                        ocultarCursor();


                        salir = 1;
                        x = 10;
                        y = 19;
                        system("cls");

                        break;

                    case 4:
                        printf("Ingrese el nuevo email: ");
                        mostrarCursor();
                        fflush(stdin);
                        gets(nodoBuscado->dato.email);
                        ocultarCursor();
                        salir = 1;
                        x = 10;
                        y = 19;
                        system("cls");

                        break;

                    case 5:
                        printf("Ingrese la nueva direccion:  ");
                        mostrarCursor();
                        fflush(stdin);
                        gets(nodoBuscado->dato.direccion);
                        ocultarCursor();
                        salir = 1;
                        x = 10;
                        y = 19;
                        system("cls");

                        break;
                    case 6:
                        printf("Ingrese la nueva pagina web: ");
                        mostrarCursor();
                        fflush(stdin);
                        gets(nodoBuscado->dato.paginaWeb);
                        ocultarCursor();
                        salir = 1;
                        x = 10;
                        y = 19;
                        system("cls");

                        break;
                    case 7:
                        printf("Ingrese el nuevo horario: ");
                        mostrarCursor();
                        fflush(stdin);
                        gets(nodoBuscado->dato.horario);
                        ocultarCursor();
                        salir = 1;
                        x = 10;
                        y = 19;
                        system("cls");

                        break;
                    case 8:
                        printf("Realiza retiros? s/n ");
                        mostrarCursor();
                        fflush(stdin);
                        scanf("%c",&respuesta);

                        while(respuesta != 'n' && respuesta != 'N' && respuesta != 'S' && respuesta != 's')
                        {
                            printf("\nPor favor ingrese s/n como respuesta: ");
                            fflush(stdin);
                            scanf("%c",&respuesta);
                        }

                        if(respuesta == 's' || respuesta == 'S')
                        {
                            nodoBuscado->dato.retira = 1;
                        }
                        else
                        {
                            nodoBuscado->dato.retira = 0;
                        }

                        ocultarCursor();
                        salir = 1;
                        x = 10;
                        y = 19;
                        system("cls");

                        break;
                    case 9:
                        printf("La empresa es recicladora? s/n ");
                        mostrarCursor();
                        fflush(stdin);
                        scanf("%c",&respuesta);

                        while(respuesta != 'n' && respuesta != 'N' && respuesta != 'S' && respuesta != 's')
                        {
                            printf("\nPor favor ingrese s/n como respuesta: ");
                            fflush(stdin);
                            scanf("%c",&respuesta);
                        }

                        if(respuesta == 's' || respuesta == 'S')
                        {
                            nodoBuscado->dato.esRecicladora = 1;
                        }
                        else
                        {
                            nodoBuscado->dato.esRecicladora = 0;
                        }

                        ocultarCursor();
                        salir = 1;
                        x = 10;
                        y = 19;
                        system("cls");

                        break;

                    case 10:
                        printf("Ingrese la nueva descripicon:  ");
                        mostrarCursor();
                        fflush(stdin);
                        gets(nodoBuscado->dato.descripcion);
                        ocultarCursor();
                        salir = 1;
                        x = 10;
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
    else
    {
        printf("\nEl CUIT ingresado no existe\n");
    }

    return arbolEmpresa;
}
void menuModificarDatosEmpresa()
{
    ///si modifico el CUIT tengo que borrar ese nodo y crear uno nuevo

    int x=10,y=13;
    gotoxy(x,y);
    printf("--------------------------------------------------");
    y++;
    gotoxy(x,y);
    printf("  Si desea modificar algun dato, elija la opcion ");
    y++;
    gotoxy(x,y);
    printf("--------------------------------------------------");
    y++;
    gotoxy(x,y);
    printf("\tNombre");
    y++;
    gotoxy(x,y);
    printf("\tContrase%ca",164);
    y++;
    gotoxy(x,y);
    printf("\tTelefono");
    y++;
    gotoxy(x,y);
    printf("\tEmail");
    y++;
    gotoxy(x,y);
    printf("\tDireccion");
    y++;
    gotoxy(x,y);
    printf("\tPagina web");
    y++;
    gotoxy(x,y);
    printf("\tHorario");
    y++;
    gotoxy(x,y);
    printf("\tRealiza retiros");
    y++;
    gotoxy(x,y);
    printf("\tEs recicladora");
    y++;
    gotoxy(x,y);
    printf("\tDescripcion");
    y++;
    gotoxy(x,y);
    printf("--------------------------------------------------");
    y+=2;
    gotoxy(x,y);
    printf("\tPara salir presione la tecla Esc\n\n");


}

NodoArbolEmpresa* darDeBajaEmpresa(NodoArbolEmpresa* arbolEmpresa,int cuit)
{
    NodoArbolEmpresa* nodoBuscadoEmpresa = validarEmpresa(arbolEmpresa,cuit);

    if(nodoBuscadoEmpresa != NULL)
    {
        nodoBuscadoEmpresa->dato.bajaEmpresa = 0; ///lo doy de baja
        gotoxy(30,10);
        printf("Baja Exitosa!");
        getch();
    }
    else
    {
        printf("\nEl CUIT ingresado no se encuentra en la lista");
    }

    return arbolEmpresa;
}

NodoArbolEmpresa* darDeAltaEmpresa(NodoArbolEmpresa* arbolEmpresa,int cuit)
{
    NodoArbolEmpresa* nodoBuscadoEmpresa = validarEmpresa(arbolEmpresa,cuit);

    if(nodoBuscadoEmpresa != NULL)
    {
        nodoBuscadoEmpresa->dato.bajaEmpresa = 1; ///lo doy de alta
    }

    return arbolEmpresa;
}

int passwordEmpresaCorrecta(NodoArbolEmpresa* nodoEmpresa,char pass[])
{
    int esCorrecto=0;

    if(strcmpi(nodoEmpresa->dato.password,pass) == 0 )
    {
        esCorrecto = 1;
    }

    return esCorrecto;
}
int logInEmpresa(NodoArbolEmpresa* arbolEmpresa, int cuit)
{
    int acceso=0,i=0;
    char pass[30],caracter, respuesta;
    NodoArbolEmpresa* nodoBuscado = inicArbolEmpresa();

    nodoBuscado = validarEmpresa(arbolEmpresa,cuit);

    if(nodoBuscado != NULL && nodoBuscado->dato.bajaEmpresa == 1) ///verifico que no este dado de baja el usuario
    {

        gotoxy(44,12);
        printf("Contrase%ca:   ",164);
        mostrarCursor();
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
        if(passwordEmpresaCorrecta(nodoBuscado,pass))
        {
            acceso = 1;
        }
        else
        {
            Color(RED,BLACK);
            gotoxy(45,22);
            printf("Contrase%ca incorrecta\n",164);
            Color(BLACK,WHITE);
        }
    }
        else if (nodoBuscado!= NULL && nodoBuscado->dato.bajaEmpresa == 0)
    {
        Color (RED, BLACK);
        gotoxy (30,13);
        printf(" CUIT dado de baja. Desea activarlo nuevamente? s/n \n");
        Color (BLACK, WHITE);
        fflush(stdin);
        scanf("%c",&respuesta);
        if(respuesta == 's' || respuesta == 'S')
        {
            arbolEmpresa = darDeAltaEmpresa (arbolEmpresa, cuit);
        }
    }
    else
    {
        Color(RED,BLACK);
        gotoxy(45,22);
        printf("El CUIT ingresado no existe\n",164);
        Color(BLACK,WHITE);
    }

    return acceso;
}


void menuEmpresas()
{
    gotoxy(30,5);
    printf("--------------------------------------------------");
    gotoxy(30,6);
    printf("             GRACIAS POR SER PARTE ");
    gotoxy(30,7);
    printf("--------------------------------------------------");
    gotoxy(30,8);
    printf("\t     Verificar datos de contacto");
    gotoxy(30,9);
    printf("\t     Ver residuos con los que trabaja");
    gotoxy(30,10);
    printf("\t     Agregar residuos a la empresa");
    gotoxy(30,11);
    printf("\t     Elminar residuo con el que trabaja");
    gotoxy(30,12);
    printf("\t     Ingresar nuevo residuo al sistema");
    gotoxy(30,13);
    printf("\t     Ver retiros pendientes");
    gotoxy(30,14);
    printf("\t     Ver retiros realizados");
    gotoxy(30,15);
    printf("\t     Marcar retiros realizados");
    gotoxy(30,16);
    printf("\t     Solicitar baja");
    gotoxy(30,17);
    printf("--------------------------------------------------\n");
    gotoxy(30,20);
    printf("\tPara salir presione la tecla Esc\n\n");

}
