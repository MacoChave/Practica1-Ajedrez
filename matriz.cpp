#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matriz.h"

/*****************************************************************************
 * ***************************************************************************
 *  CONSTRUCTORES
 * ***************************************************************************
*****************************************************************************/
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

/*****************************************************************************
 * ***************************************************************************
 *  DESTRUCTORES
 * ***************************************************************************
*****************************************************************************/
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
 * ***************************************************************************
 *  ENCABEZADOS
 * ***************************************************************************
*****************************************************************************/
/*****************************************************************************
 *  ORDENAR NODOS POR NIVEL
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

/*****************************************************************************
 *  INSERTAR EN FILAS O COLUMNAS
*****************************************************************************/
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

void Encabezado::eliminarFila(NodoMatriz *nodo)
{
    bool top = false;
    bool bottom = false;

    if (nodo->adelante != NULL)
        nodo->adelante->atras = nodo->atras;
    else
        top = true;
    if (nodo->atras != NULL)
        nodo->atras->adelante = nodo->adelante;
    else
        bottom = true;

    if (nodo->derecha != NULL)
    {
        if (!bottom)
        {
            nodo->derecha->izquierda = nodo->atras;
            nodo->atras->derecha = nodo->derecha;
        }
        else
            nodo->derecha->izquierda = nodo->izquierda;
    }
    if (nodo->izquierda != NULL)
    {
        if (!bottom)
        {
            nodo->izquierda->derecha = nodo->atras;
            nodo->atras->izquierda = nodo->izquierda;
        }
        else
            nodo->izquierda->derecha = nodo->derecha;
    }
    else
    {
        if (top && !bottom)
            apunta = nodo->atras;
        else if (top)
            apunta = nodo->derecha;
    }
}

void Encabezado::eliminarColumna(NodoMatriz *nodo)
{
    bool top = false;
    bool bottom = false;

    if (nodo->adelante == NULL)
        top = true;
    if (nodo->atras == NULL)
        bottom = true;

    if (nodo->abajo != NULL)
    {
        if (!bottom)
        {
            nodo->abajo->arriba = nodo->atras;
            nodo->atras->abajo = nodo->abajo;
        }
        else
            nodo->abajo->arriba = nodo->arriba;
    }
    if (nodo->arriba != NULL)
    {
        if (!bottom)
        {
            nodo->arriba->abajo = nodo->atras;
            nodo->atras->arriba = nodo->arriba;
        }
        else
            nodo->arriba->abajo = nodo->abajo;
    }
    else
    {
        if (top &&!bottom)
            apunta = nodo->atras;
        else if (top)
            apunta = nodo->abajo;
    }
}

/*****************************************************************************
 *  BUSCAR NODO
*****************************************************************************/
NodoMatriz *Encabezado::buscarNodo(NodoMatriz *nodo, char *dato, int color, int nivel)
{
    NodoMatriz *aux = nodo;
    NodoMatriz *tmp;

    while (aux != NULL)
    {
        if (strcmp(aux->dato, dato) == 0 && aux->color == color && aux->nivel == nivel)
            break;
        else
        {
            if (aux->atras != NULL)
            {
                tmp = aux->atras;
                if (strcmp(tmp->dato, dato) == 0 && tmp->color == color && tmp->nivel == nivel)
                {
                    aux = tmp;
                    break;
                }
                else
                {
                    if (tmp->atras != NULL)
                    {
                        tmp = tmp->atras;
                        if (strcmp(tmp->dato, dato) == 0 && tmp->color == color && tmp->nivel == nivel)
                        {
                            aux = tmp;
                            break;
                        }
                    }
                }
            }
        }
        aux = aux->derecha;
    }

    return aux;
}

/*****************************************************************************
 * ***************************************************************************
 *  LISTA ENCABEZADO
 * ***************************************************************************
*****************************************************************************/
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

void ListaEncabezado::eliminarFila(NodoMatriz *nodo)
{
    /*  BUSCAR ENCABEZADO UBICACION FILA  */
    Encabezado *filaEliminar = primero;

    while (filaEliminar != NULL)
    {
        if (filaEliminar->indice < nodo->y)
            filaEliminar = filaEliminar->siguiente;
        else
            break;
    }

    filaEliminar->eliminarFila(nodo);
}

void ListaEncabezado::eliminarColumna(NodoMatriz *nodo)
{
    /*  BUSCAR ENCABEZADO UBICACION COLUMNA  */
    Encabezado *columnaEliminar = primero;

    while (columnaEliminar != NULL)
    {
        if (columnaEliminar->indice < nodo->x)
            columnaEliminar = columnaEliminar->siguiente;
        else
            break;
    }

    columnaEliminar->eliminarColumna(nodo);
}

NodoMatriz *ListaEncabezado::buscarNodoMatriz(char *dato, int color, int nivel)
{
    Encabezado *filaAux = primero;
    NodoMatriz *aux = NULL;

    while (filaAux != NULL)
    {
        aux = filaAux->buscarNodo(filaAux->apunta, dato, color, nivel);
        if (aux == NULL)
            filaAux = filaAux->siguiente;
        else
            break;
    }
    return aux;
}

/*****************************************************************************
 * ***************************************************************************
 *  MATRIZ
 * ***************************************************************************
*****************************************************************************/
/*****************************************************************************
 *  INSERTAR
*****************************************************************************/
void Matriz::insertar(char *dato, int color, int y, int x, int nivel)
{
    Encabezado *col = columnas->insertar(x);
    Encabezado *fil = filas->insertar(y);
    NodoMatriz *nuevo = new NodoMatriz(dato, color, y, x, nivel);

    fil->insertarFila(nuevo);
    col->insertarColumna(nuevo);
}

/*****************************************************************************
 *  MOVER
*****************************************************************************/
bool Matriz::validarMovimiento(NodoMatriz *nodo, int fila, int columna)
{
    /*
     * T - TORRE | C - CABALLO | A - ALFIL | D - DAMA | R - REY | P - PEON
     * 0 - NEGRO
     * 1 - BLANCO
    */
    if (strcmp(nodo->dato, "T"))
    {
        if (nodo->color == 0)
        {
        }
        else
        {
        }
    }
    if (strcmp(nodo->dato, "C"))
    {
        if (nodo->color == 0)
        {
        }
        else
        {
        }
    }
    if (strcmp(nodo->dato, "A"))
    {
        if (nodo->color == 0)
        {
        }
        else
        {
        }
    }
    if (strcmp(nodo->dato, "D"))
    {
        if (nodo->color == 0)
        {
        }
        else
        {
        }
    }
    if (strcmp(nodo->dato, "R"))
    {
        if (nodo->color == 0)
        {
        }
        else
        {
        }
    }
    if (strcmp(nodo->dato, "P"))
    {
        if (abs(fila - nodo->y) == 1)
        {

        }
    }
}

void Matriz::mover(char *dato, int color, int nivel, int fila, int columna)
{
    NodoMatriz *nodoEliminar = filas->buscarNodoMatriz(dato, color, nivel);
    if (nodoEliminar != NULL)
    {
        filas->eliminarFila(nodoEliminar);
        columnas->eliminarColumna(nodoEliminar);

        delete(nodoEliminar);
        nodoEliminar = NULL;
    }
}

/****************************************************************************
 *  ESCRIBIR EN ARCHIVO
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

NodoMatriz *Matriz::buscarNivel(NodoMatriz *nodo, int nivel)
{
    NodoMatriz *aux = nodo;
    while (aux != NULL)
    {
        if (aux->nivel == nivel)
            break;
        else
            aux = aux->atras;
    }
    return aux;
}

/*****************************************************************************
 *  GRAFICAR POR LINALIZACIÓN
*****************************************************************************/
void Matriz::linealizarFila(int nivel)
{
    char dot[100];

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
            NodoMatriz *aux = buscarNivel(actual, nivel);
            if (aux != NULL)
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

                escribir("filas.dot", dot, "a");
            }

            actual = actual->derecha;
        }
        row = row->siguiente;
    }
    escribir("filas.dot", "NULL;\n}", "a");

    system("dot -Tpng /home/marco/Escritorio/filas.dot -o /home/marco/Escritorio/filas.png");
}

void Matriz::linealizarColumna(int nivel)
{
    char dot[100];

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
            NodoMatriz *aux = buscarNivel(actual, nivel);
            if (aux != NULL)
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

                escribir("columnas.dot", dot, "a");
            }

            actual = actual->abajo;
        }
        column = column->siguiente;
    }
    escribir("columnas.dot", "NULL;\n}", "a");

    system("dot -Tpng /home/marco/Escritorio/columnas.dot -o /home/marco/Escritorio/columnas.png");
}

void Matriz::graficarColumnas(char *titulo, int nivel)
{
    char dot[100];
    Encabezado *column = columnas->primero;

    while (column != NULL)
    {
        NodoMatriz *actual = column->apunta;
        char nodo[10];

        while (actual != NULL)
        {
            NodoMatriz *aux = buscarNivel(actual, nivel);
            if (aux != NULL)
            {
                sprintf(nodo, "nd%d%d%d", aux->y, aux->x, aux->nivel);
                strcpy(dot, nodo);
                strcat(dot, ";\n\t");
                strcat(dot, nodo);
                strcat(dot, "[label=\"");
                strcat(dot, aux->dato);
                strcat(dot, "\"");

                strcat(dot, ", color=");
                if (aux->color == 0)
                    strcat(dot, "gray75");
                else
                    strcat(dot, "gray25");
                strcat(dot, "];\n\t");

                if (buscarNivel(actual->abajo, nivel) != NULL)
                {
                    strcat(dot, nodo);
                    strcat(dot, " -> ");
                }

                escribir(titulo, dot, "a");
            }

            actual = actual->abajo;
        }
        column = column->siguiente;
    }
}

void Matriz::graficarFilas(char *titulo, int nivel)
{
    char dot[100];
    Encabezado *fila = filas->primero;

    while (fila != NULL)
    {
        NodoMatriz *actual = fila->apunta;
        char nodo[15];

        while (actual != NULL)
        {
            NodoMatriz *aux = buscarNivel(actual, nivel);
            if (aux != NULL)
            {
                sprintf(nodo, "nd%d%d%d", aux->y, aux->x, aux->nivel);
                strcpy(dot, nodo);
                strcat(dot, ";\n\t");

                if (buscarNivel(actual->derecha, nivel) != NULL)
                {
                    strcat(dot, nodo);
                    strcat(dot, " -> ");
                }

                escribir(titulo, dot, "a");
            }

            actual = actual->derecha;
        }
        fila = fila->siguiente;
    }
}

void Matriz::graficarEnlaceColumna(char *titulo, int nivel)
{
    char dot[75];
    Encabezado *column = columnas->primero;
    strcpy(dot, "MATRIZ");

    while (column != NULL)
    {
        NodoMatriz *actual = column->apunta;
        char col[3];

        sprintf(col, "C%d", column->indice);

        while (actual != NULL)
        {
            NodoMatriz *aux = buscarNivel(actual, nivel);
            if (aux != NULL)
            {
                strcat(dot, " -> ");
                strcat(dot, col);

                escribir(titulo, dot, "a");
                strcpy(dot, "");
                break;
            }

            actual = actual->abajo;
        }
        column = column->siguiente;
    }
    strcpy(dot, ";\n\t");
    escribir(titulo, dot, "a");
}

void Matriz::graficarEnlaceFila(char *titulo, int nivel)
{
    char dot[75];
    Encabezado *fila = filas->primero;
    strcpy(dot, "MATRIZ");

    while (fila != NULL)
    {
        NodoMatriz *actual = fila->apunta;
        char fil[3];

        sprintf(fil, "F%d", fila->indice);

        while (actual != NULL)
        {
            NodoMatriz *aux = buscarNivel(actual, nivel);
            if (aux != NULL)
            {
                strcat(dot, " -> ");
                strcat(dot, fil);

                escribir(titulo, dot, "a");

                strcpy(dot, "");
                break;
            }

            actual = actual->derecha;
        }
        fila = fila->siguiente;
    }
    strcpy(dot, ";\n\t");
    escribir(titulo, dot, "a");
}

void Matriz::graficarEnlaceColumnaNodo(char *titulo, int nivel)
{
    char dot[75];
    Encabezado *column = columnas->primero;

    while (column != NULL)
    {
        NodoMatriz *actual = column->apunta;
        char nodo[10];
        char col[3];

        sprintf(col, "C%d", column->indice);

        while (actual != NULL)
        {
            NodoMatriz *aux = buscarNivel(actual, nivel);
            if (aux != NULL)
            {
                sprintf(nodo, "nd%d%d%d", aux->y, aux->x, aux->nivel);
                strcpy(dot, col);
                strcat(dot, " -> ");
                strcat(dot, nodo);
                strcat(dot, ";\n\t");

                escribir(titulo, dot, "a");
                break;
            }

            actual = actual->abajo;
        }
        column = column->siguiente;
    }
}

void Matriz::graficarEnlaceFilaNodo(char *titulo, int nivel)
{
    char dot[75];
    Encabezado *fila = filas->primero;

    while (fila != NULL)
    {
        NodoMatriz *actual = fila->apunta;
        char nodo[15];
        char fil[3];

        sprintf(fil, "F%d", fila->indice);

        while (actual != NULL)
        {
            NodoMatriz *aux = buscarNivel(actual, nivel);
            if (aux != NULL)
            {
                sprintf(nodo, "nd%d%d%d", aux->y, aux->x, aux->nivel);
                strcpy(dot, fil);
                strcat(dot, " -> ");
                strcat(dot, nodo);
                strcat(dot, ";\n\t");

                escribir(titulo, dot, "a");
                strcpy(dot, "");
                break;
            }

            actual = actual->derecha;
        }
        fila = fila->siguiente;
    }
}

void Matriz::setRank(char *titulo, int nivel)
{
    char dot[75];
    Encabezado *encabezadoAux = columnas->primero;

    strcpy(dot, "{ rank=same; MATRIZ; ");
    escribir(titulo, dot, "a");

    while (encabezadoAux != NULL)
    {
        NodoMatriz *actual = encabezadoAux->apunta;
        char nodo[10];
        char col[3];

        sprintf(col, "C%d", encabezadoAux->indice);

        while (actual != NULL)
        {
            NodoMatriz *aux = buscarNivel(actual, nivel);
            if (aux != NULL)
            {
                strcpy(dot, col);
                strcat(dot, "; ");

                escribir(titulo, dot, "a");
                break;
            }

            actual = actual->abajo;
        }
        encabezadoAux = encabezadoAux->siguiente;
    }
    strcpy(dot, "};\n\t");
    escribir(titulo, dot, "a");

    encabezadoAux = filas->primero;

    while (encabezadoAux != NULL)
    {
        NodoMatriz *actual = encabezadoAux->apunta;
        char nodo[15];
        char fil[3];

        sprintf(fil, "F%d", encabezadoAux->indice);
        strcpy(dot, "{ rank=same; ");
        strcat(dot, fil);
        strcat(dot, "; ");

        while (actual != NULL)
        {
            NodoMatriz *aux = buscarNivel(actual, nivel);
            if (aux != NULL)
            {
                sprintf(nodo, "nd%d%d%d", aux->y, aux->x, aux->nivel);
                strcat(dot, nodo);
                strcat(dot, "; ");

                escribir(titulo, dot, "a");
                strcpy(dot, "");
            }

            actual = actual->derecha;
        }
        strcpy(dot, "};\n\t");
        escribir(titulo, dot, "a");

        encabezadoAux = encabezadoAux->siguiente;
    }
}

void Matriz::graficar(int nivel)
{
    char dot[120];
    char tituloGrafica[10];
    char cmd[100];
    char filename[15];

    sprintf(tituloGrafica, "Matriz_%d", nivel);
    strcpy(filename, tituloGrafica);
    strcat(filename, ".dot");
    printf("%s", tituloGrafica);
    printf("%s", filename);

    /***********************************
     * CREAR ENCABEZADO DOT
    ***********************************/
    strcpy(dot, "digraph matriz\n{\n");
    strcat(dot, "\tnode[shape=box, style=filled, color=lightsteelblue3];\n");
    strcat(dot, "\tedge[color=black];\n");
    strcat(dot, "\trankdir=UD;\n");

    escribir(filename, dot, "w");

    /***********************************
     * LISTAR COLUMNAS
    ***********************************/
    graficarColumnas(filename, nivel);
    escribir(filename, "\n\t", "a");

    /***********************************
     * LISTAR FILAS
    ***********************************/
    graficarFilas(filename, nivel);
    escribir(filename, "\n\t", "a");

    /***********************************
     * ENLAZAR COLUMNAS Y FILAS
    ***********************************/
    graficarEnlaceColumnaNodo(filename, nivel);
    escribir(filename, "\n\t", "a");
    graficarEnlaceFilaNodo(filename, nivel);
    escribir(filename, "\n\t", "a");

    graficarEnlaceColumna(filename, nivel);
    escribir(filename, "\n\t", "a");
    graficarEnlaceFila(filename, nivel);
    escribir(filename, "\n\t", "a");

    /***********************************
     * ALINEAR FILAS
    ***********************************/
    setRank(filename, nivel);

    strcpy(dot, "\n}");
    escribir(filename, dot, "a");

    strcpy(cmd, "dot -Tpng /home/marco/Escritorio/");
    strcat(cmd, filename);
    strcat(cmd, " -o /home/marco/Escritorio/");
    strcat(cmd, tituloGrafica);
    strcat(cmd, ".png");
    system(cmd);
}

