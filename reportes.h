#ifndef REPORTES_H
#define REPORTES_H

#include <QDialog>

namespace Ui {
class Reportes;
}

class Reportes : public QDialog
{
    Q_OBJECT

public:
    explicit Reportes(QWidget *parent = 0);
    ~Reportes();

private:
    Ui::Reportes *ui;
};

#endif // REPORTES_H
