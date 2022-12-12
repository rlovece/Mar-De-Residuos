#ifndef PREGUNTASFRECUENTES_H_INCLUDED
#define PREGUNTASFRECUENTES_H_INCLUDED

typedef struct
{
    int idPregunta;
    char pregunta[100];
    char respuesta[1000];
    int bajaPregunta; ///1 alta, 0 baja
}PreguntaFrecuente;

typedef struct _NodoPreguntaFrecuente
{
    PreguntaFrecuente dato;
    struct _NodoPreguntaFrecuente* siguiente;
}NodoPreguntaFrecuente;

///Prototipado Funciones Preguntas Frecuentes

NodoPreguntaFrecuente* bajarPreguntasFrecuentesArchivo(NodoPreguntaFrecuente*);
NodoPreguntaFrecuente* agregarAlFinalNodoPreguntaFrecuente(NodoPreguntaFrecuente*,NodoPreguntaFrecuente*);
NodoPreguntaFrecuente* buscarUltimoNodoPreguntaFrecuente(NodoPreguntaFrecuente*);
NodoPreguntaFrecuente* inicListaPreguntasFrecuentes();
NodoPreguntaFrecuente* crearNodoPreguntaFrecuente(PreguntaFrecuente);
PreguntaFrecuente crearUnaPreguntaFrecuente(int);
int ultimoIdCargadoPreguntaFrecuente(NodoPreguntaFrecuente*);

void mostrarUnaPreguntaFrecuente(PreguntaFrecuente,int);
void mostrarPreguntasFrecuentes(NodoPreguntaFrecuente*,int);  ///variable para ver como mostrar las preguntas
void guardarPreguntasFrecuentes(NodoPreguntaFrecuente*);
NodoPreguntaFrecuente* modificarDatosPreguntaFrecuente(NodoPreguntaFrecuente*,int); ///modifica segun el id
void menuModificarDatosPreguntaFrecuente();
NodoPreguntaFrecuente* darDeBajaPreguntaFrecuente(NodoPreguntaFrecuente*,int);
NodoPreguntaFrecuente* validarPreguntaFrecuente(NodoPreguntaFrecuente*,int);

#endif // PREGUNTASFRECUENTES_H_INCLUDED
