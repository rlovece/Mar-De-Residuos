#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "estilo.h"
#include "Ciudadado.h"
#include "fecha.h"
#include "validaciones.h"
#include "menus.h"

#define N 100
#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

Ciudadano cargarUnCiudadano (int DNI)
{
    char arroba[] = {"@"};
    char com[] = {".com"};
    int flag =0;
    Ciudadano nuevo;
    nuevo.DNICiudadano = DNI;
    mostrarCursor();
    printf("\n Ingrese Nombre y Apellido: ");
    fflush(stdin);
    gets(nuevo.nombreYApellido);
    printf("\n Correo electronico: ");
    do
    {
        fflush(stdin);
        gets(nuevo.email);

        if (strstr(nuevo.email,arroba)!=0 && strstr(nuevo.email,com)!=0)
        {
            flag=1;
        }
        else
        {
            printf("Ingrese un correo valido: ");
        }
    }
    while (flag==0);
    printf("\n Domicilio: ");
    fflush(stdin);
    gets(nuevo.direccion);
    printf("\n Password (entre 6 y 10 caracteres): ");
    valPassword(nuevo.password);
    printf("\n Telefono (sin 0 ni 15): ");
    fflush(stdin);
    gets(nuevo.telefono);
    printf("\n Fecha de Nacimiento: ");
    nuevo.fechaNacimiento = cargarFecha();
    nuevo.bajaCiudadano=1;
    ocultarCursor();
    mostrarCiudadano (nuevo);
    return nuevo;
}

void mostrarCiudadano(Ciudadano aMostrar)
{
    printf("\n DNI: %i", aMostrar.DNICiudadano);
    printf("\n Nombre y Apellido: %s", aMostrar.nombreYApellido);
    printf("\n Correo Electronico: %s", aMostrar.email);
    printf("\n Telefono: %s", aMostrar.telefono);
    printf("\n Nombre y Apellido: %s", aMostrar.direccion);
    printf("\n Fecha Nac: ");
    mostrarFecha(aMostrar.fechaNacimiento);
}

void unCiudadanoAlArchivo (FILE* archi, Ciudadano nuevo)
{
    fwrite(&nuevo, sizeof(Ciudadano), 1, archi);
}

nodoCiudadano* inicArbolCiudadanos ()
{
    return NULL;
}

nodoCiudadano* crearNodoCiudadano (Ciudadano dato)
{
    nodoCiudadano* aux = (nodoCiudadano*) malloc(sizeof( nodoCiudadano ));
    aux->dato=dato;
    aux->der=NULL;
    aux->izq=NULL;
    return aux;
}

nodoCiudadano * insertar (nodoCiudadano* arbol, Ciudadano nuevo)
{
    if(arbol==NULL)
        arbol = crearNodoCiudadano(nuevo);
    else
    {
        if(nuevo.DNICiudadano > arbol->dato.DNICiudadano)
            arbol->der = insertar(arbol->der, nuevo);
        else
            arbol->izq = insertar(arbol->izq, nuevo);
    }
    return arbol;
}

nodoCiudadano* buscarCiudadano (nodoCiudadano* arbol, int DNI)
{
    nodoCiudadano* rta= inicArbolCiudadanos();
    if(arbol!=NULL)
    {
        if(DNI == arbol->dato.DNICiudadano)
        {
            rta = arbol;
        }
        else if(DNI > arbol->dato.DNICiudadano)
        {
            rta = buscarCiudadano(arbol->der, DNI);
        }
        else
        {
            rta = buscarCiudadano(arbol->izq, DNI);
        }

    }
    return rta;
}

int validarCiudadano (nodoCiudadano* arbol, int DNI)
{
    int flag =0; /// no encontrado
    if (buscarCiudadano(arbol, DNI))
    {
        flag=1;
    }
    return flag;
}

nodoCiudadano* bajarCiudadanosArchivo (nodoCiudadano* arbolCiudadanos)
{
    Ciudadano aux;
    FILE* pArchi = fopen (ARCHIVO_CIUDADANOS, "rb");
    if (pArchi)
    {
        while(fread(&aux, sizeof(Ciudadano),1, pArchi)>0)
        {
            arbolCiudadanos = insertar(arbolCiudadanos, aux);
            mostrarCiudadano (aux);
        }
        fclose(pArchi);
    }

    return arbolCiudadanos;
}

Ciudadano modificarCiudadano (Ciudadano aModificar)
{
    /// PARA MOVER FLECHA
    char icono;
    int x, y, teclaMov, ingresoSubmenu,salir;
    x = 5;
    y = 14;
    ingresoSubmenu = 1;
    salir=0;
    icono = 16;
    gotoxy(0,0); /// FIN MOVER



    do
    {


        mostrarCiudadano(aModificar);

        menuModificarCiudadano();

        gotoxy(5, 14);
        printf("%c", icono);

        ingresoSubmenu = 1;
        salir = 0;
        gotoxy (5, 12);




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

            else if (teclaMov == DOWN && y<19)
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
                    mostrarCursor();
                    printf("\n Ingrese Nombre y Apellido: ");
                    fflush(stdin);
                    gets(aModificar.nombreYApellido);
                    ocultarCursor();
                    x = 5;
                    y = 14;
                    gotoxy(2,27);
                    system("pause");
//                    system("cls");

                    break;

                case 2:
                    gotoxy (5, 25);
                    mostrarCursor();
                    printf("\n Correo electronico: ");
                    valMail(aModificar.email);
                    ocultarCursor();
                    x = 5;
                    y = 14;
                    gotoxy(2,27);
                    system("pause");


                    break;

                case 3:
                    gotoxy (5, 25);
                    mostrarCursor();
                    printf("\n Domicilio: ");
                    fflush(stdin);
                    gets(aModificar.direccion);
                    ocultarCursor();
                    x = 5;
                    y = 14;
                    gotoxy(2,27);
                    system("pause");


                    break;

                case 4:
                    gotoxy (5, 25);
                    mostrarCursor();
                    printf("\n Password (entre 6 y 10 caracteres): ");
                    valPassword(aModificar.password);
                    ocultarCursor();
                    x = 5;
                    y = 14;
                    gotoxy(2,27);
                    system("pause");


                    break;

                case 5:
                    gotoxy (5, 25);
                    mostrarCursor();
                    printf("\n Telefono (sin 0 ni 15): ");
                    fflush(stdin);
                    gets(aModificar.telefono);
                    ocultarCursor();
                    x = 5;
                    y = 14;
                    gotoxy(2,27);
                    system("pause");


                    break;

                case 6:
                    gotoxy (5, 25);
                    mostrarCursor();
                    printf("\n Fecha de Nacimiento: ");
                    aModificar.fechaNacimiento = cargarFecha();
                    ocultarCursor();
                    x = 5;
                    y = 14;
                    gotoxy(2,27);
                    system("pause");


                    break;
                }
            }
        }
        while(teclaMov !=ESC && salir != 1);
    } //codigo para salir
    while (teclaMov !=ESC);

    return aModificar;
}

void guardarCiudadanos (nodoCiudadano* arbolCiudadano)
{
    FILE* pArchivo = fopen(ARCHIVO_CIUDADANOS,"wb");

    if(pArchivo)
    {
        guardarArbolCiudadano (arbolCiudadano,pArchivo);

        fclose(pArchivo);
    }
}

void menuModificarCiudadano ()
{

    gotoxy(2,11);
    printf("--------------------------------------------------");
    gotoxy(2,12);
    printf("  Si desea modificar algun dato, elija la opcion ");
    gotoxy(2,13);
    printf("--------------------------------------------------");
    gotoxy(2,14);
    printf("\t     Nombre y Apellido");
    gotoxy(2,15);
    printf("\t     Correo Electronico");
    gotoxy(2,16);
    printf("\t     Domicilio");
    gotoxy(2,17);
    printf("\t     Contrase%ca", 164);
    gotoxy(2,18);
    printf("\t     Telefono");
    gotoxy(2,19);
    printf("\t     Fecha de Nacimiento");
    gotoxy(2,20);
    printf(" No es posible modificar el DNI. En caso de error \n");
    gotoxy(2,21);
    printf(" por correo electronico: marderesiduos@mdp.com.ar\n");
    gotoxy(2,22);
    printf("-------------------------------------------------\n");
        gotoxy(2,24);
        printf("\tPara salir presione la tecla Esc\n\n");

}

void guardarArbolCiudadano (nodoCiudadano* arbolCiudadano,FILE* pArchivo) ///guardo preOrder
{
    if(arbolCiudadano)
    {
        fwrite(&(arbolCiudadano->dato),sizeof(Ciudadano),1,pArchivo);
        guardarArbolCiudadano(arbolCiudadano->izq,pArchivo);
        guardarArbolCiudadano(arbolCiudadano->der,pArchivo);
    }
}

int loginCiudadano (nodoCiudadano* arbolCiudadanos, int DNI)
{
    int acceso=0,i=0;
    char pass[30],caracter;
    char respuesta;
    nodoCiudadano* nodoBuscado = inicArbolCiudadanos();

    nodoBuscado = buscarCiudadano (arbolCiudadanos, DNI);

    if(nodoBuscado!= NULL && nodoBuscado->dato.bajaCiudadano == 1)
    {

        mostrarCursor();
        gotoxy(43,12);
        printf("Contrase%ca:  ",164);
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

        if(passwordCiudadanoCorrecta(nodoBuscado,pass))
        {
            acceso = 1;
        }
        else
        {
            Color (RED, BLACK);
            gotoxy(45,22);
            printf("Contrase%ca incorrecta \n\n\n",164);
            Color (BLACK, WHITE);
        }

    }
    else if (nodoBuscado!= NULL && nodoBuscado->dato.bajaCiudadano == 0)
    {
        Color (RED, BLACK);
        gotoxy (30,13);
        printf(" DNI dado de baja. Desea activarlo nuevamente? s/n \n");
        Color (BLACK, WHITE);
        fflush(stdin);
        scanf("%c",&respuesta);
        if(respuesta == 's' || respuesta == 'S')
        {
            arbolCiudadanos = darDeAltaCiudadano (arbolCiudadanos, DNI);
        }
    }
    else
    {
        Color(RED,BLACK);
        gotoxy(45,22);
        printf("El DNI ingresado no existe\n",164);
        Color(BLACK,WHITE);
    }


    return acceso;
}

int passwordCiudadanoCorrecta(nodoCiudadano* nodoBuscado, char pass[])
{
    int esCorrecto=0;

    if(strcmpi(nodoBuscado->dato.password, pass) == 0 )
    {
        esCorrecto = 1;
    }

    return esCorrecto;
}

void mostrarArbolCiudadanos (nodoCiudadano* arbolCiudadanos)
{
    if(arbolCiudadanos != NULL)
    {
        mostrarArbolCiudadanos(arbolCiudadanos->izq);
        mostrarCiudadano(arbolCiudadanos->dato);
        mostrarArbolCiudadanos(arbolCiudadanos->der);
    }
}

nodoCiudadano* darDeBajaCiudadano (nodoCiudadano* arbolCiudadanos, int DNI)
{
    nodoCiudadano* nodoBuscado = buscarCiudadano(arbolCiudadanos, DNI);

    if(nodoBuscado != NULL)
    {
        nodoBuscado->dato.bajaCiudadano = 0; ///lo doy de baja
    }

    return arbolCiudadanos;
}

nodoCiudadano* darDeAltaCiudadano (nodoCiudadano* arbolCiudadanos, int DNI)
{
    nodoCiudadano* nodoBuscado = buscarCiudadano(arbolCiudadanos, DNI);

    if(nodoBuscado != NULL)
    {
        nodoBuscado->dato.bajaCiudadano = 1; ///lo doy de alta
    }

    return arbolCiudadanos;
}
void menuCiudadano ()
{

    gotoxy(7,4);
    printf("--------------------------------------------------");
    gotoxy(7,5);
    printf("             GRACIAS POR SER PARTE ");
    gotoxy(7,6);
    printf("--------------------------------------------------");
    gotoxy(7,7);
    printf("\t     Verificar datos de contacto");
    gotoxy(7,8);
    printf("\t     Coordinar transaccion de materiales");
    gotoxy(7,9);
    printf("\t     Ver transacciones pendientes");
    gotoxy(7,10);
    printf("\t     Solicitar baja");
    gotoxy(7,11);
    printf("--------------------------------------------------\n");
    gotoxy(7,14);
    printf("\tPara salir presione la tecla Esc\n\n");
}
