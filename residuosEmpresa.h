#ifndef RESIDUOSEMPRESA_H_INCLUDED
#define RESIDUOSEMPRESA_H_INCLUDED

///Estructura ResiduosEmpresa

typedef struct
{
    int CUIT;
    int idResiduo;
    int bajaResiduoEmpresa; ///1 alta, 0 baja
}ResiduosEmpresa;

typedef struct _NodoResiduosEmpresa
{
    ResiduosEmpresa	dato;
    struct NodoResiduosEmpresa* siguiente;
}NodoResiduosEmpresa;

///Prototipado Funciones NodoResiduoEmpresa

NodoResiduosEmpresa* bajarResiduosEmpresaArchivo(NodoResiduosEmpresa*);
NodoResiduosEmpresa* inicListaResiduosEmpresa();
NodoResiduosEmpresa* crearNodoResiduosEmpresa(ResiduosEmpresa);
ResiduosEmpresa crearUnResiduoEmpresa(int,int);
NodoResiduosEmpresa* subprogramaCrearUnResiduoEmpresa(NodoResiduosEmpresa*,NodoResiduo*,int);
NodoResiduosEmpresa* agregarAlFinalNodoResiduoEmpresa(NodoResiduosEmpresa*,NodoResiduosEmpresa*);
NodoResiduosEmpresa* buscarUltimoNodoResiduoEmpresa(NodoResiduosEmpresa*);
void mostrarResiduosEmpresa(NodoResiduosEmpresa*,NodoResiduo*,int);
void guardarResiduosEmpresa(NodoResiduosEmpresa*);
NodoResiduosEmpresa* subprogramaDarDeBajaResiduoEmpresa(NodoResiduosEmpresa*,NodoResiduo*,int);
NodoResiduosEmpresa* darDeBajaResiduoEmpresa(NodoResiduosEmpresa*,int,int);





#endif // RESIDUOSEMPRESA_H_INCLUDED
