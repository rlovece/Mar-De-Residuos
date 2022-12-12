#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "fecha.h"


void valPassword (char password[])
{
    char auxPassword[10];
    mostrarCursor();
    do
    {
        fflush(stdin);
        gets(auxPassword);
        if (strlen(auxPassword)<6)
        {
            printf("Ingrese una contrase%ca valida", 164);
        }
    }
    while (strlen(auxPassword)<6);
    strcpy(password, auxPassword);
    ocultarCursor();
}


void valTelefono (long long int *tel) /// OJO NO LA USO
{
    int flag =0;
    do{
        scanf("%ld", tel);
        if (*tel>10000000 && *tel<9999999999)
        {
            flag=1;
        }
        else
        {
            printf("Ingrese un nro valido: ");
        }
    }while (flag ==0);
}

void valMail (char mail[])
{
    char auxMail[40];
    int flag =0;

    mostrarCursor();

    do
    {
        fflush(stdin);
        gets(auxMail);
        char arroba[] = {"@"};
        char com[] = {".com"};

        if (strstr(auxMail,arroba)!=0 && strstr(auxMail,com)!=0)
        {
            flag=1;
        }
        else
        {
            printf("Ingrese un correo valido: ");
        }
    }while (flag==0);
    strcpy(mail, auxMail);

    ocultarCursor();

//    return mail;
}
