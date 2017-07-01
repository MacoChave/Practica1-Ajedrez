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
    turno = true;
    ui->fmeJugador1->setEnabled(false);
    ui->fmeJugador2->setEnabled(false);

    strcpy(torre, "T");
    strcpy(alfil, "A");
    strcpy(caballo, "C");
    strcpy(reina, "D");
    strcpy(rey, "R");
    strcpy(peon, "P");
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

void Principal::splitUsuarios(char* texto)
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
    /***********************************
     * BLANCAS COLOR = 0
     * BLANCAS NIVEL 0
    ***********************************/
    matriz->insertar(caballo, 0, 8, 1, 0);
    matriz->insertar(alfil, 0, 8, 2, 0);
    matriz->insertar(torre, 0, 8, 3, 0);
    matriz->insertar(rey, 0, 8, 4, 0);
    matriz->insertar(reina, 0, 8, 5, 0);
    matriz->insertar(torre, 0, 8, 6, 0);
    matriz->insertar(alfil, 0, 8, 7, 0);
    matriz->insertar(caballo, 0, 8, 8, 0);
    matriz->insertar(peon, 0, 7, 1, 0);
    matriz->insertar(peon, 0, 7, 2, 0);
    matriz->insertar(peon, 0, 7, 3, 0);
    matriz->insertar(peon, 0, 7, 4, 0);
    matriz->insertar(peon, 0, 7, 5, 0);
    matriz->insertar(peon, 0, 7, 6, 0);
    matriz->insertar(peon, 0, 7, 7, 0);
    matriz->insertar(peon, 0, 7, 8, 0);

    /***********************************
     * BLANCAS NIVEL 1
    ***********************************/
    matriz->insertar(torre, 0, 8, 6, 1);
    matriz->insertar(alfil, 0, 8, 7, 1);
    matriz->insertar(caballo, 0, 8, 8, 1);
    matriz->insertar(peon, 0, 7, 6, 1);
    matriz->insertar(peon, 0, 7, 7, 1);
    matriz->insertar(peon, 0, 7, 8, 1);

    /***********************************
     * BLANCAS NIVEL 2
    ***********************************/
    matriz->insertar(caballo, 0, 8, 1, 2);
    matriz->insertar(alfil, 0, 8, 2, 2);
    matriz->insertar(torre, 0, 8, 3, 2);
    matriz->insertar(peon, 0, 7, 1, 2);
    matriz->insertar(peon, 0, 7, 2, 2);
    matriz->insertar(peon, 0, 7, 3, 2);

    /***********************************
     * NEGRAS COLOR = 1
     * NEGRAS NIVEL 0
    ***********************************/
    matriz->insertar(caballo, 1, 1, 1, 0);
    matriz->insertar(alfil, 1, 1, 2, 0);
    matriz->insertar(torre, 1, 1, 3, 0);
    matriz->insertar(rey, 1, 1, 4, 0);
    matriz->insertar(reina, 1, 1, 5, 0);
    matriz->insertar(torre, 1, 1, 6, 0);
    matriz->insertar(alfil, 1, 1, 7, 0);
    matriz->insertar(caballo, 1, 1, 8, 0);
    matriz->insertar(peon, 1, 2, 1, 0);
    matriz->insertar(peon, 1, 2, 2, 0);
    matriz->insertar(peon, 1, 2, 3, 0);
    matriz->insertar(peon, 1, 2, 4, 0);
    matriz->insertar(peon, 1, 2, 5, 0);
    matriz->insertar(peon, 1, 2, 6, 0);
    matriz->insertar(peon, 1, 2, 7, 0);
    matriz->insertar(peon, 1, 2, 8, 0);

    /***********************************
     * NEGRAS NIVEL 1
    ***********************************/
    matriz->insertar(caballo, 1, 1, 1, 1);
    matriz->insertar(alfil, 1, 1, 2, 1);
    matriz->insertar(torre, 1, 1, 3, 1);
    matriz->insertar(peon, 1, 2, 1, 1);
    matriz->insertar(peon, 1, 2, 2, 1);
    matriz->insertar(peon, 1, 2, 3, 1);

    /***********************************
     * NEGRAS NIVEL 2
    ***********************************/
    matriz->insertar(torre, 1, 1, 6, 2);
    matriz->insertar(alfil, 1, 1, 7, 2);
    matriz->insertar(caballo, 1, 1, 8, 2);
    matriz->insertar(peon, 1, 2, 6, 2);
    matriz->insertar(peon, 1, 2, 7, 2);
    matriz->insertar(peon, 1, 2, 8, 2);
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
        splitUsuarios(texto.toLatin1().data());
}

void Principal::on_actionGraficar_triggered()
{
    arbol->graficar();
    system("/home/marco/Escritorio/arbol.png");
}

void Principal::on_actionAgregar_triggered()
{
    QString usuario = QInputDialog::getText(
                this,
                "Agregar usuario",
                "Ingresar nombre de usuario");
    arbol->insertar(usuario.toLatin1().data(), 0, 0);
}

void Principal::on_actionEliminar_triggered()
{
    QString usuario = QInputDialog::getText(
                this,
                "Eliminar usuario",
                "Ingresar nombre de usuario");

    arbol->eliminar(usuario.toLatin1().data());
}

void Principal::on_actionLinealizar_por_Filas_triggered()
{
    int nivel = QInputDialog::getInt(
                this,
                "Selección de nivel",
                "Ingresar el nivel a linealizar por filas");
    matriz->linealizarFila(nivel);
    system("/home/marco/Escritorio/filas.png");
}

void Principal::on_actionLinealizar_por_Columnas_triggered()
{
    int nivel = QInputDialog::getInt(
                this,
                "Seleccion de nivel",
                "Ingresar el nivel a linealizar por columna");
    matriz->linealizarColumna(nivel);
    system("/home/marco/Escritorio/columnas.png");
}

void Principal::on_actionGraficar_Matriz_triggered()
{
    int nivel = QInputDialog::getInt(
                this,
                "Seleccion de nivel",
                "Ingresar el nivel de matriz");
    matriz->graficar(nivel);
}

int Principal::filaAsociada(char dato)
{
    switch (dato) {
    case 'A':
        return 1;
        break;
    case 'B':
        return 2;
        break;
    case 'C':
        return 3;
        break;
    case 'D':
        return 4;
        break;
    case 'E':
        return 5;
        break;
    case 'F':
        return 6;
        break;
    case 'G':
        return 7;
        break;
    case 'H':
        return 8;
        break;
    default:
        return 0;
        break;
    }
}

void Principal::on_btnMover2_clicked()
{
    char *texto;
    char *dato;
    char *destino;
    int columnaDestino;
    int filaDestino;
    int nivel;
    int color = 0;

    texto = ui->edtMovimiento2->text().toLatin1().data();
    dato = strtok(texto, "-");
    nivel = atoi(strtok(NULL, "-"));
    destino = strtok(NULL, "-");
    filaDestino = filaAsociada(destino[0]);
    columnaDestino = destino[1] - '0';

    if (matriz->mover(dato, color, nivel, filaDestino, columnaDestino))
    {
        turno = !turno;
        ui->fmeJugador2->setEnabled(!turno);
        ui->fmeJugador1->setEnabled(turno);
        ui->edtConsola->setText(ui->edtMovimiento2->text());
        ui->edtMovimiento2->setText("");

        matriz->graficar(0);
        matriz->graficar(1);
        matriz->graficar(2);

        QImage m;
        m.load("/home/marco/Escritorio/Matriz_0");
        ui->lblNivel0->setPixmap(QPixmap::fromImage(m).scaled(ui->lblNivel0->width(), ui->lblNivel0->height(), Qt::KeepAspectRatio));
        m.load("/home/marco/Escritorio/Matriz_1");
        ui->lblNivel1->setPixmap(QPixmap::fromImage(m).scaled(ui->lblNivel1->width(), ui->lblNivel1->height(), Qt::KeepAspectRatio));
        m.load("/home/marco/Escritorio/Matriz_2");
        ui->lblNivel2->setPixmap(QPixmap::fromImage(m).scaled(ui->lblNivel2->width(), ui->lblNivel2->height(), Qt::KeepAspectRatio));
    }
    else
        ui->edtConsola->setText("Movimiento inválido");
}

void Principal::on_btnMover1_clicked()
{
    char *texto;
    char *dato;
    char *destino;
    int columnaDestino;
    int filaDestino;
    int nivel;
    int color = 1;

    texto = ui->edtMovimiento1->text().toLatin1().data();
    dato = strtok(texto, "-");
    nivel = atoi(strtok(NULL, "-"));
    destino = strtok(NULL, "-");
    filaDestino = filaAsociada(destino[0]);
    columnaDestino = destino[1] - '0';

    if (matriz->mover(dato, color, nivel, filaDestino, columnaDestino))
    {
        turno = !turno;
        ui->fmeJugador1->setEnabled(turno);
        ui->fmeJugador2->setEnabled(!turno);

        ui->edtConsola->setText(ui->edtMovimiento1->text());
        ui->edtMovimiento1->setText("");

        matriz->graficar(0);
        matriz->graficar(1);
        matriz->graficar(2);

        QImage m;
        m.load("/home/marco/Escritorio/Matriz_0");
        ui->lblNivel0->setPixmap(QPixmap::fromImage(m).scaled(ui->lblNivel0->width(), ui->lblNivel0->height(), Qt::KeepAspectRatio));
        m.load("/home/marco/Escritorio/Matriz_1");
        ui->lblNivel1->setPixmap(QPixmap::fromImage(m).scaled(ui->lblNivel1->width(), ui->lblNivel1->height(), Qt::KeepAspectRatio));
        m.load("/home/marco/Escritorio/Matriz_2");
        ui->lblNivel2->setPixmap(QPixmap::fromImage(m).scaled(ui->lblNivel2->width(), ui->lblNivel2->height(), Qt::KeepAspectRatio));
    }
    else
        ui->edtConsola->setText("Movimiento inválido");
}

void Principal::on_actionJugar_triggered()
{
    QString usuarioA = QInputDialog::getText(
                this,
                "Usuario 1",
                "Ingresar usuario 1");
    QString usuarioB = QInputDialog::getText(
                this,
                "Usuario 2",
                "Ingresar usuario 2");
    bool a = false, b = false;

    if (arbol->buscar(usuarioA.toLatin1().data()))
        a = true;
    if (arbol->buscar(usuarioB.toLatin1().data()))
        b = true;

    if (a && b)
    {
        ui->edtConsola->setText("Usuarios válidos");
        matriz->graficar(0);
        matriz->graficar(1);
        matriz->graficar(2);

        QImage m;
        m.load("/home/marco/Escritorio/Matriz_0");
        ui->lblNivel0->setPixmap(QPixmap::fromImage(m).scaled(ui->lblNivel0->width(), ui->lblNivel0->height(), Qt::KeepAspectRatio));
        m.load("/home/marco/Escritorio/Matriz_1");
        ui->lblNivel1->setPixmap(QPixmap::fromImage(m).scaled(ui->lblNivel1->width(), ui->lblNivel1->height(), Qt::KeepAspectRatio));
        m.load("/home/marco/Escritorio/Matriz_2");
        ui->lblNivel2->setPixmap(QPixmap::fromImage(m).scaled(ui->lblNivel2->width(), ui->lblNivel2->height(), Qt::KeepAspectRatio));

        ui->lblUser1->setText(usuarioA);
        ui->lblUser2->setText(usuarioB);
        turno = true;
        ui->fmeJugador1->setEnabled(turno);
    }
    else
        ui->edtConsola->setText("Usuarios no válidos.");
}

void Principal::on_actionTop_10_triggered()
{
    arbol->top();
}
