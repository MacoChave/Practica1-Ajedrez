#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include "matriz.h"
#include "abb.h"

namespace Ui {
class Principal;
}

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = 0);
    ~Principal();
    Matriz *matriz;
    ABB *arbol;

private slots:
    void on_actionAbrir_triggered();

    void on_actionLinealizar_por_Filas_triggered();

    void on_actionLinealizar_por_Columnas_triggered();

    void on_actionGraficar_triggered();

    void on_actionGraficar_Matriz_triggered();

    void on_actionEliminar_triggered();

    void on_actionAgregar_triggered();

    void on_btnMover2_clicked();

    void on_btnMover1_clicked();

    void on_actionJugar_triggered();

private:
    Ui::Principal *ui;
    QString lectura(QString filename);
    void splitUsuarios(char* texto);
    void insertarMatriz();
    int filaAsociada(char dato);
    char torre[2];
    char alfil[2];
    char caballo[2];
    char reina[2];
    char rey[2];
    char peon[2];
    bool turno;
};

#endif // PRINCIPAL_H
