#include <QTextStream>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "principal.h"
#include "ui_principal.h"

Principal::Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principal)
{
    matriz = new Matriz();
    arbol = new ABB();
    ui->setupUi(this);
    insertarMatriz();
}

Principal::~Principal()
{
    delete ui;
}

QString Principal::lectura(QString filename)
{
    QFile file(filename);

    if (!file.open(QFile::ReadOnly | QFile::Text))
        return NULL;
    else
    {
        QTextStream in(&file);
        QString texto = in.readAll();

        file.close();

        return texto;
    }
}

void Principal::separar(char* texto)
{
    bool fin = false;

    char *usuario;
    int victorias;
    int derrotas;
    /**********************************
     * INSERTAR PRIMERA FILA
    **********************************/
    usuario = strtok(texto, "_\n");
    victorias = atoi(strtok(NULL, "_\n"));
    derrotas = atoi(strtok(NULL, "_\n"));

    arbol->insertar(usuario, victorias, derrotas);

    /**********************************
     * INSERTAR FILA SIGUIENTES
    **********************************/

    while (!fin)
    {
        usuario = strtok(NULL, "_\n");

        if (strcmp(usuario, "#") != 0)
        {
            victorias = atoi(strtok(NULL, "_\n"));
            derrotas = atoi(strtok(NULL, "_\n"));

            arbol->insertar(usuario, victorias, derrotas);
        }
        else
            fin = true;
    }
}

void Principal::insertarMatriz()
{
    matriz->insertar("Torre", 0, 2, 0);
    matriz->insertar("Torre", 0, 7, 0);
    matriz->insertar("Peon", 1, 0, 0);
    matriz->insertar("Rey", 1, 3, 0);
    matriz->insertar("Peon", 1, 7, 0);
    matriz->insertar("Caballo", 2, 5, 0);
    matriz->insertar("Peon", 3, 2, 0);
    matriz->insertar("Peon", 3, 3, 0);
}

void Principal::on_actionAbrir_triggered()
{
    /*
    arbol->insertar("Sakamoto", 10, 0);
    arbol->insertar("Neji", 8, 2);
    arbol->insertar("Yamada", 5, 5);
    arbol->insertar("Mikasa", 8, 2);
    arbol->insertar("Kosuda", 2, 8);
    arbol->insertar("Eren", 4, 6);
    arbol->insertar("Asuna", 7, 3);
    arbol->insertar("Kirito", 9, 1);
    */

    QString filename = QFileDialog::getOpenFileName(
                this,
                "Selector de archivo",
                "/home/Escritorio/",
                "Archivos de texto *.txt");

    QString texto = lectura(filename);

    if (texto != NULL)
        separar(texto.toLatin1().data());
}

void Principal::on_actionLinealizar_por_Filas_triggered()
{
    matriz->linealizarFila();
}

void Principal::on_actionLinealizar_por_Columnas_triggered()
{
    matriz->linealizarColumna();
}

void Principal::on_actionGraficar_triggered()
{
    arbol->graficar();
}

void Principal::on_actionGraficar_Matriz_triggered()
{
    matriz->graficar(0);
}

void Principal::on_actionEliminar_triggered()
{
    arbol->eliminar("Zero");
    arbol->eliminar("Sakura");
}
