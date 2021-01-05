#ifndef INICIODIALOG_H
#define INICIODIALOG_H

#include <QDialog>
#include "menuprincipal.h"
#include "registrodialog.h"
#include "usuario.h"
#include <list>

using namespace std;

namespace Ui {
class inicioDialog;
}

class inicioDialog : public QDialog
{
    Q_OBJECT

public:
    explicit inicioDialog(QWidget *parent = 0);
    ~inicioDialog();

    void consultar();

    void registrar(QString n, QString f, QString u, QString c, QString co);

    void hello();



signals:
    void iniciar();

private slots:
    void on_usuarioLE_textChanged(const QString &arg1);

    void on_contrasenaLE_textChanged(const QString &arg1);

    void on_iniciarPB_clicked();

    void on_nuevoUPB_clicked();

private:
    Ui::inicioDialog *ui;
    list<Usuario> usuarios;
};

#endif // INICIODIALOG_H
