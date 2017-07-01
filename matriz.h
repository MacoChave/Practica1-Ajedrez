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
    void eliminarFila(NodoMatriz *nodo);
    void eliminarColumna(NodoMatriz *nodo);
    NodoMatriz *buscarNodo(NodoMatriz *nodo, char *dato, int color, int nivel);
    NodoMatriz *buscarNodo(NodoMatriz *nodo, int columna, int nivel);
};

class ListaEncabezado
{
public:
    ListaEncabezado();
    ~ListaEncabezado();

    Encabezado *primero;
    Encabezado *ultimo;
    Encabezado* insertar(int indice);
    void eliminarFila(NodoMatriz *nodo);
    void eliminarColumna(NodoMatriz *nodo);
    NodoMatriz *buscarNodoMatriz(char *dato, int color, int nivel);
    NodoMatriz *buscarNodoMatriz(int fila, int columna, int nivel);
};

class Matriz
{
    NodoMatriz* validarMovimiento(NodoMatriz *nodoDestino, char *pieza, int y, int x, int color, int nivel);
    void escribir(char filename[], char texto[], char *modo);
    NodoMatriz* buscarNivel(NodoMatriz *nodo, int nivel);
    void graficarEnlaceColumnaNodo(char *titulo, int nivel);
    void graficarEnlaceFilaNodo(char *titulo, int nivel);
    void graficarColumnas(char *titulo, int nivel);
    void graficarFilas(char *titulo, int nivel);
    void graficarEnlaceColumna(char *titulo, int nivel);
    void graficarEnlaceFila(char *titulo, int nivel);
    void setRank(char *titulo, int nivel);
public:
    Matriz();
    ~Matriz();

    ListaEncabezado *columnas;
    ListaEncabezado *filas;
    void insertar(char *dato, int color, int y, int x, int nivel);
    bool mover(char dato[], int color, int nivel, int fila, int columna);
    void linealizarFila(int nivel);
    void linealizarColumna(int nivel);
    void graficar(int nivel);
};

#endif // MATRIZ_H
