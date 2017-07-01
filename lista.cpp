#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"

/****************************************
 * CONSTRUCTORES
*****************************************/
NodoLista::NodoLista(char *user, int victorias)
{
    usuario = new char[sizeof(user)];
    strcpy(usuario, user);
    victoria = victorias;
    anterior = NULL;
    siguiente = NULL;
}

Lista::Lista()
{
    primero = NULL;
}

/****************************************
 * DESTRUCTORES
*****************************************/
NodoLista::~NodoLista()
{
    strcpy(usuario, "");
    victoria = 0;
    anterior = NULL;
    siguiente = NULL;
}

Lista::~Lista()
{
    primero = NULL;
}

void Lista::agregar(char *usuario, int victorias)
{
    if (primero != NULL)
    {
        if (primero->victoria < victorias)
        {
            /* INSERTAR EN CABEZA */
            NodoLista *nuevo = new NodoLista(usuario, victorias);
            nuevo->siguiente = primero;
            primero->anterior = nuevo;

            primero = nuevo;
        }
        else
        {
            NodoLista *aux = primero;
            while (aux->siguiente != NULL)
            {
                if (aux->victoria > victorias)
                    aux = aux->siguiente;
                else
                    break;
            }

            if (aux->victoria < victorias)
            {
                /* INSERTAR ANTES */
                NodoLista *nuevo = new NodoLista(usuario, victorias);
                nuevo->anterior = aux->anterior;
                nuevo->siguiente = aux;
                aux->anterior->siguiente = nuevo;
                aux->anterior = nuevo;
            } else if(aux->victoria > victorias)
            {
                NodoLista *nuevo = new NodoLista(usuario, victorias);
                /* INSERTAR DESPUES */
                nuevo->siguiente = aux->siguiente;
                nuevo->anterior = aux;
                if (aux->siguiente != NULL)
                    aux->siguiente->anterior = nuevo;
                aux->siguiente = nuevo;
            }
        }
    }
    else
        primero = new NodoLista(usuario, victorias);
}

/**************************************
 * GRAFICAR
**************************************/
void Lista::escribir(char filename[], char texto[], char *modo)
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

void Lista::graficar()
{
    char dot[120];
    NodoLista *aux = primero;

    /***********************************
     * CREAR ENCABEZADO DOT
    ***********************************/
    strcpy(dot, "digraph linealColumn\n{\n");
    strcat(dot, "\tnodesep=0.05;\n");
    strcat(dot, "\trankdir=LR;\n");
    strcat(dot, "\tnode [shape=record]\n");

    escribir("top.dot", dot, "w");
    strcpy(dot, "");

    for (int i = 0; i < 10; i++)
    {
        if (aux != NULL)
        {
            char v[2];
            sprintf(v, "%d", aux->victoria);
            strcpy(dot, "nd");
            strcat(dot, aux->usuario);
            strcat(dot, ";\n\t");
            strcat(dot, "nd");
            strcat(dot, aux->usuario);
            strcat(dot, "[label=\"");
            strcat(dot, aux->usuario);
            strcat(dot, "\\n");
            strcat(dot, v);
            strcat(dot, "\"]\n\t");

            strcat(dot, "nd");
            strcat(dot, aux->usuario);
            strcat(dot, " -> ");

            escribir("top.dot", dot, "a");
        }
        else
            break;
        aux = aux->siguiente;
    }

    escribir("top.dot", "NULL;\n}", "a");

    system("dot -Tpng /home/marco/Escritorio/top.dot -o /home/marco/Escritorio/top.png");
}
