#include "registrodialog.h"
#include "ui_registrodialog.h"
#include "iniciodialog.h"
#include <iostream>
#include <string>
#include <QApplication>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

using namespace std;

registroDialog::registroDialog(QWidget *parent) :
    QWidget(parent,Qt::Window),
    ui(new Ui::registroDialog)
{
    ui->setupUi(this);
    //connect(ui->registrarPB, SIGNAL(registrar()), this, SLOT(on_registrarPB_clicked()));
}

registroDialog::~registroDialog()
{
    delete ui;
}

void registroDialog::on_nuevoNLE_textChanged(const QString &arg1)
{
    if(ui->nuevoNLE->text().size() > 0 &&
            ui->nuevoULE->text().size() > 0 &&
            ui->nuevoCLE->text().size() > 0 &&
            ui->nuevoMLE->text().size() > 0)
    {
        ui->registrarPB->setEnabled(true);
    }
    else
    {
        ui->registrarPB->setEnabled(false);
    }
}

void registroDialog::on_nuevoULE_textChanged(const QString &arg1)
{
    if(ui->nuevoNLE->text().size() > 0 &&
            ui->nuevoULE->text().size() > 0 &&
            ui->nuevoCLE->text().size() > 0 &&
            ui->nuevoMLE->text().size() > 0)
    {
        ui->registrarPB->setEnabled(true);
    }
    else
    {
        ui->registrarPB->setEnabled(false);
    }
}

void registroDialog::on_nuevoCLE_textChanged(const QString &arg1)
{
    if(ui->nuevoNLE->text().size() > 0 &&
            ui->nuevoULE->text().size() > 0 &&
            ui->nuevoCLE->text().size() > 0 &&
            ui->nuevoMLE->text().size() > 0)
    {
        ui->registrarPB->setEnabled(true);
    }
    else
    {
        ui->registrarPB->setEnabled(false);
    }
}

void registroDialog::on_nuevoMLE_textChanged(const QString &arg1)
{
    if(ui->nuevoNLE->text().size() > 0 &&
            ui->nuevoULE->text().size() > 0 &&
            ui->nuevoCLE->text().size() > 0 &&
            ui->nuevoMLE->text().size() > 0)
    {
        ui->registrarPB->setEnabled(true);
    }
    else
    {
        ui->registrarPB->setEnabled(false);
    }
}

void registroDialog::on_registrarPB_clicked()
{
    inicioDialog p;
    QString date = ui->nuevoFDE->date().toString("dd/MM/yyyy");
    p.registrar(ui->nuevoNLE->text(),date,ui->nuevoULE->text(),ui->nuevoCLE->text(),ui->nuevoMLE->text());
    inicioDialog *s = new inicioDialog(this);
    this->hide();
    s->show();
}

