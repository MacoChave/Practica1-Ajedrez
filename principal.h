#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
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

private:
    Ui::Principal *ui;
    QString lectura(QString filename);
    void separar(char* texto);
    void insertarMatriz();
};

#endif // PRINCIPAL_H
