#include <QTextStream>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "principal.h"
#include "ui_principal.h"
#include "reportes.h"

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
    matriz->insertar("Caballo", 0, 8, 1, 0);
    matriz->insertar("Alfil", 0, 8, 2, 0);
    matriz->insertar("Torre", 0, 8, 3, 0);
    matriz->insertar("Rey", 0, 8, 4, 0);
    matriz->insertar("Reina", 0, 8, 5, 0);
    matriz->insertar("Torre", 0, 8, 6, 0);
    matriz->insertar("Alfil", 0, 8, 7, 0);
    matriz->insertar("Caballo", 0, 8, 8, 0);
    matriz->insertar("Peon", 0, 7, 1, 0);
    matriz->insertar("Peon", 0, 7, 2, 0);
    matriz->insertar("Peon", 0, 7, 3, 0);
    matriz->insertar("Peon", 0, 7, 4, 0);
    matriz->insertar("Peon", 0, 7, 5, 0);
    matriz->insertar("Peon", 0, 7, 6, 0);
    matriz->insertar("Peon", 0, 7, 7, 0);
    matriz->insertar("Peon", 0, 7, 8, 0);

    matriz->insertar("Caballo", 1, 1, 1, 0);
    matriz->insertar("Alfil", 1, 1, 2, 0);
    matriz->insertar("Torre", 1, 1, 3, 0);
    matriz->insertar("Rey", 1, 1, 4, 0);
    matriz->insertar("Reina", 1, 1, 5, 0);
    matriz->insertar("Torre", 1, 1, 6, 0);
    matriz->insertar("Alfil", 1, 1, 7, 0);
    matriz->insertar("Caballo", 1, 1, 8, 0);
    matriz->insertar("Peon", 1, 2, 1, 0);
    matriz->insertar("Peon", 1, 2, 2, 0);
    matriz->insertar("Peon", 1, 2, 3, 0);
    matriz->insertar("Peon", 1, 2, 4, 0);
    matriz->insertar("Peon", 1, 2, 5, 0);
    matriz->insertar("Peon", 1, 2, 6, 0);
    matriz->insertar("Peon", 1, 2, 7, 0);
    matriz->insertar("Peon", 1, 2, 8, 0);
}

void Principal::on_actionAbrir_triggered()
{
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
    Reportes *reporteWindow = new Reportes(this);
    reporteWindow->setVisible(true);

    delete(reporteWindow);
}

void Principal::on_actionEliminar_triggered()
{
    QString usuario = QInputDialog::getText(
                this,
                "Eliminar usuario",
                "Ingresar usuario a elliminar");

    arbol->eliminar(usuario.toLatin1().data());
}
