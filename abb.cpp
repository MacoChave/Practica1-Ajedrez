#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "abb.h"

/****************************************
 * CONSTRUCTORES
*****************************************/
NodoArbol::NodoArbol(char *usuario_, int victorias_, int derrotas_)
{
    usuario = new char[sizeof(usuario_)];
    strcpy(usuario, usuario_);
    victorias = victorias_;
    derrotas = derrotas_;
    izquierda = NULL;
    derecha = NULL;
}

ABB::ABB()
{
    nodo = NULL;
}

/****************************************
 * DESTRUCTORES
*****************************************/
NodoArbol::~NodoArbol()
{
    delete[] (usuario);
    usuario = NULL;
    victorias = 0;
    derrotas = 0;
    izquierda = NULL;
    derecha = NULL;
}

ABB::~ABB()
{
    delete(nodo);
}

/****************************************
 * ACCIONES RECURSIVOS PRIVADOS
*****************************************/
void ABB::insertar(NodoArbol *nodo, char *usuario_, int victorias_, int derrotas_)
{
    if (nodo != NULL)
    {
        if (strcmp(nodo->usuario, usuario_) > 0)
        {
            if (nodo->izquierda != NULL)
                insertar(nodo->izquierda, usuario_, victorias_, derrotas_);
            else
                nodo->izquierda = new NodoArbol(usuario_, victorias_, derrotas_);
        }
        else if (strcmp(nodo->usuario, usuario_) < 0)
        {
            if (nodo->derecha != NULL)
                insertar(nodo->derecha, usuario_, victorias_, derrotas_);
            else
                nodo->derecha = new NodoArbol(usuario_, victorias_, derrotas_);
        }
    }
}

NodoArbol *ABB::menores(NodoArbol *actual)
{
    if (actual->izquierda != NULL)
        return menores(actual->izquierda);
    else
        return actual;
}

NodoArbol *ABB::mayores(NodoArbol *actual)
{
    if (actual->derecha != NULL)
        return mayores(actual->derecha);
    else
        return actual;
}

NodoArbol *ABB::buscar(NodoArbol *actual, char *usuario)
{
    if (strcmp(actual->usuario, usuario) > 0)
    {
        if (actual->izquierda != NULL)
            return buscar(actual->izquierda, usuario);
        else
            return NULL;
    }
    else if (strcmp(actual->usuario, usuario) < 0)
    {
        if (actual->derecha != NULL)
            return buscar(actual->derecha, usuario);
        else
            return NULL;
    }
    else
        return actual;
}

NodoArbol *ABB::buscarPadre(NodoArbol *actual, char *usuario)
{
    if (strcmp(actual->usuario, usuario) > 0)
    {
        if (actual->izquierda != NULL)
        {
            if (strcmp(actual->izquierda->usuario, usuario) == 0)
                return actual;
            else
                return buscarPadre(actual->izquierda, usuario);
        }
    }
    else if (strcmp(actual->usuario, usuario) < 0)
    {
        if (actual->derecha != NULL)
        {
            if (strcmp(actual->derecha->usuario, usuario) == 0)
                return actual;
            else
                return buscarPadre(actual->derecha, usuario);
        }
    }
    else
        return NULL;
}

void ABB::eliminarNodoHoja(NodoArbol *actual)
{
    NodoArbol *padre = buscarPadre(nodo, actual->usuario);

    if (padre != NULL)
    {
        if (strcmp(padre->usuario, actual->usuario) > 0)
            padre->izquierda = NULL;
        else
            padre->derecha = NULL;
    }
    else
        nodo = NULL;

    delete(actual);
    actual = NULL;
}

void ABB::eliminarNodoConHijoIzq(NodoArbol *actual)
{
    NodoArbol *mayor = mayores(actual->izquierda);
    NodoArbol *padre = buscarPadre(actual, mayor->usuario);

    strcpy(actual->usuario, mayor->usuario);
    actual->victorias = mayor->victorias;
    actual->derrotas = mayor->derrotas;

    if (padre != actual)
        padre->derecha = mayor->izquierda;
    else
        actual->izquierda = mayor->izquierda;

    delete(mayor);
    mayor = NULL;
}

void ABB::eliminarNodoConHijoDch(NodoArbol *actual)
{
    NodoArbol *menor = menores(actual->derecha);
    NodoArbol *padre = buscarPadre(actual, menor->usuario);

    strcpy(actual->usuario, menor->usuario);
    actual->victorias = menor->victorias;
    actual->derrotas = menor->derrotas;

    if (padre != actual)
        padre->izquierda = menor->derecha;
    else
        actual->derecha = menor->derecha;

    delete(menor);
    menor = NULL;
}

/****************************************
 * ACCIONES PUBLICOS
*****************************************/
void ABB::insertar(char *usuario_, int victorias_, int derrotas_)
{
    if (nodo != NULL)
    {
        if (strcmp(nodo->usuario, usuario_) > 0)
        {
            if (nodo->izquierda != NULL)
                insertar(nodo->izquierda, usuario_, victorias_, derrotas_);
            else
                nodo->izquierda = new NodoArbol(usuario_, victorias_, derrotas_);
        }
        else if (strcmp(nodo->usuario, usuario_) < 0)
        {
            if (nodo->derecha != NULL)
                insertar(nodo->derecha, usuario_, victorias_, derrotas_);
            else
                nodo->derecha = new NodoArbol(usuario_, victorias_, derrotas_);
        }
    }
    else
        nodo = new NodoArbol(usuario_, victorias_, derrotas_);
}

void ABB::eliminar(char *usuario_)
{
    NodoArbol *temp = buscar(usuario_);
    if (temp != NULL)
    {
        if (temp->izquierda == NULL && temp->derecha == NULL)
        {
            /* ES NODO HOJA */
            eliminarNodoHoja(temp);
        }
        else
        {
            if (temp->izquierda != NULL)
            {
                /* TIENE UN HIJO IZQUIERDO */
                eliminarNodoConHijoIzq(temp);
            }
            else if (temp->derecha != NULL)
            {
                /* TIENE UN HIJO DERECHO */
                eliminarNodoConHijoDch(temp);
            }
        }
    }
}

NodoArbol *ABB::buscar(char *usuario)
{
    if (strcmp(nodo->usuario, usuario) > 0)
    {
        if (nodo->izquierda != NULL)
            return buscar(nodo->izquierda, usuario);
        else
            return NULL;
    }
    else if (strcmp(nodo->usuario, usuario) < 0)
    {
        if (nodo->derecha != NULL)
            return buscar(nodo->derecha, usuario);
        else
            return NULL;
    }
    else
        return nodo;
}

/**************************************
 * GRAFICAR
**************************************/
void ABB::escribir(char filename[], char texto[], char *modo)
{
    char path[25];
    strcpy(path, "/home/marco/Escritorio/");
    strcat(path, filename);

    FILE *archivo;
    archivo = fopen(path, modo);

    if (!feof(archivo))
    {
        fprintf(archivo, "%s", texto);
        fflush(archivo);
        fclose(archivo);
    }
}

void ABB::graficar(NodoArbol *nodo)
{
    if (nodo != NULL)
    {
        char dot[128];

        strcpy(dot, "\tnd");
        strcat(dot, nodo->usuario);
        strcat(dot, "[label=\"<izq> | ");
        strcat(dot, nodo->usuario);
        strcat(dot, " | <dch>\"];\n");

        escribir("arbol.dot", dot, "a");

        if (nodo->izquierda != NULL)
        {
            strcpy(dot, "\tnd");
            strcat(dot, nodo->usuario);
            strcat(dot, " : izq -> nd");
            strcat(dot, nodo->izquierda->usuario);
            strcat(dot, ";\n");

            escribir("arbol.dot", dot, "a");
        }

        if (nodo->derecha != NULL)
        {
            strcpy(dot, "\tnd");
            strcat(dot, nodo->usuario);
            strcat(dot, " : dch -> nd");
            strcat(dot, nodo->derecha->usuario);
            strcat(dot, ";\n");

            escribir("arbol.dot", dot, "a");
        }

        graficar(nodo->izquierda);
        graficar(nodo->derecha);
    }
}

void ABB::graficar()
{
    char dot[256];

    strcpy(dot, "digraph arbol\n{\n");
    strcat(dot, "\trankdir=TB;\n");
    strcat(dot, "\tnode [shape=record]\n");

    escribir("arbol.dot", dot, "w");
    strcpy(dot, "");

    graficar(nodo);

    escribir("arbol.dot", "}", "a");

    system("dot -Tpng /home/marco/Escritorio/arbol.dot -o /home/marco/Escritorio/arbol.png");
}
