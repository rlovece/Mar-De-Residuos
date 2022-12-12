#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

typedef struct
{
    int dia;
    int mes;
    int anio;
} fecha;

fecha cargarFecha ();
void mostrarFecha (fecha fecha);

#endif // FECHA_H_INCLUDED
