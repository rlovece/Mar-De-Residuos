#ifndef EMPRESAS_H_INCLUDED
#define EMPRESAS_H_INCLUDED

///Estructura Empresa
typedef struct
{
    int CUIT;
    char nombre[60];
    char password[30];
    char telefono[30];
    char email[60];
    char direccion[60];
    char paginaWeb[60];
    int	bajaEmpresa;  /// 1 alta, 0 baja
    int retira; /// 1 retira, 0 recibe
    int	esRecicladora; /// 1 recicla
    char horario[60];
    char descripcion[100];
} Empresa;

typedef struct _NodoArbolEmpresa
{
    Empresa dato;
    struct _NodoArbolEmpresa* izq;
    struct _NodoArbolEmpresa* der;
}NodoArbolEmpresa;

///Prototipado Funciones Empresa

NodoArbolEmpresa* bajarEmpresasArchivo(NodoArbolEmpresa*);
NodoArbolEmpresa* inicArbolEmpresa();
NodoArbolEmpresa* crearNodoArbolEmpresa(Empresa);
Empresa crearUnaEmpresa(int); /// recibe el CUIT como parametro
NodoArbolEmpresa* cargarUnaEmpresa(NodoArbolEmpresa*);
NodoArbolEmpresa* insertarNodoArbolEmpresa(NodoArbolEmpresa*,Empresa);
void mostrarUnaEmpresa(Empresa); ///vista empresa
void mostrarEmpresa(Empresa empresa); ///vista admin
void mostrarEmpresas(NodoArbolEmpresa*);	///inOrder
void guardarEmpresas(NodoArbolEmpresa*);
void guardarArbolEmpresa(NodoArbolEmpresa*,FILE*); ///guardo preOrder
NodoArbolEmpresa* validarEmpresa(NodoArbolEmpresa*,int);

NodoArbolEmpresa* modificarDatosEmpresa(NodoArbolEmpresa*,int); ///falta ver caso de modificar el CUIT
void menuModificarDatosEmpresa();
NodoArbolEmpresa* darDeBajaEmpresa(NodoArbolEmpresa*,int);
int passwordEmpresaCorrecta(NodoArbolEmpresa*,char[]);
int logInEmpresa(NodoArbolEmpresa*,int);

void mostrarUnaEmpresaACiudadano (Empresa empresa, int yEmpresa);

NodoArbolEmpresa* darDeBajaEmpresa(NodoArbolEmpresa* arbolEmpresa,int cuit);
NodoArbolEmpresa* darDeAltaEmpresa(NodoArbolEmpresa* arbolEmpresa,int cuit);

void menuEmpresas();
#endif // EMPRESAS_H_INCLUDED
