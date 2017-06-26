#ifndef MATRIZ_H
#define MATRIZ_H

class NodoMatriz
{
public:
    NodoMatriz(char *dato_, int color_, int fila_, int columna_, int nivel_);
    ~NodoMatriz();

    char* dato;
    int color;
    int y;
    int x;
    int nivel;
    NodoMatriz *izquierda;
    NodoMatriz *derecha;
    NodoMatriz *arriba;
    NodoMatriz *abajo;
    NodoMatriz *adelante;
    NodoMatriz *atras;
};

class Encabezado
{
    NodoMatriz *ordenarNodos(NodoMatriz *actual, NodoMatriz *nuevo);
public:
    Encabezado(int indice_);
    ~Encabezado();

    int indice;
    Encabezado *siguiente;
    Encabezado *anterior;
    NodoMatriz *apunta;
    void insertarFila(NodoMatriz *nuevo);
    void insertarColumna(NodoMatriz *nuevo);
    NodoMatriz *buscarNodo(NodoMatriz *nodo, char *dato, int color, int nivel);
};

class ListaEncabezado
{
public:
    ListaEncabezado();
    ~ListaEncabezado();

    Encabezado *primero;
    Encabezado *ultimo;
    Encabezado* insertar(int indice);
    NodoMatriz *buscarNodoMatriz(char *dato, int color, int nivel);
};

class Matriz
{
    void escribir(char filename[], char texto[], char *modo);
    NodoMatriz* buscarNivel(NodoMatriz *nodo, int nivel);
    void rank(int nivel);
    void graficarColumnas(int nivel);
    void graficarFilas(int nivel);
public:
    Matriz();
    ~Matriz();

    ListaEncabezado *columnas;
    ListaEncabezado *filas;
    void insertar(char *dato, int color, int y, int x, int nivel);
    void mover(char *dato, int color, int nivel);
    void linealizarFila(int nivel);
    void linealizarColumna(int nivel);
    void graficar(int nivel);
};

#endif // MATRIZ_H
