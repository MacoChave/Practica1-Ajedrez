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
    void separar(char* texto);
    void insertarMatriz();
    char torre[6];
    char alfil[6];
    char caballo[8];
    char reina[6];
    char rey[4];
    char peon[5];
    bool turno;
};

#endif // PRINCIPAL_H
