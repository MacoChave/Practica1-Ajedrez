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
    raiz = NULL;
}

/****************************************
 * DESTRUCTORES
*****************************************/
NodoArbol::~NodoArbol()
{
    delete[] (usuario);
    victorias = 0;
    derrotas = 0;
    izquierda = NULL;
    derecha = NULL;
}

ABB::~ABB()
{
    delete(raiz);
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

void ABB::eliminar(NodoArbol *nodo, char *usuario_)
{

}

/****************************************
 * ACCIONES PUBLICOS
*****************************************/
void ABB::insertar(char *usuario_, int victorias_, int derrotas_)
{
    if (raiz != NULL)
    {
        if (strcmp(raiz->usuario, usuario_) > 0)
        {
            if (raiz->izquierda != NULL)
                insertar(raiz->izquierda, usuario_, victorias_, derrotas_);
            else
                raiz->izquierda = new NodoArbol(usuario_, victorias_, derrotas_);
        }
        else if (strcmp(raiz->usuario, usuario_) < 0)
        {
            if (raiz->derecha != NULL)
                insertar(raiz->derecha, usuario_, victorias_, derrotas_);
            else
                raiz->derecha = new NodoArbol(usuario_, victorias_, derrotas_);
        }
    }
    else
        raiz = new NodoArbol(usuario_, victorias_, derrotas_);
}

void ABB::eliminar(char *usuario_)
{

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

    graficar(raiz);

    escribir("arbol.dot", "}", "a");

    system("dot -Tpng /home/marco/Escritorio/arbol.dot -o /home/marco/Escritorio/arbol.png");
}
