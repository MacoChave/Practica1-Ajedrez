#ifndef ABB_H
#define ABB_H

class NodoArbol
{
public:
    NodoArbol(char *usuario_, int victorias_, int derrotas_);
    ~NodoArbol();
    char *usuario;
    int victorias;
    int derrotas;
    NodoArbol *izquierda;
    NodoArbol *derecha;
};

class ABB
{
    void insertar(NodoArbol *nodo, char *usuario_, int victorias_, int derrotas_);
    void eliminar(NodoArbol *nodo, char *usuario_);
    void graficar(NodoArbol *nodo);
    void escribir(char filename[], char texto[], char *modo);
    NodoArbol *menores(NodoArbol *actual);
    NodoArbol *mayores(NodoArbol *actual);
    NodoArbol *buscar(NodoArbol *actual, char *usuario);
    NodoArbol *buscarPadre(NodoArbol *actual, char *usuario);
public:
    ABB();
    ~ABB();
    NodoArbol *nodo;

    void insertar(char *usuario_, int victorias_, int derrotas_);
    void eliminar(char *usuario_);
    NodoArbol *buscar(char *usuario);
    void graficar();
};

#endif // ABB_H
