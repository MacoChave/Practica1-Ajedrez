#include "principal.h"
#include "ui_principal.h"

Principal::Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principal)
{
    matriz = new Matriz();
    ui->setupUi(this);
    //insertarMatriz();
}

Principal::~Principal()
{
    delete ui;
}

QString Principal::lectura(QString filename)
{
    /*
    QFile file(filename);

    if (!file.open(QFile::ReadOnly | QFile::Text))
        return NULL;
    else
    {
        QTextStream in (&file);
        QString texto = in.readAll();

        file.close();

        return texto;
    }
    */
}

void Principal::separar(char* texto)
{
    /*
    bool fin = false;

    char *artista;
    char *album;
    char *cancion;
    char *path;
    float valoracion;

    artista = strtok(texto, "_\n");
    album = strtok(NULL, "_\n");
    cancion = strtok(NULL, "_\n");
    path = strtok(NULL, "_\n");
    valoracion = atof(strtok(NULL, "_\n"));

    lista->add(artista, album, cancion, path, valoracion);
    while (!fin)
    {
        artista = strtok(NULL, "_\n");

        if (strcmp(artista, "#") != 0)
        {
            album = strtok(NULL, "_\n");
            cancion = strtok(NULL, "_\n");
            path = strtok(NULL, "_\n");
            valoracion = atof(strtok(NULL, "_\n"));

            lista->add(artista, album, cancion, path, valoracion);
        }
        else
            fin = true;
    }
    */
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
    matriz->graficarFilas();
}

void Principal::on_actionLinealizar_por_Columnas_triggered()
{
    matriz->graficarColumnas();
}
