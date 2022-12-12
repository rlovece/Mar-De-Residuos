#include <stdio.h>
#include <stdlib.h>
#include "fecha.h"

const int anio_actual = 2022;

fecha cargarFecha ()
/// carga un dato de tipo fecha
{
    int aux, flag=0;
    fecha fecha;
    do
    {
        printf("a%co (xxxx): ",164);
        scanf("%i", &aux);
        if (aux>=1930 && aux<=2022)
        {
            fecha.anio=aux;
            flag=1;
        }
        else
        {
            printf("A%co invalido, por favor vuelva a ingresar \n", 164);
        }
    }
    while (flag==0);
    flag=0;
    do
    {
        printf("mes (xx): ");
        scanf("%i", &aux);
        if (aux>0 && aux<=12)
        {
            fecha.mes=aux;
            flag=1;
        }
        else
        {
            printf("N%cmero de mes invalido, por favor vuelva a ingresar \n", 163);
        }
    }
    while (flag==0);
    flag=0;
    do
    {
        printf("d%ca (xx): ",161);
        scanf("%i", &aux);
        if ((fecha.mes==1 || fecha.mes==3 || fecha.mes==5 || fecha.mes==7 || fecha.mes==8 || fecha.mes==10 || fecha.mes==12)&& (aux>0 && aux<=31))
        {
            fecha.dia=aux;
            flag=1;
        }
        else if ((fecha.mes==4 || fecha.mes==6 || fecha.mes==9 || fecha.mes==11) && (aux>0 && aux<=30))
        {
            fecha.dia=aux;
            flag=1;
        }
        else if ((fecha.anio%4==0) && (aux>0 && aux<=29))
        {
         fecha.dia=aux;
            flag=1;
        }
        else if (aux>0 && aux<=28)
        {
                     fecha.dia=aux;
            flag=1;
        }
        else
        {
            printf("N%cmero de d%ca invalido, por favor vuelva a ingresar \n", 163, 161);
        }
    }while (flag==0);

    return fecha;
}
void mostrarFecha (fecha fecha)
/// muestra por pantalla un dato de tipo fecha
{
    printf("%i/%i/%i ", fecha.dia, fecha.mes, fecha.anio);
}
