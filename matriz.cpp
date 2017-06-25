#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matriz.h"

/******************************************************************************
 * CONSTRUCTORES
******************************************************************************/
NodoMatriz::NodoMatriz(char *dato_, int color_, int fila_, int columna_, int nivel_)
{
    dato = new char[sizeof(dato)];
    strcpy(dato, dato_);
    color = color_;
    y = fila_;
    x = columna_;
    nivel = nivel_;
    izquierda = NULL;
    derecha = NULL;
    arriba = NULL;
    abajo = NULL;
    adelante = NULL;
    atras = NULL;
}

Encabezado::Encabezado(int indice_)
{
    indice = indice_;
    apunta = NULL;
    siguiente = NULL;
    anterior = NULL;
}

ListaEncabezado::ListaEncabezado()
{
    primero = NULL;
    ultimo = NULL;
}

Matriz::Matriz()
{
    columnas = new ListaEncabezado();
    filas = new ListaEncabezado();
}

/******************************************************************************
 * DESTRUCTORES
******************************************************************************/
NodoMatriz::~NodoMatriz()
{
    delete[] (dato);
    color = 0;
    y = 0;
    x = 0;
    nivel = 0;
    izquierda = NULL;
    derecha = NULL;
    arriba = NULL;
    abajo = NULL;
    adelante = NULL;
    atras = NULL;
}

Encabezado::~Encabezado()
{
    indice = 0;
    delete(apunta);
    siguiente = NULL;
    anterior = NULL;
}

ListaEncabezado::~ListaEncabezado()
{
    delete(primero);
}

Matriz::~Matriz()
{
    delete(columnas);
    delete(filas);
}

/*****************************************************************************
 * INSERTAR
*****************************************************************************/

NodoMatriz* Encabezado::ordenarNodos(NodoMatriz * actual, NodoMatriz *nuevo)
{
    if (actual->nivel > nuevo->nivel)
    {
        actual->adelante = nuevo;
        nuevo->atras = actual;

        nuevo->arriba = actual->arriba;
        nuevo->abajo = actual->abajo;
        nuevo->derecha = actual->derecha;
        nuevo->izquierda = actual->izquierda;

        if (actual->arriba != NULL)
            actual->arriba->abajo = nuevo;
        if (actual->abajo != NULL)
            actual->abajo->arriba = nuevo;
        if (actual->derecha != NULL)
            actual->derecha->izquierda = nuevo;
        if (actual->izquierda != NULL)
            actual->izquierda->derecha = nuevo;

        return nuevo;
    }
    else
    {
        nuevo->atras = actual->atras;
        nuevo->adelante = actual;
        if (actual->atras != NULL)
            actual->atras->adelante = nuevo;
        actual->atras = nuevo;

        return actual;
    }
}

void Encabezado::insertarFila(NodoMatriz *nuevo)
{
    if (apunta != NULL)
    {
        if (apunta->x > nuevo->x)
        {
            /* INSERTAR EN CABEZA */
            nuevo->derecha = apunta;
            apunta->izquierda = nuevo;

            apunta = nuevo;
        }
        else
        {
            NodoMatriz *aux = apunta;
            while (aux->derecha != NULL)
            {
                if (aux->x < nuevo->x)
                    aux = aux->derecha;
                else
                    break;
            }

            if (aux->x > nuevo->x)
            {
                /* INSERTAR ANTES */
                nuevo->izquierda = aux->izquierda;
                nuevo->derecha = aux;
                aux->izquierda->derecha = nuevo;
                aux->izquierda = nuevo;
            }
            else if (aux->x < nuevo->x)
            {
                /* INSERTAR DESPUES */
                nuevo->derecha = aux->derecha;
                nuevo->izquierda = aux;
                if (aux->derecha != NULL)
                    aux->derecha->izquierda = nuevo;
                aux->derecha = nuevo;
            }
            else
            {
                aux = ordenarNodos(aux, nuevo);
                if (aux->izquierda == NULL)
                    apunta = aux;
            }
        }
    }
    else
        apunta = nuevo;
}

void Encabezado::insertarColumna(NodoMatriz *nuevo)
{
    if (apunta != NULL)
    {
        if (apunta->y > nuevo->y)
        {
            /* INSERTAR EN CABEZA */
            nuevo->abajo = apunta;
            apunta->arriba = nuevo;

            apunta = nuevo;
        }
        else
        {
            NodoMatriz *aux = apunta;
            while (aux->abajo != NULL)
            {
                if (aux->y < nuevo->y)
                    aux = aux->abajo;
                else
                    break;
            }

            if (aux->y > nuevo->y)
            {
                /* INSERTAR ANTES */
                nuevo->arriba = aux->arriba;
                nuevo->abajo = aux;
                aux->arriba->abajo = nuevo;
                aux->arriba = nuevo;
            } else if(aux->y < nuevo->y)
            {
                /* INSERTAR DESPUES */
                nuevo->abajo = aux->abajo;
                nuevo->arriba = aux;
                if (aux->abajo != NULL)
                    aux->abajo->arriba = nuevo;
                aux->abajo = nuevo;
            }
        }
    }
    else
        apunta = nuevo;
}

Encabezado *ListaEncabezado::getEncabezado(int indice)
{
    Encabezado *actual = primero;

    while (actual != NULL)
    {
        if (actual->indice == indice)
            return actual;

        actual = actual->siguiente;
    }

    return NULL;
}

Encabezado *ListaEncabezado::insertar(int indice)
{
    if (primero != NULL)
    {
        if (primero->indice > indice)
        {
            /* INSERTAR EN CABEZA */
            Encabezado *temp = primero;
            primero = new Encabezado(indice);
            primero->siguiente = temp;
            temp->anterior = primero;

            return primero;
        }
        else if (ultimo->indice < indice)
        {
            /* INSERTAR EN COLA */
            ultimo->siguiente = new Encabezado(indice);
            ultimo = ultimo->siguiente;

            return ultimo;
        }
        else
        {
            Encabezado *actual = primero;
            while (actual != ultimo)
            {
                if (actual->indice < indice)
                    actual = actual->siguiente;
                else
                    break;
            }

            if (actual->indice > indice)
            {
                /* INSERTAR ANTES */
                Encabezado *nuevo = new Encabezado(indice);
                nuevo->anterior = actual->anterior;
                nuevo->siguiente = actual;
                actual->anterior->siguiente = nuevo;
                actual->anterior = nuevo;

                return nuevo;
            }
            else
                return actual;
        }
    }
    else
    {
        /* INICIAR LISTA */
        primero = new Encabezado(indice);
        ultimo = primero;

        return primero;
    }
}

void Matriz::insertar(char *dato, int color, int y, int x, int nivel)
{
    Encabezado *col = columnas->insertar(x);
    Encabezado *fil = filas->insertar(y);
    NodoMatriz *nuevo = new NodoMatriz(dato, color, y, x, nivel);

    fil->insertarFila(nuevo);
    col->insertarColumna(nuevo);
}

/****************************************************************************
 * GRAFICAR
****************************************************************************/
void Matriz::escribir(char filename[], char texto[], char *modo)
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

void Matriz::linealizarFila()
{
    char dot[256];

    strcpy(dot, "digraph linealRow\n{\n");
    strcat(dot, "\tnodesep=0.05;\n");
    strcat(dot, "\trankdir=LR;\n");
    strcat(dot, "\tnode [shape=record]\n");

    escribir("filas.dot", dot, "w");
    strcpy(dot, "");

    Encabezado *row = filas->primero;
    while (row != NULL)
    {
        NodoMatriz *actual = row->apunta;
        char nodo[10];

        while (actual != NULL)
        {
            sprintf(nodo, "nd%d%d%d", actual->y, actual->x, actual->nivel);
            strcpy(dot, nodo);
            strcat(dot, ";\n\t");
            strcat(dot, nodo);
            strcat(dot, "[label=\"");
            strcat(dot, actual->dato);
            strcat(dot, "\"];\n\t");

            strcat(dot, nodo);
            strcat(dot, " -> ");

            actual = actual->derecha;
            strcpy(nodo, "");

            escribir("filas.dot", dot, "a");
        }
        row = row->siguiente;
    }
    escribir("filas.dot", "NULL;\n}", "a");

    system("dot -Tpng /home/marco/Escritorio/filas.dot -o /home/marco/Escritorio/filas.png");
}

void Matriz::linealizarColumna()
{
    char dot[256];

    strcpy(dot, "digraph linealColumn\n{\n");
    strcat(dot, "\tnodesep=0.05;\n");
    strcat(dot, "\trankdir=LR;\n");
    strcat(dot, "\tnode [shape=record]\n");

    escribir("columnas.dot", dot, "w");
    strcpy(dot, "");

    Encabezado *column = columnas->primero;
    while (column != NULL)
    {
        NodoMatriz *actual = column->apunta;
        char nodo[10];

        while (actual != NULL)
        {
            sprintf(nodo, "nd%d%d%d", actual->y, actual->x, actual->nivel);
            strcpy(dot, nodo);
            strcat(dot, ";\n\t");
            strcat(dot, nodo);
            strcat(dot, "[label=\"");
            strcat(dot, actual->dato);
            strcat(dot, "\"];\n\t");

            strcat(dot, nodo);
            strcat(dot, " -> ");

            actual = actual->abajo;
            strcpy(nodo, "");

            escribir("columnas.dot", dot, "a");
        }
        column = column->siguiente;
    }
    escribir("columnas.dot", "NULL;\n}", "a");

    system("dot -Tpng /home/marco/Escritorio/columnas.dot -o /home/marco/Escritorio/columnas.png");
}

void Matriz::rank()
{
    char dot[128];
    char nodo[10];

    /***********************************
     * RANKSAME MATRIZ Y COLUMNAS
    ***********************************/
    strcpy(dot, "\n\t{ rank=same; MATRIZ -> ");
    Encabezado *encabezado = columnas->primero;
    while (encabezado != NULL)
    {
        sprintf(nodo, "C%d; ", encabezado->indice);
        strcat(dot, nodo);

        encabezado = encabezado->siguiente;
    }
    strcat(dot, "};");
    escribir("matriz.dot", dot, "a");

    /***********************************
     * RANKSAME LISTAS FILAS
    ***********************************/
    encabezado = filas->primero;
    while (encabezado != NULL)
    {
        NodoMatriz *actual = encabezado->apunta;
        strcpy(dot, "\t{ rank=same; ");
        sprintf(nodo, "F%d; ", encabezado->indice);
        strcat(dot, nodo);
        escribir("matriz.dot", dot, "a");

        while (actual != NULL)
        {
            sprintf(nodo, "nd%d%d%d", actual->y, actual->x, actual->nivel);
            strcpy(dot, nodo);
            strcat(dot, "; ");

            actual = actual->derecha;

            escribir("matriz.dot", dot, "a");
        }

        strcpy(dot, "};\n");
        escribir("matriz.dot", dot, "a");
        encabezado = encabezado->siguiente;
    }
}

void Matriz::graficarColumnas(int nivel)
{
    char dot[256];
    char nodo[10];

    Encabezado *column = columnas->primero;
    while (column != NULL)
    {
        NodoMatriz *actual = column->apunta;

        strcpy(dot, "\n\t");
        sprintf(nodo, "C%d", column->indice);
        strcat(dot, nodo);
        strcat(dot, "[label=\"");
        sprintf(nodo, "%d", column->indice);
        strcat(dot, nodo);
        strcat(dot, "\"];\n");
        strcat(dot, "\t");
        sprintf(nodo, "C%d", column->indice);
        strcat(dot, nodo);
        strcat(dot, " -> ");
        escribir("matriz.dot", dot, "a");

        while (actual != NULL)
        {
            sprintf(nodo, "nd%d%d%d", actual->y, actual->x, actual->nivel);
            strcpy(dot, nodo);
            strcat(dot, ";\n\t");
            strcat(dot, nodo);
            strcat(dot, "[label=\"");
            strcat(dot, actual->dato);
            strcat(dot, "\"];\n");
            if (actual->abajo != NULL)
            {
                strcat(dot, "\t");
                strcat(dot, nodo);
                strcat(dot, " -> ");
            }

            actual = actual->abajo;
            strcpy(nodo, "");

            escribir("matriz.dot", dot, "a");
        }
        column = column->siguiente;
    }
}

void Matriz::graficarFilas(int nivel)
{
    char dot[256];
    char nodo[10];

    Encabezado *row = filas->primero;
    while (row != NULL)
    {
        NodoMatriz *actual = row->apunta;

        strcpy(dot, "\n\t");
        sprintf(nodo, "F%d", row->indice);
        strcat(dot, nodo);
        strcat(dot, "[label=\"");
        sprintf(nodo, "%d", row->indice);
        strcat(dot, nodo);
        strcat(dot, "\"];\n");
        strcat(dot, "\t");
        sprintf(nodo, "F%d", row->indice);
        strcat(dot, nodo);
        strcat(dot, " -> ");
        escribir("matriz.dot", dot, "a");

        while (actual != NULL)
        {
            sprintf(nodo, "nd%d%d%d", actual->y, actual->x, actual->nivel);
            strcpy(dot, nodo);
            strcat(dot, ";\n");

            if (actual->derecha != NULL)
            {
                strcat(dot, "\t");
                strcat(dot, nodo);
                strcat(dot, " -> ");
            }

            actual = actual->derecha;
            strcpy(nodo, "");

            escribir("matriz.dot", dot, "a");
        }
        row = row->siguiente;
    }
}

void Matriz::graficar(int nivel)
{
    char dot[128];
    char nodo[5];
    Encabezado *encabezado;

    /***********************************
     * CREAR ENCABEZADO DOT
    ***********************************/
    strcpy(dot, "digraph matriz\n{\n");
    strcat(dot, "\tnode[shape=box, style=filled, color=lightsteelblue3];\n");
    strcat(dot, "\tedge[color=black];\n");
    strcat(dot, "\trankdir=UD;\n");

    escribir("matriz.dot", dot, "w");

    /* { rank=same; Listar filas } */
    rank();

    /***********************************
     * LISTAR COLUMNAS
    ***********************************/
    graficarColumnas(nivel);

    /***********************************
     * LISTAR FILAS
    ***********************************/
    graficarFilas(nivel);

    /***********************************
     * ENLAZAR COLUMNAS
    ***********************************/
    encabezado = columnas->primero;
    strcpy(dot, "\tMATRIZ -> ");
    while (encabezado != NULL)
    {
        sprintf(nodo, "C%d", encabezado->indice);
        strcat(dot, nodo);
        if (encabezado->siguiente != NULL)
            strcat(dot, " -> ");
        encabezado = encabezado->siguiente;
    }
    strcat(dot, ";\n");
    escribir("matriz.dot", dot, "a");

    /***********************************
     * ENLAZAR FILAS
    ***********************************/
    encabezado = filas->primero;
    strcpy(dot, "\tMATRIZ -> ");
    while (encabezado != NULL)
    {
        sprintf(nodo, "F%d", encabezado->indice);
        strcat(dot, nodo);
        if (encabezado->siguiente != NULL)
            strcat(dot, " -> ");
        encabezado = encabezado->siguiente;
    }
    strcat(dot, ";\n");
    escribir("matriz.dot", dot, "a");

    strcpy(dot, "}");
    escribir("matriz.dot", dot, "a");

    system("dot -Tpng /home/marco/Escritorio/matriz.dot -o /home/marco/Escritorio/matriz.png");
}
