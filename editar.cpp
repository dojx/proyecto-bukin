#include "editar.h"
#include "ui_editar.h"
#include "menuprincipal.h"
#include <QDate>
#include <QApplication>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <fstream>
#include <QMessageBox>
#include <stdio.h>

editar::editar(QWidget *parent) :
    QWidget(parent,Qt::Window),
    ui(new Ui::editar)
{
    ui->setupUi(this);

}

editar::~editar()
{
    delete ui;
}

void editar::setedit(QString n, QString u, QString f, QString co, QString c)
{
    ecuser.setNombre(n);
    ecuser.setUser(u);
    ecuser.setFecha(f);
    ecuser.setCorreo(co);
    ecuser.setContrasena(c);

    ui->enombreLE->setText(ecuser.getNombre());
    ui->euserLE->setText(ecuser.getUser());
    ui->ecorreoLE->setText(ecuser.getCorreo());
    ui->cnuevaLE->setText(ecuser.getContrasena());
    ui->efechaDE->setDate(QDate::fromString(ecuser.getFecha(),"dd/MM/yyyy"));


}

void editar::on_cactualLE_textChanged(const QString &arg1)
{
    if(ecuser.getContrasena()==ui->cactualLE->text())
    {
        ui->enombreLE->setReadOnly(false);
        ui->efechaDE->setReadOnly(false);
        ui->euserLE->setReadOnly(false);
        ui->cnuevaLE->setReadOnly(false);
        ui->ecorreoLE->setReadOnly(false);
        if (ui->enombreLE->text().size() > 0 &&
                ui->euserLE->text().size()> 0 &&
                ui->ecorreoLE->text().size()> 0 &&
                ui->cnuevaLE->text().size()> 0)
        {
            ui->eguardarPB->setEnabled(true);
        }
        else
        {
            ui->eguardarPB->setEnabled(false);
        }
    }
    else
    {
        ui->enombreLE->setReadOnly(true);
        ui->efechaDE->setReadOnly(true);
        ui->euserLE->setReadOnly(true);
        ui->cnuevaLE->setReadOnly(true);
        ui->ecorreoLE->setReadOnly(true);
        ui->eguardarPB->setEnabled(false);
    }

}

void editar::on_enombreLE_textChanged(const QString &arg1)
{
    if (ui->enombreLE->text().size() > 0 &&
            ui->euserLE->text().size()> 0 &&
            ui->ecorreoLE->text().size()> 0 &&
            ui->cnuevaLE->text().size()> 0 &&
            ecuser.getContrasena()==ui->cactualLE->text())
    {
        ui->eguardarPB->setEnabled(true);
    }
    else
    {
        ui->eguardarPB->setEnabled(false);
    }

}


void editar::on_euserLE_textChanged(const QString &arg1)
{
    if (ui->enombreLE->text().size() > 0 &&
            ui->euserLE->text().size()> 0 &&
            ui->ecorreoLE->text().size()> 0 &&
            ui->cnuevaLE->text().size()> 0 &&
            ecuser.getContrasena()==ui->cactualLE->text())
    {
        ui->eguardarPB->setEnabled(true);
    }
    else
    {
        ui->eguardarPB->setEnabled(false);
    }

}

void editar::on_cnuevaLE_textChanged(const QString &arg1)
{
    if (ui->enombreLE->text().size() > 0 &&
            ui->euserLE->text().size()> 0 &&
            ui->ecorreoLE->text().size()> 0 &&
            ui->cnuevaLE->text().size()> 0 &&
            ecuser.getContrasena()==ui->cactualLE->text())
    {
        ui->eguardarPB->setEnabled(true);
    }
    else
    {
        ui->eguardarPB->setEnabled(false);
    }

}

void editar::on_ecorreoLE_textChanged(const QString &arg1)
{
    if (ui->enombreLE->text().size() > 0 &&
            ui->euserLE->text().size()> 0 &&
            ui->ecorreoLE->text().size()> 0 &&
            ui->cnuevaLE->text().size()> 0 &&
            ecuser.getContrasena()==ui->cactualLE->text())
    {
        ui->eguardarPB->setEnabled(true);
    }
    else
    {
        ui->eguardarPB->setEnabled(false);
    }

}


void editar::on_eguardarPB_clicked()
{
    QFile f("/home/dojx/Documents/C++/applibro/registros.txt");
    if(f.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString s;
        QTextStream t(&f);
        while(!t.atEnd())
        {
            QString line = t.readLine();
            if(!line.contains(ecuser.getUser())&&!line.contains(ecuser.getCorreo()))
                s.append(line + "\n");
        }
        f.resize(0);
        t << s;
        f.close();
    }

    QString usuario=ui->euserLE->text();
    QString old=ecuser.getUser();
    QString bkstxt="_bks.txt";
    QString fvtxt="_fv.txt";
    QString direccion1="/home/dojx/Documents/C++/applibro/libros/"+old+bkstxt;
    QString direccion2="/home/dojx/Documents/C++/applibro/libros/"+usuario+bkstxt;
    QString direccion3="/home/dojx/Documents/C++/applibro/favoritos/"+old+fvtxt;
    QString direccion4="/home/dojx/Documents/C++/applibro/favoritos/"+usuario+fvtxt;

    QByteArray ba = direccion1.toLatin1();
    QByteArray bo = direccion2.toLatin1();
    QByteArray bi = direccion3.toLatin1();
    QByteArray bu = direccion4.toLatin1();

    const char* FileName = ba.data();
    const char* FileName2 = bo.data();
    const char* FileName3 = bi.data();
    const char* FileName4 = bu.data();

    std::rename(FileName,FileName2);
    std::rename(FileName3,FileName4);

    ecuser.setNombre(ui->enombreLE->text());
    ecuser.setUser(ui->euserLE->text());
    ecuser.setFecha(ui->efechaDE->date().toString("dd/MM/yyyy"));
    ecuser.setCorreo(ui->ecorreoLE->text());
    ecuser.setContrasena(ui->cnuevaLE->text());

    std::ofstream outfile;
    outfile.open("/home/dojx/Documents/C++/applibro/registros.txt", std::ios_base::app);
    outfile <<ecuser.getNombre().toStdString()
       <<"|"<<ecuser.getFecha().toStdString()
      <<"|"<<ecuser.getUser().toStdString()
     <<"|"<<ecuser.getContrasena().toStdString()
    <<"|"<<ecuser.getCorreo().toStdString()<<endl;


    menuPrincipal *k=new menuPrincipal(this);

    k->setcurrentuser(ecuser.getNombre(),
                      ecuser.getUser(),
                      ecuser.getCorreo(),
                      ecuser.getFecha(),
                      ecuser.getContrasena());

    this->hide();
    k->show();


}

void editar::on_ecancelarPB_clicked()
{
    menuPrincipal *k=new menuPrincipal(this);
    k->setcurrentuser(ecuser.getNombre(),
                      ecuser.getUser(),
                      ecuser.getCorreo(),
                      ecuser.getFecha(),
                      ecuser.getContrasena());
    this->hide();
    k->show();
}

