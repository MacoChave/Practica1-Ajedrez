#ifndef LISTA_H
#define LISTA_H

class NodoLista
{
public:
    NodoLista(char *user, int victorias);
    ~NodoLista();
    char *usuario;
    int victoria;
    NodoLista *anterior;
    NodoLista *siguiente;
};

class Lista
{
    void escribir(char filename[], char texto[], char *tipo);
public:
    Lista();
    ~Lista();
    NodoLista *primero;
    void agregar(char *user, int victorias);
    void graficar();
};

#endif // LISTA_H
