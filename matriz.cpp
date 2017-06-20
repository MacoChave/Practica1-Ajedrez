#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matriz.h"

/****************************************
 * CONSTRUCTORES
****************************************/
Nodo::Nodo(char *dato_, int fila_, int columna_, int nivel_)
{
    dato = new char[sizeof(dato)];
    strcpy(dato, dato_);
    fila = fila_;
    columna = columna_;
    nivel = nivel_;
    izquierda = NULL;
    derecha = NULL;
    arriba = NULL;
    abajo = NULL;
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
}

Matriz::Matriz()
{
    columnas = new ListaEncabezado();
    filas = new ListaEncabezado();
}

/****************************************
 * DESTRUCTORES
****************************************/
Nodo::~Nodo()
{
    delete[] (dato);
    izquierda = NULL;
    derecha = NULL;
    arriba = NULL;
    abajo = NULL;
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

/***************************************
 * INSERTAR
***************************************/
void ListaEncabezado::insertar(Encabezado *nuevo)
{
    if (primero == NULL)
        primero = nuevo;
    else
    {
        if (nuevo->indice < primero->indice)
        {
            nuevo->siguiente = primero;
            primero->anterior = nuevo;
            primero = nuevo;
        }
        else
        {
            Encabezado *actual = primero;

            while (actual->siguiente != NULL)
            {
                if (nuevo->indice < actual->indice)
                {
                    nuevo->anterior = actual->anterior;
                    nuevo->siguiente = actual;
                    actual->anterior->siguiente = nuevo;
                    actual->anterior = nuevo;
                    break;
                }
                actual = actual->siguiente;
            }
            if (actual->siguiente == NULL)
            {
                if (nuevo->indice < actual->indice)
                {
                    nuevo->anterior = actual->anterior;
                    nuevo->siguiente = actual;
                    actual->anterior->siguiente = nuevo;
                    actual->anterior = nuevo;
                }
                else
                {
                    actual->siguiente = nuevo;
                    nuevo->anterior = actual;
                }
            }
        }
    }
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

void Matriz::insertar(char *dato, int fila, int columna, int nivel)
{
    // CREAR NUEVO NODO
    Nodo *nuevo = new Nodo(dato, fila, columna, nivel);

    // FILA
    Encabezado *row = filas->getEncabezado(fila);

    if (row == NULL)
    {
        /* CREAR UNA FILA E INSERTAR */
        row = new Encabezado(fila);
        filas->insertar(row);
        row->apunta = nuevo;
    }
    else
    {
        /* INSERTAR EN FILA LOCALIZADA */
        if (nuevo->columna < row->apunta->columna)
        {
            /* INSERTAR AL INICIO */
            nuevo->derecha = row->apunta;
            row->apunta->izquierda = nuevo;
            row->apunta = nuevo;
        }
        else
        {
            Nodo *actual = row->apunta;

            while (actual->derecha != NULL)
            {
                if (nuevo->columna < actual->columna)
                {
                    /* INSERTAR AL MEDIO */
                    nuevo->izquierda = actual->izquierda;
                    nuevo->derecha = actual;
                    actual->izquierda->derecha = nuevo;
                    actual->izquierda = nuevo;
                    break;
                }
                actual = actual->derecha;
            }
            if (actual->derecha == NULL)
            {
                /* INSERTAR AL FINAL */
                actual->derecha = nuevo;
                nuevo->izquierda = actual;
            }
        }
    }

    // COLUMNA
    Encabezado *column = columnas->getEncabezado(columna);

    if (column == NULL)
    {
        /* CREAR UNA COLUMNA E INSERTAR */
        column = new Encabezado(columna);
        columnas->insertar(column);
        column->apunta = nuevo;
    }
    else
    {
        /* INSERTAR UNA COLUMNA LOCALIZADA */
        if (nuevo->fila < column->apunta->fila)
        {
            /* INSERTAR AL INICIO */
            nuevo->abajo = column->apunta;
            column->apunta->arriba = nuevo;
            column->apunta = nuevo;
        }
        else
        {
            Nodo *actual = column->apunta;

            while (actual->abajo != NULL)
            {
                if (nuevo->fila < actual->fila)
                {
                    /* INSERTAR AL MEDIO */
                    nuevo->arriba = actual->arriba;
                    nuevo->abajo = actual;
                    actual->arriba->abajo = nuevo;
                    actual->arriba = nuevo;
                    break;
                }
                actual = actual->abajo;
            }
            if (actual->abajo == NULL)
            {
                /* INSERTAR AL FINAL */
                actual->abajo = nuevo;
                nuevo->arriba = actual;
            }
        }
    }
}

/**************************************
 * GRAFICAR
**************************************/
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

void Matriz::graficarFilas()
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
        Nodo *actual = row->apunta;
        char nodo[10];

        while (actual != NULL)
        {
            sprintf(nodo, "nd%d%d%d", actual->fila, actual->columna, actual->nivel);
            strcpy(dot, nodo);
            strcat(dot, ";\n\t");
            strcat(dot, nodo);
            strcat(dot, "[label=\"");
            strcat(dot, actual->dato);
            strcat(dot, "\"];\n");
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

void Matriz::graficarColumnas()
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
        Nodo *actual = column->apunta;
        char nodo[10];

        while (actual != NULL)
        {
            sprintf(nodo, "nd%d%d%d", actual->fila, actual->columna, actual->nivel);
            strcpy(dot, nodo);
            strcat(dot, ";\n\t");
            strcat(dot, nodo);
            strcat(dot, "[label=\"");
            strcat(dot, actual->dato);
            strcat(dot, "\"];\n");
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
