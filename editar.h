#ifndef EDITAR_H
#define EDITAR_H

#include <QWidget>
#include "usuario.h"
#include <QDate>

namespace Ui {
class editar;
}

class editar : public QWidget
{
    Q_OBJECT

public:
    explicit editar(QWidget *parent = 0);
    ~editar();
    void setedit(QString n,QString u, QString f,QString co,QString c);

private slots:
    void on_cactualLE_textChanged(const QString &arg1);

    void on_enombreLE_textChanged(const QString &arg1);

    void on_euserLE_textChanged(const QString &arg1);

    void on_cnuevaLE_textChanged(const QString &arg1);

    void on_ecorreoLE_textChanged(const QString &arg1);

    void on_eguardarPB_clicked();

    void on_ecancelarPB_clicked();

private:
    Ui::editar *ui;
    Usuario ecuser;
};

#endif // EDITAR_H
