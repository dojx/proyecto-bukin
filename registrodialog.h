#ifndef REGISTRODIALOG_H
#define REGISTRODIALOG_H

#include <QWidget>

namespace Ui {
class registroDialog;
}

class registroDialog : public QWidget
{
    Q_OBJECT

public:
    explicit registroDialog(QWidget *parent = 0);
    ~registroDialog();

signals:
    void registrar(QString nombre, QString usuario, QString pass);

private slots:
    void on_nuevoNLE_textChanged(const QString &arg1);

    void on_nuevoULE_textChanged(const QString &arg1);

    void on_nuevoCLE_textChanged(const QString &arg1);

    void on_nuevoMLE_textChanged(const QString &arg1);

    void on_registrarPB_clicked();


private:
    Ui::registroDialog *ui;
};

#endif // REGISTRODIALOG_H
