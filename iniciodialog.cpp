#include "iniciodialog.h"
#include "ui_iniciodialog.h"
#include "registrodialog.h"
#include "usuario.h"
#include <QApplication>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <fstream>
#include <QMessageBox>
#include <QSoundEffect>
#include <QMediaPlayer>

inicioDialog::inicioDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inicioDialog)
{
    ui->setupUi(this);
    //connect(ui->iniciarPB, SIGNAL(iniciar()), this, SLOT(hello()));
    //connect(ui->nuevoUPB, SIGNAL(registro()), this, SLOT(on_nuevoUPB_clicked()));
        QFile file("/home/dojx/Documents/C++/applibro/registros.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"Archivo no encontrado";
        }

        QFile fileSalida("out.txt");
        //if (!fileSalida.open(QIODevice::WriteOnly | QIODevice::Text))
          //  return 0;
        QTextStream out(&fileSalida);

        QTextStream in(&file);
            //return 0;
        while (!in.atEnd())
        {
            QString line = in.readLine();
            //qDebug()<<line;
            QStringList campos = line.trimmed().split('|');
            QString nombre = campos[0];
            QString fecha = campos[1];
            QString user = campos[2];
            QString contrasena = campos[3];
            QString correo = campos[4];
            Usuario u;
            u.setNombre(nombre);
            u.setFecha(fecha);
            u.setUser(user);
            u.setContrasena(contrasena);
            u.setCorreo(correo);
            usuarios.push_back(u);
        }
        file.close();
        fileSalida.close();

}

inicioDialog::~inicioDialog()
{
    delete ui;
}

void inicioDialog::on_usuarioLE_textChanged(const QString &arg1)
{
    if (ui->usuarioLE->text().size() > 0 &&
            ui->contrasenaLE->text().size() > 0)
    {
        ui->iniciarPB->setEnabled(true);
    }
    else
    {
        ui->iniciarPB->setEnabled(false);
    }
}

void inicioDialog::on_contrasenaLE_textChanged(const QString &arg1)
{
    if (ui->usuarioLE->text().size() > 0 &&
            ui->contrasenaLE->text().size() > 0)
    {
        ui->iniciarPB->setEnabled(true);
    }
    else
    {
        ui->iniciarPB->setEnabled(false);
    }
}

void inicioDialog::on_iniciarPB_clicked()
{

    int x=1;
    list<Usuario>::iterator it=usuarios.begin();
    while(it!=usuarios.end())
    {
        if(it->getUser()==ui->usuarioLE->text()&&
                it->getContrasena()==ui->contrasenaLE->text())
        {
            QSoundEffect *effect = new QSoundEffect(this);

            effect->setSource(QUrl::fromLocalFile("/home/dojx/Documents/C++/applibro/FALCON_-_PUNCH_.wav"));
            effect->play();
            menuPrincipal *s = new menuPrincipal(this);
            this->hide();
            s->show();
            s->setcurrentuser(it->getNombre(),it->getUser(),it->getCorreo(),it->getFecha(),it->getContrasena());
            x=0;
        }
        it++;
    }
    if(x==1)
    {
        QMessageBox m;
        m.setText("Error: Usuario o contraseña incorrecta");
        m.exec();
    }

}

void inicioDialog::on_nuevoUPB_clicked()
{
    registroDialog *s = new registroDialog(this);
    this->hide();
    s->show();
}

void inicioDialog::consultar()
{

    list<Usuario>::iterator it = usuarios.begin();
    while(it != usuarios.end())
    {
       qDebug()<<"Nombre: " <<it->getNombre() <<endl
            <<"Fecha: " <<it->getFecha() <<endl
           <<"Usuario: " <<it->getUser() <<endl
          <<"Contrasena: " <<it->getContrasena() <<endl
         <<"Correo: " <<it->getCorreo() <<endl
        <<"-----------------------------------" <<endl;

    ++it;
    }
}

void inicioDialog::registrar(QString n,QString f,QString u,QString c,QString co)
{
    int x=1;
    list<Usuario>:: iterator it = usuarios.begin();
    QMessageBox m;
    while(it != usuarios.end())
    {
        if (it->getUser()==u&&it->getCorreo()!=co)
        {
            m.setText("Error!: Usuario ya existe");
            m.exec();
            x=0;
        }
        else if(it->getCorreo()==co&&it->getUser()!=u)
        {
            m.setText("Error!: Correo ya esta registrado");
            m.exec();
            x=0;
        }
        else if(it->getCorreo()==co&&it->getUser()==u)
        {
            m.setText("Error!: Usuario y Correo ya estan registrados");
            m.exec();
            x=0;
        }
        ++it;
    }

    if(x==1)
    {
        Usuario l;
        l.setNombre(n);
        l.setFecha(f);
        l.setUser(u);
        l.setContrasena(c);
        l.setCorreo(co);

        std::ofstream outfile;
        outfile.open("/home/dojx/Documents/C++/applibro/registros.txt", std::ios_base::app);
        outfile <<l.getNombre().toStdString()
           <<"|"<<l.getFecha().toStdString()
          <<"|"<<l.getUser().toStdString()
         <<"|"<<l.getContrasena().toStdString()
        <<"|"<<l.getCorreo().toStdString()<<endl;
    }

}

void inicioDialog::hello()
{
    qDebug("hello");

}



