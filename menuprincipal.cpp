#include "menuprincipal.h"
#include "ui_menuprincipal.h"
#include "libro.h"
#include "usuario.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include "editar.h"
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>
#include <iostream>
#include <fstream>
#include <QMediaPlayer>

menuPrincipal::menuPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menuPrincipal)
{
    ui->setupUi(this);
    QMediaPlayer *effect = new QMediaPlayer(this);
    effect->setMedia(QUrl::fromLocalFile("/home/dojx/Documents/C++/applibro/All_Star_-_Smash_Mouth_[Lyrics].mp3"));
    //effect->play();


    QFile file("/home/dojx/Documents/C++/applibro/libros.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Archivo no encontrado";
        //return 0;
    }
    QFile fileSalida("out.txt");
    QTextStream out(&fileSalida);
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        //qDebug()<<line;
        QStringList campos = line.trimmed().split('|');
        QString titulo = campos[0];
        QString autor = campos[1];
        QString editorial = campos[2];
        QString anio = campos[3];
        QString tipo = campos[4];
        libro l;
        l.setTitulo(titulo);
        l.setAutor(autor);
        l.setEditorial(editorial);
        l.setAnio(anio);
        l.setTipo(tipo);
        libros.push_back(l);
    }
    file.close();
    fileSalida.close();


    ui->librostreeWidget->setHeaderHidden(false);
    ui->mislibrostreeWidget->setHeaderHidden(false);
    ui->favoritostreeWidget->setHeaderHidden(false);
    ui->categoriastreeWidget->setHeaderHidden(false);
}

menuPrincipal::~menuPrincipal()
{
    delete ui;
}

void menuPrincipal::setcurrentuser(QString n, QString u, QString co, QString f, QString c)
{
    cuser.setNombre(n);
    cuser.setFecha(f);
    cuser.setUser(u);
    cuser.setContrasena(c);
    cuser.setCorreo(co);

    ui->listWidgetPerfil->addItem("Nombre: "+cuser.getNombre());
    ui->listWidgetPerfil->addItem("Nombre de Usuario: "+cuser.getUser());
    ui->listWidgetPerfil->addItem("Correo: "+cuser.getCorreo());
    ui->listWidgetPerfil->addItem("Fecha de Nacimiento: "+cuser.getFecha());

    cargarfavoritos();
    cargarmislibros();
    //cargarrecomendados();
}
void menuPrincipal::hideprincipal()
{
    this->hide();
}

void menuPrincipal::addroot(QString title, QString author, QString publish, QString year, QString genre, int tree)
{    
    QTreeWidgetItem *itm;
    if(tree==2)
    {
        itm = new QTreeWidgetItem(ui->favoritostreeWidget);
        itm->setCheckState(1, Qt::Checked);
        itm->setText(0,title);
        //ui->librostreeWidget->addTopLevelItem(itm);
        addchild(itm,"Autor: "+author);
        addchild(itm,"Editorial: "+publish);
        addchild(itm,"Anio: "+year);
        addchild(itm,"Genero: "+genre);
    }
    else
    {
        if(tree==0)
        {
            itm = new QTreeWidgetItem(ui->librostreeWidget);
        }
        else if(tree==1)
        {
            itm = new QTreeWidgetItem(ui->mislibrostreeWidget);
        }
        else if(tree==3)
        {
            itm = new QTreeWidgetItem(ui->categoriastreeWidget);
        }
        else if(tree==4)
        {
            itm = new QTreeWidgetItem(ui->recomendadostreeWidget);
        }
        itm->setCheckState(1, Qt::Unchecked);
        itm->setCheckState(2, Qt::Unchecked);
        list<libro>::iterator it=mislibros.begin();
        while(it!=mislibros.end())
        {
            if(title==it->getTitulo())
            {
                itm->setCheckState(1, Qt::Checked);
            }
            it++;
        }
        it=favoritos.begin();
        while(it!=favoritos.end())
        {
            if(title==it->getTitulo())
            {
                itm->setCheckState(2, Qt::Checked);
            }
            it++;
        }
        itm->setText(0,title);
        //ui->librostreeWidget->addTopLevelItem(itm);
        addchild(itm,"Autor: "+author);
        addchild(itm,"Editorial: "+publish);
        addchild(itm,"Anio: "+year);
        addchild(itm,"Genero: "+genre);
    }

}


void menuPrincipal::addchild(QTreeWidgetItem *parent, QString info)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0,info);
    parent->addChild(itm);
}

void menuPrincipal::setmislibrostw()
{
    ui->mislibrostreeWidget->clear();
    list<libro>::iterator it=mislibros.begin();
    while(it!=mislibros.end())
    {
        addroot(it->getTitulo(),it->getAutor(),it->getEditorial(),it->getAnio(),it->getTipo(),1);
        it++;
    }
    ui->mislibrostreeWidget->resizeColumnToContents(0);
    setmislibrostxt();
}

void menuPrincipal::cargarmislibros()
{   
    QString usuario=cuser.getUser();
    QString bkstxt="_bks.txt";
    QString direccion="/home/dojx/Documents/C++/applibro/libros/"+usuario+bkstxt;
    QFile file(direccion);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray ba = direccion.toLatin1();
        const char* FileName = ba.data();
        std::ofstream outfile(FileName);
        outfile.close();
        //qDebug()<<"Archivo no encontrado";
        //return 0;
    }
    QFile fileSalida("out.txt");
    QTextStream out(&fileSalida);
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        //qDebug()<<line;
        QStringList campos = line.trimmed().split('|');
        QString titulo = campos[0];
        QString autor = campos[1];
        QString editorial = campos[2];
        QString anio = campos[3];
        QString tipo = campos[4];
        libro l;
        l.setTitulo(titulo);
        l.setAutor(autor);
        l.setEditorial(editorial);
        l.setAnio(anio);
        l.setTipo(tipo);
        mislibros.push_back(l);
    }
    file.close();
    fileSalida.close();
    setmislibrostw();
}

void menuPrincipal::setfavoritostw()
{
    ui->favoritostreeWidget->clear();
    list<libro>::iterator it=favoritos.begin();
    while(it!=favoritos.end())
    {
        addroot(it->getTitulo(),it->getAutor(),it->getEditorial(),it->getAnio(),it->getTipo(),2);
        it++;
    }
    ui->favoritostreeWidget->resizeColumnToContents(0);
    setfavoritostxt();
}

void menuPrincipal::cargarfavoritos()
{    
    QString usuario=cuser.getUser();
    QString fvtxt="_fv.txt";
    QString direccion="/home/dojx/Documents/C++/applibro/favoritos/"+usuario+fvtxt;
    QFile file(direccion);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray ba = direccion.toLatin1();
        const char* FileName = ba.data();
        std::ofstream outfile(FileName);
        outfile.close();
        qDebug()<<"Archivo no encontrado";
        //return 0;
    }
    QFile fileSalida("out.txt");
    QTextStream out(&fileSalida);
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        //qDebug()<<line;
        QStringList campos = line.trimmed().split('|');
        QString titulo = campos[0];
        QString autor = campos[1];
        QString editorial = campos[2];
        QString anio = campos[3];
        QString tipo = campos[4];
        libro l;
        l.setTitulo(titulo);
        l.setAutor(autor);
        l.setEditorial(editorial);
        l.setAnio(anio);
        l.setTipo(tipo);
        favoritos.push_back(l);
    }
    file.close();
    fileSalida.close();
    setfavoritostw();
}


void menuPrincipal::setmislibrostxt()
{
    QString usuario=cuser.getUser();
    QString bkstxt="_bks.txt";
    QString direccion="/home/dojx/Documents/C++/applibro/libros/"+usuario+bkstxt;

    QByteArray ba = direccion.toLatin1();
    const char* FileName = ba.data();

    std::ofstream outfile(FileName);

    list<libro>::iterator it=mislibros.begin();
    while(it!=mislibros.end())
    {
        outfile << it->getTitulo().toStdString()
                << "|" << it->getAutor().toStdString()
                   << "|" << it->getEditorial().toStdString()
                      << "|" << it->getAnio().toStdString()
                      << "|" << it->getTipo().toStdString() <<endl;
        it++;
    }
    outfile.close();
}

void menuPrincipal::setfavoritostxt()
{
    QString usuario=cuser.getUser();
    QString fvtxt="_fv.txt";
    QString direccion="/home/dojx/Documents/C++/applibro/favoritos/"+usuario+fvtxt;

    QByteArray ba = direccion.toLatin1();
    const char* FileName = ba.data();

    std::ofstream outfile(FileName);

    list<libro>::iterator it=favoritos.begin();
    while(it!=favoritos.end())
    {
        outfile << it->getTitulo().toStdString()
                << "|" << it->getAutor().toStdString()
                   << "|" << it->getEditorial().toStdString()
                      << "|" << it->getAnio().toStdString()
                      << "|" << it->getTipo().toStdString() <<endl;
        it++;
    }
    outfile.close();
}

void menuPrincipal::buscarcategoria(QString categ)
{
    ui->categoriastreeWidget->clear();
    list<libro>::iterator it=libros.begin();
    while(it!=libros.end())
    {
        if(it->getTipo()==categ)
        {
            addroot(it->getTitulo(),it->getAutor(),it->getEditorial(),it->getAnio(),it->getTipo(),3);
        }
        it++;
    }
    ui->categoriastreeWidget->resizeColumnToContents(0);
    ordenlibro=2;
    ordenautor=2;
    ordenanio=2;
    ordenpublish=2;
    ordentipo=2;
}

void menuPrincipal::ordenardatos(int l, int m)
{
    QString dato;
    int dat;
    if(m==1)
    {
        if(ordenautor==2)
            ordenautor=1;
        else
            ordenautor=2;
        ordenlibro=2;
        ordenanio=2;
        ordentipo=2;
        ordenpublish=2;
        dato="Autor:";
        dat=ordenautor;


    }
    else if(m==2)
    {
        if(ordenanio==2)
            ordenanio=1;
        else
            ordenanio=2;
        ordenlibro=2;
        ordentipo=2;
        ordenautor=2;
        ordenpublish=2;
        dato="Anio:";
        dat=ordenanio;
    }
    else if(m==3)
    {
        if(ordenpublish==2)
            ordenpublish=1;
        else
            ordenpublish=2;
        ordenlibro=2;
        ordenanio=2;
        ordenautor=2;
        ordentipo=2;
        dato="Editorial:";
        dat=ordenpublish;
    }
    else if(m==4)
    {
        if(ordentipo==2)
            ordentipo=1;
        else
            ordentipo=2;
        ordenlibro=2;
        ordenanio=2;
        ordenautor=2;
        ordenpublish=2;
        dato="Genero:";
        dat=ordentipo;
    }


    int i=0,x,y;
    QString datos[500];
    QTreeWidget *tree;
    if(l==1)
        tree=ui->librostreeWidget;
    else if(l==2)
        tree=ui->mislibrostreeWidget;
    else if(l==3)
        tree=ui->favoritostreeWidget;
    else if(l==4)
        tree=ui->categoriastreeWidget;
    QTreeWidgetItemIterator it(tree);
    while(*it)
    {
        QVariant w;
        w = (*it)->data(0, 0);
        if(w.toString().contains(dato))
        {
            x=0;
            y=0;
            do
            {
                if(w.toString()==datos[x])
                {
                    y=1;
                }
                x++;

            }while(x<i);

            if(y==0)
            {

                datos[i]=w.toString();
                i++;
            }
          }
        it++;
    }
    if(l==1)
         ui->librostreeWidget->clear();
    else if(l==2)
        ui->mislibrostreeWidget->clear();
    else if(l==3)
        ui->favoritostreeWidget->clear();
    else if(l==4)
        ui->categoriastreeWidget->clear();
    for(x=0;x<i-1;x++)
    {
        for(y=0;y<i-1-x;y++)
        {
            if(dat==1)
            {
                if(datos[y].compare(datos[y+1],Qt::CaseInsensitive)>0)
                {

                    QString cambio=datos[y];
                    datos[y]=datos[y+1];
                    datos[y+1]=cambio;
                }
            }
            else if(dat==2)
            {
                if(datos[y+1].compare(datos[y],Qt::CaseInsensitive)>0)
                {

                    QString cambio=datos[y];
                    datos[y]=datos[y+1];
                    datos[y+1]=cambio;
                }
            }

        }
    }
    for(x=0;x<i;x++)
    {
        qDebug()<<datos[x];
        if(l==1)
        {
            list<libro>::iterator iti=libros.begin();
            while(iti!=libros.end())
            {
                if(m==2)
                {
                    dato="Anio: "+iti->getAnio();
                    if(datos[x]==dato&&
                            iti->getTitulo().contains(ui->libroLE->text(),Qt::CaseInsensitive) &&
                            iti->getAutor().contains(ui->autorLE->text(),Qt::CaseInsensitive) &&
                            iti->getEditorial().contains(ui->editorialLE->text(),Qt::CaseInsensitive) &&
                            iti->getAnio().contains(ui->anioLE->text(),Qt::CaseInsensitive) &&
                            iti->getTipo().contains(ui->categoriaLE->text(),Qt::CaseInsensitive))
                    {
                         addroot(iti->getTitulo(),iti->getAutor(),iti->getEditorial(),iti->getAnio(),iti->getTipo(),0);
                    }
                }
                else
                {
                    if(m==1)
                        dato=iti->getAutor();
                    else if(m==3)
                        dato=iti->getEditorial();
                    else if(m==4)
                        dato=iti->getTipo();
                    if(datos[x].contains(dato)&&
                            iti->getTitulo().contains(ui->libroLE->text(),Qt::CaseInsensitive) &&
                            iti->getAutor().contains(ui->autorLE->text(),Qt::CaseInsensitive) &&
                            iti->getEditorial().contains(ui->editorialLE->text(),Qt::CaseInsensitive) &&
                            iti->getAnio().contains(ui->anioLE->text(),Qt::CaseInsensitive) &&
                            iti->getTipo().contains(ui->categoriaLE->text(),Qt::CaseInsensitive))
                    {
                         addroot(iti->getTitulo(),iti->getAutor(),iti->getEditorial(),iti->getAnio(),iti->getTipo(),0);
                    }
                }

                iti++;
            }
        }
        else if(l==2)
        {
            list<libro>::iterator iti=mislibros.begin();
            while(iti!=mislibros.end())
            {
                if(m==2)
                {
                    dato="Anio: "+iti->getAnio();
                    if(datos[x]==dato)
                    {
                         addroot(iti->getTitulo(),iti->getAutor(),iti->getEditorial(),iti->getAnio(),iti->getTipo(),1);
                    }
                }
                else
                {
                    if(m==1)
                        dato=iti->getAutor();
                    else if(m==3)
                        dato=iti->getEditorial();
                    else if(m==4)
                        dato=iti->getTipo();
                    if(datos[x].contains(dato))
                    {
                         addroot(iti->getTitulo(),iti->getAutor(),iti->getEditorial(),iti->getAnio(),iti->getTipo(),1);
                    }
                }
                iti++;
            }
        }
        else if(l==3)
        {
            list<libro>::iterator iti=favoritos.begin();
            while(iti!=favoritos.end())
            {
                if(m==2)
                {
                    dato="Anio: "+iti->getAnio();
                    if(datos[x]==dato)
                    {
                         addroot(iti->getTitulo(),iti->getAutor(),iti->getEditorial(),iti->getAnio(),iti->getTipo(),2);
                    }
                }
                else
                {
                    if(m==1)
                        dato=iti->getAutor();
                    else if(m==3)
                        dato=iti->getEditorial();
                    else if(m==4)
                        dato=iti->getTipo();
                    if(datos[x].contains(dato))
                    {
                         addroot(iti->getTitulo(),iti->getAutor(),iti->getEditorial(),iti->getAnio(),iti->getTipo(),2);
                    }
                }
                iti++;
            }
        }
        else if(l==4)
        {
            QString catego;
            if(cate==1)
                catego="Antología";
            else if(cate==2)
                catego="Biografía";
            else if(cate==3)
                catego="Clásico";
            else if(cate==4)
                catego="Drama";
            else if(cate==5)
                catego="Expositivo";
            else if(cate==6)
                catego="Epistolar";
            else if(cate==7)
                catego="Narrativa";
            else if(cate==8)
                catego="Obra gráfica";
            else if(cate==9)
                catego="Poesía";
            else if(cate==10)
                catego="Referencia";
            list<libro>::iterator iti=libros.begin();
            while(iti!=libros.end())
            {
                if(m==2)
                {
                    dato="Anio: "+iti->getAnio();
                    if(datos[x]==dato&&iti->getTipo()==catego)
                    {
                         addroot(iti->getTitulo(),iti->getAutor(),iti->getEditorial(),iti->getAnio(),iti->getTipo(),3);
                    }
                }
                else
                {
                    if(m==1)
                        dato=iti->getAutor();
                    else if(m==3)
                        dato=iti->getEditorial();
                    if(datos[x].contains(dato)&&iti->getTipo()==catego)
                    {
                         addroot(iti->getTitulo(),iti->getAutor(),iti->getEditorial(),iti->getAnio(),iti->getTipo(),3);
                    }
                }

                iti++;
            }
        }

    }
    ui->favoritostreeWidget->resizeColumnToContents(0);
}

void menuPrincipal::generagrafo()
{
    //lista de usaurioss
    std::list<Usuario> usaurioss;
    QFile file("/home/dojx/Documents/C++/applibro/registros.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug()<<"Archivo no encontrado";
    QFile fileSalida("out.txt");
    QTextStream out(&fileSalida);
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList campos = line.trimmed().split('|');
        QString user = campos[2];
        Usuario u;
        u.setUser(user);
        usaurioss.push_back(u);
    }
    file.close();
    fileSalida.close();

    //libross
    std::list<libro> libross;
    QFile file2("/home/dojx/Documents/C++/applibro/libros.txt");
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Archivo no encontrado";
        //return 0;
    }
    QFile fileSalida2("out.txt");
    QTextStream out2(&fileSalida2);
    QTextStream in2(&file2);
    while (!in2.atEnd())
    {
        QString line = in2.readLine();
        QStringList campos = line.trimmed().split('|');
        QString titulo = campos[0]+'('+campos[3]+')';
        libro n;
        n.setTitulo(titulo);
        libross.push_back(n);
    }
    file2.close();
    fileSalida2.close();


    //grafos y aristas
    QHash<QString, int> aristas;
    list<QString> origens;

    list<libro>::iterator itep=libross.begin();
    while(itep!=libross.end())
    {
        aristas.clear();
        list<Usuario>::iterator it=usaurioss.begin();
        while(it!=usaurioss.end())
        {

            std::list<libro> mislibross;
            std::list<libro> favoritoss;
            QString usuario=it->getUser();
            QString direccion1="/home/dojx/Documents/C++/applibro/libros/"+usuario+"_bks.txt";
            QString direccion2="/home/dojx/Documents/C++/applibro/favoritos/"+usuario+"_fv.txt";

            //mislibross
            QFile file3(direccion1);
            if (!file3.open(QIODevice::ReadOnly | QIODevice::Text))
                qDebug()<<"Archivo no encontrado";
            QFile fileSalida3("out.txt");
            QTextStream out3(&fileSalida3);
            QTextStream in3(&file3);
            while (!in3.atEnd())
            {
                QString line = in3.readLine();
                QStringList campos = line.trimmed().split('|');
                QString titulo = campos[0]+'('+campos[3]+')';
                libro n;
                n.setTitulo(titulo);
                mislibross.push_back(n);
            }
            file3.close();
            fileSalida3.close();

            //favoritoss
            QFile file4(direccion2);
            if (!file4.open(QIODevice::ReadOnly | QIODevice::Text))
                qDebug()<<"Archivo no encontrado";
            QFile fileSalida4("out.txt");
            QTextStream out4(&fileSalida4);
            QTextStream in4(&file4);
            while (!in4.atEnd())
            {
                QString line = in4.readLine();
                QStringList campos = line.trimmed().split('|');
                QString titulo = campos[0]+'('+campos[3]+')';
                libro m;
                m.setTitulo(titulo);
                favoritoss.push_back(m);
            }
            file4.close();
            fileSalida4.close();


            int mlcontain=0;
            list<libro>::iterator ita=mislibross.begin();
            while(ita!=mislibross.end())
            {
                int repi=1;
                if(itep!=libross.begin())
                {
                    if(itep->getTitulo()==ita->getTitulo())
                    {
                        list<QString>::iterator itu=origens.begin();
                        while(itu!=origens.end())
                        {
                            if(itu->toStdString()==ita->getTitulo().toStdString())
                                repi=0;
                            itu++;
                        }
                        if(repi==1)
                            mlcontain=1;
                    }

                }
                else if(itep->getTitulo()==ita->getTitulo())
                {
                   mlcontain=1;
                }
                ita++;
            }
            if(mlcontain==1)
            {
                ita=mislibross.begin();
                while(ita!=mislibross.end())
                {
                    if(itep->getTitulo()!=ita->getTitulo())
                    {
                        aristas[ita->getTitulo()]+=1;
                    }
                    ita++;
                }
            }

            int fvcontain=0;
            ita=favoritoss.begin();
            while(ita!=favoritoss.end())
            {
                int repi=1;
                if(itep!=libross.begin())
                {
                    if(itep->getTitulo()==ita->getTitulo())
                    {
                        list<QString>::iterator itu=origens.begin();
                        while(itu!=origens.end())
                        {
                            if(itu->toStdString()==ita->getTitulo().toStdString())
                                repi=0;
                            itu++;
                        }
                        if(repi==1)
                           fvcontain=1;
                    }

                }
                else if(itep->getTitulo()==ita->getTitulo())
                {
                   fvcontain=1;
                }
                ita++;
            }
            if(fvcontain==1)
            {
                ita=favoritoss.begin();
                while(ita!=favoritoss.end())
                {
                    if(itep->getTitulo()!=ita->getTitulo())
                    {
                        aristas[ita->getTitulo()]+=5;
                    }
                    ita++;
                }
            }

            it++;
        }
        grafo.insert(itep->getTitulo(),aristas);
        origens.push_back(itep->getTitulo());
        itep++;
    }

//    //imprimir
//    QHash<QString, QHash<QString, int> >::iterator origenes= grafo.begin();
//    while(origenes != grafo.end())
//    {
//        QHash<QString, int>::iterator destinos = origenes.value().begin();
//        while(destinos != origenes.value().end())
//        {
//            if(destinos.value()!=0)
//            {
//                qDebug()<<origenes.key() << ":"
//                       <<destinos.key() <<"," << destinos.value();
//            }

//            ++destinos;
//        }
//        ++origenes;
//    }

}

void menuPrincipal::cargarrecomendados()
{
    generagrafo();
    int z=0;
    bool yaesta;
    QHash<QString, QHash<QString, int> >::iterator origenes= grafo.begin();
    while(origenes != grafo.end())
    {
        qDebug()<<origenes.key();
        list<libro>::iterator it=mislibros.begin();
        while(it!=mislibros.end())
        {
            if(origenes.key().contains(it->getTitulo()))
            {
                QHash<QString, int>::iterator destinos = origenes.value().begin();
                while(destinos != origenes.value().end())
                {
                    yaesta=false;
                    for(z=0;z<tam-1;z++)
                    {
                        if(recomendados[z]==destinos.key()
                                &&valores[z]<destinos.value())
                        {
                            valores[z]=destinos.value();
                            yaesta=true;
                            z=tam;
                        }
                        else if(recomendados[z]==destinos.key()
                                &&valores[z]>destinos.value())
                        {
                            yaesta=true;
                            z=tam;
                        }
                    }
                    if(yaesta==false)
                    {
                        recomendados[tam]=destinos.key();
                        valores[tam]=destinos.value();
                        tam++;
                    }
                    ++destinos;
                }
            }
            it++;
        }

        ++origenes;
    }
   ordenarrecomendados();
}

void menuPrincipal::ordenarrecomendados()
{
    int x,y;
    for(x=0;x<tam-1;x++)
    {
        for(y=0;y<tam-1-x;y++)
        {
            if(valores[y]<valores[y+1])
            {
                QString cambio=recomendados[y];
                int change=valores[y];
                recomendados[y]=recomendados[y+1];
                recomendados[y+1]=cambio;
                valores[y]=valores[y+1];
                valores[y+1]=change;
            }
        }
    }
    for(x=0;x<tam-1;x++)
    {
        qDebug()<<recomendados[x];
        qDebug()<<valores[x];

    }
}


void menuPrincipal::on_libroLE_textChanged(const QString &arg1)
{
    if (ui->libroLE->text().size() > 0 ||
            ui->autorLE->text().size() > 0 ||
            ui->editorialLE->text().size() > 0 ||
            ui->anioLE->text().size() > 0 ||
            ui->categoriaLE->text().size() > 0)
    {
        ui->buscarPB->setEnabled(true);
    }
    else
    {
        ui->buscarPB->setEnabled(false);
    }
}

void menuPrincipal::on_autorLE_textChanged(const QString &arg1)
{
    if (ui->libroLE->text().size() > 0 ||
            ui->autorLE->text().size() > 0 ||
            ui->editorialLE->text().size() > 0 ||
            ui->anioLE->text().size() > 0 ||
            ui->categoriaLE->text().size() > 0)
    {
        ui->buscarPB->setEnabled(true);
    }
    else
    {
        ui->buscarPB->setEnabled(false);
    }

}

void menuPrincipal::on_anioLE_textChanged(const QString &arg1)
{
    if (ui->libroLE->text().size() > 0 ||
            ui->autorLE->text().size() > 0 ||
            ui->editorialLE->text().size() > 0 ||
            ui->anioLE->text().size() > 0 ||
            ui->categoriaLE->text().size() > 0)
    {
        ui->buscarPB->setEnabled(true);
    }
    else
    {
        ui->buscarPB->setEnabled(false);
    }
}

void menuPrincipal::on_editorialLE_textChanged(const QString &arg1)
{
    if (ui->libroLE->text().size() > 0 ||
            ui->autorLE->text().size() > 0 ||
            ui->editorialLE->text().size() > 0 ||
            ui->anioLE->text().size() > 0 ||
            ui->categoriaLE->text().size() > 0)
    {
        ui->buscarPB->setEnabled(true);
    }
    else
    {
        ui->buscarPB->setEnabled(false);
    }
}

void menuPrincipal::on_categoriaLE_textChanged(const QString &arg1)
{
    if (ui->libroLE->text().size() > 0 ||
            ui->autorLE->text().size() > 0 ||
            ui->editorialLE->text().size() > 0 ||
            ui->anioLE->text().size() > 0 ||
            ui->categoriaLE->text().size() > 0)
    {
        ui->buscarPB->setEnabled(true);
    }
    else
    {
        ui->buscarPB->setEnabled(false);
    }
}

void menuPrincipal::on_buscarPB_clicked()
{
    ui->librostreeWidget->clear();
    list<libro>::iterator it=libros.begin();
    while(it!=libros.end())
    {
        if(it->getTitulo().contains(ui->libroLE->text(),Qt::CaseInsensitive) &&
                it->getAutor().contains(ui->autorLE->text(),Qt::CaseInsensitive) &&
                it->getEditorial().contains(ui->editorialLE->text(),Qt::CaseInsensitive) &&
                it->getAnio().contains(ui->anioLE->text(),Qt::CaseInsensitive) &&
                it->getTipo().contains(ui->categoriaLE->text(),Qt::CaseInsensitive))
        {
            addroot(it->getTitulo(),it->getAutor(),it->getEditorial(),it->getAnio(),it->getTipo(),0);
        }
        it++;
    }
    ui->librostreeWidget->resizeColumnToContents(0);
    ordenlibro=2;
    ordenautor=2;
    ordenanio=2;
    ordenpublish=2;
    ordentipo=2;

}

void menuPrincipal::on_editarperfilPB_clicked()
{
    editar *s=new editar(this);
    this->hide();
    s->show();
    s->setedit(cuser.getNombre(),cuser.getUser(),cuser.getFecha(),cuser.getCorreo(),cuser.getContrasena());
}

void menuPrincipal::on_librostreeWidget_clicked(const QModelIndex &index)
{
    QTreeWidgetItemIterator it(ui->librostreeWidget);
    while (*it)
    {
        if ((*it)->checkState(1) == 0 &&(*it)->checkState(2) == 2)
        {
            (*it)->setCheckState(1,Qt::Checked);
        }
        ++it;
    }
}

void menuPrincipal::on_guardarmlPB_clicked()
{
    int x,y;
    QTreeWidgetItemIterator it(ui->mislibrostreeWidget);
    while (*it)
    {
        x=1;
        y=1;
        if((*it)->checkState(1) == 2 &&
                (*it)->checkState(2) == 2)
        {
            QVariant w;
            QVariant b;
            //qDebug()<<(*it)->data(0,);
            w = (*it)->data(0, 0);
            list<libro>::iterator ite=libros.begin();
            while(ite!=libros.end())
            {
                if(ite->getTitulo() == w.toString())
                {
                    list<libro>::iterator iti=mislibros.begin();
                    while(iti!=mislibros.end())
                    {
                        if(ite->getTitulo()==iti->getTitulo())
                        {
                            y=0;
                        }
                        iti++;
                    }
                    iti=favoritos.begin();
                    while(iti!=favoritos.end())
                    {
                        if(ite->getTitulo()==iti->getTitulo())
                        {
                            x=0;
                        }
                        iti++;
                    }
                    if(x==1)
                    {
                        libro l;
                        l.setTitulo(ite->getTitulo());
                        l.setAutor(ite->getAutor());
                        l.setEditorial(ite->getEditorial());
                        l.setAnio(ite->getAnio());
                        l.setTipo(ite->getTipo());
                        favoritos.push_back(l);
                        if(y==1)
                        {
                            mislibros.push_back(l);
                        }
                    }
                }
                ite++;
            }
        }
        else if((*it)->checkState(1) == 2 && (*it)->checkState(2) == 0)
        {
            QVariant w;
            w = (*it)->data(0, 0);
            list<libro>::iterator ite=libros.begin();
            while(ite!=libros.end())
            {
                if(ite->getTitulo() == w.toString())
                {
                    list<libro>::iterator iti=mislibros.begin();
                    while(iti!=mislibros.end())
                    {
                        if(ite->getTitulo()==iti->getTitulo())
                        {
                            x=0;
                        }
                        iti++;
                    }
                    if(x==1)
                    {
                        libro l;
                        l.setTitulo(ite->getTitulo());
                        l.setAutor(ite->getAutor());
                        l.setEditorial(ite->getEditorial());
                        l.setAnio(ite->getAnio());
                        l.setTipo(ite->getTipo());
                        mislibros.push_back(l);
                    }
                }
                ite++;
            }
            list<libro>::iterator ito=favoritos.begin();
            while(ito!=favoritos.end())
            {
                if(ito->getTitulo() == w.toString())
                {
                    ito = favoritos.erase(ito);
                }
                else
                {
                    ito++;
                }
            }
        }
        else
        {
            QVariant p;
            p = (*it)->data(0, 0);
            list<libro>::iterator ito=mislibros.begin();
            while(ito!=mislibros.end())
            {
                if(ito->getTitulo() == p.toString())
                {
                    ito = mislibros.erase(ito);
                }
                else
                {
                    ito++;
                }
            }

            ito=favoritos.begin();
            while(ito!=favoritos.end())
            {
                if(ito->getTitulo() == p.toString())
                {
                    ito = favoritos.erase(ito);
                }
                else
                {
                    ito++;
                }
            }
        }
        ++it;
    }
    setmislibrostw();
    setfavoritostw();
    if (ui->libroLE->text().size() > 0 ||
            ui->autorLE->text().size() > 0 ||
            ui->editorialLE->text().size() > 0 ||
            ui->anioLE->text().size() > 0 ||
            ui->categoriaLE->text().size() > 0)
    {
        on_buscarPB_clicked();
    }

}

void menuPrincipal::on_guardarbPB_clicked()
{
    int x,y;
    QTreeWidgetItemIterator it(ui->librostreeWidget);
    while (*it)
    {
        x=1;
        y=1;
        if((*it)->checkState(1) == 2 &&
                (*it)->checkState(2) == 2)
        {
            QVariant w;
            w = (*it)->data(0, 0);
            list<libro>::iterator ite=libros.begin();
            while(ite!=libros.end())
            {
                if(ite->getTitulo() == w.toString())
                {
                    list<libro>::iterator iti=mislibros.begin();
                    while(iti!=mislibros.end())
                    {
                        if(ite->getTitulo()==iti->getTitulo())
                        {
                            y=0;
                        }
                        iti++;
                    }
                    iti=favoritos.begin();
                    while(iti!=favoritos.end())
                    {
                        if(ite->getTitulo()==iti->getTitulo())
                        {
                            x=0;
                        }
                        iti++;
                    }
                    if(x==1)
                    {
                        libro l;
                        l.setTitulo(ite->getTitulo());
                        l.setAutor(ite->getAutor());
                        l.setEditorial(ite->getEditorial());
                        l.setAnio(ite->getAnio());
                        l.setTipo(ite->getTipo());
                        favoritos.push_back(l);
                        if(y==1)
                        {
                            mislibros.push_back(l);
                        }
                    }
                }
                ite++;
            }
        }
        else if((*it)->checkState(1) == 2 && (*it)->checkState(2) == 0)
        {
            QVariant w;
            w = (*it)->data(0, 0);
            list<libro>::iterator ite=libros.begin();
            while(ite!=libros.end())
            {
                if(ite->getTitulo() == w.toString())
                {
                    list<libro>::iterator iti=mislibros.begin();
                    while(iti!=mislibros.end())
                    {
                        if(ite->getTitulo()==iti->getTitulo())
                        {
                            x=0;
                        }
                        iti++;
                    }
                    if(x==1)
                    {
                        libro l;
                        l.setTitulo(ite->getTitulo());
                        l.setAutor(ite->getAutor());
                        l.setEditorial(ite->getEditorial());
                        l.setAnio(ite->getAnio());
                        l.setTipo(ite->getTipo());
                        mislibros.push_back(l);
                    }
                }
                ite++;
            }
            list<libro>::iterator ito=favoritos.begin();
            while(ito!=favoritos.end())
            {
                if(ito->getTitulo() == w.toString())
                {
                    ito = favoritos.erase(ito);
                }
                else
                {
                    ito++;
                }
            }
        }
        else
        {
            QVariant p;
            p = (*it)->data(0, 0);
            list<libro>::iterator ito=mislibros.begin();
            while(ito!=mislibros.end())
            {
                if(ito->getTitulo() == p.toString())
                {
                    ito = mislibros.erase(ito);
                }
                else
                {
                    ito++;
                }
            }

            ito=favoritos.begin();
            while(ito!=favoritos.end())
            {
                if(ito->getTitulo() == p.toString())
                {
                    ito = favoritos.erase(ito);
                }
                else
                {
                    ito++;
                }
            }
        }
        ++it;
    }
    setmislibrostw();
    setfavoritostw();
}

void menuPrincipal::on_mislibrostreeWidget_clicked(const QModelIndex &index)
{
    QTreeWidgetItemIterator it(ui->mislibrostreeWidget);
    while (*it)
    {
        if ((*it)->checkState(1) == 0 &&(*it)->checkState(2) == 2)
        {
            (*it)->setCheckState(1,Qt::Checked);
        }
        ++it;
    }
}

void menuPrincipal::on_guardarfPB_clicked()
{
    QTreeWidgetItemIterator it(ui->favoritostreeWidget);
    while (*it)
    {
        if ((*it)->checkState(1) == 0)
        {
            QVariant p;
            p = (*it)->data(0, 0);
            list<libro>::iterator ito=favoritos.begin();
            while(ito!=favoritos.end())
            {
                if(ito->getTitulo() == p.toString())
                {
                    ito = favoritos.erase(ito);
                }
                else
                {
                    ito++;
                }
            }
        }
        ++it;
    }
    setmislibrostw();
    setfavoritostw();
    if (ui->libroLE->text().size() > 0 ||
            ui->autorLE->text().size() > 0 ||
            ui->editorialLE->text().size() > 0 ||
            ui->anioLE->text().size() > 0 ||
            ui->categoriaLE->text().size() > 0)
    {
        on_buscarPB_clicked();
    }
}

void menuPrincipal::on_ordenarlibroBPB_clicked()
{
    if(ordenlibro==2)
        ordenlibro=1;
    else
        ordenlibro=2;
    ordenautor=2;
    ordenanio=2;
    ordenpublish=2;
    ordentipo=2;

    int i=0,x,y,z;
    QString datos[500];
    QTreeWidgetItemIterator it(ui->librostreeWidget,QTreeWidgetItemIterator::HasChildren);
    while(*it)
    {
        z=0;
        QVariant w;
        w = (*it)->data(0, 0);
        for(x=0;x<i;x++)
            if(datos[x]==w.toString())
                z=1;
        if(z==0)
            datos[i]=w.toString();
        i++;
        it++;
    }
    ui->librostreeWidget->clear();
    for(x=0;x<i-1;x++)
    {
        for(y=0;y<i-1-x;y++)
        {
            if(ordenlibro==1)
            {
                if(datos[y].compare(datos[y+1],Qt::CaseInsensitive)>0)
                {

                    QString cambio=datos[y];
                    datos[y]=datos[y+1];
                    datos[y+1]=cambio;
                }
            }
            else if(ordenlibro==2)
            {
                if(datos[y+1].compare(datos[y],Qt::CaseInsensitive)>0)
                {

                    QString cambio=datos[y];
                    datos[y]=datos[y+1];
                    datos[y+1]=cambio;
                }
            }
        }
    }
    for(x=0;x<i;x++)
    {
        qDebug()<<datos[x];
        list<libro>::iterator iti=libros.begin();
        while(iti!=libros.end())
        {
            if(datos[x]==iti->getTitulo())
            {
                 addroot(iti->getTitulo(),iti->getAutor(),iti->getEditorial(),iti->getAnio(),iti->getTipo(),0);
            }
            iti++;
        }
    }
    ui->librostreeWidget->resizeColumnToContents(0);
}

void menuPrincipal::on_ordenarautorBPB_clicked()
{
    ordenardatos(1,1);
    ui->librostreeWidget->resizeColumnToContents(0);
}


void menuPrincipal::on_ordenaranioBPB_clicked()
{
    ordenardatos(1,2);
    ui->librostreeWidget->resizeColumnToContents(0);

}

void menuPrincipal::on_ordenarpublishBPB_clicked()
{
    ordenardatos(1,3);
    ui->librostreeWidget->resizeColumnToContents(0);

}

void menuPrincipal::on_ordenartipoBPB_clicked()
{
    ordenardatos(1,4);
    ui->librostreeWidget->resizeColumnToContents(0);


}

void menuPrincipal::on_ordenartituloMPB_clicked()
{
    if(ordenlibro==2)
        ordenlibro=1;
    else
        ordenlibro=2;
    ordenautor=2;
    ordenanio=2;
    ordenpublish=2;
    ordentipo=2;

    int i=0,x,y,z;
    QString datos[500];
    QTreeWidgetItemIterator it(ui->mislibrostreeWidget,QTreeWidgetItemIterator::HasChildren);
    while(*it)
    {
        z=0;
        QVariant w;
        w = (*it)->data(0, 0);
        for(x=0;x<i;x++)
            if(datos[x]==w.toString())
                z=1;
        if(z==0)
            datos[i]=w.toString();
        i++;
        it++;
    }
    ui->mislibrostreeWidget->clear();
    for(x=0;x<i-1;x++)
    {
        for(y=0;y<i-1-x;y++)
        {
            if(ordenlibro==1)
            {
                if(datos[y].compare(datos[y+1],Qt::CaseInsensitive)>0)
                {

                    QString cambio=datos[y];
                    datos[y]=datos[y+1];
                    datos[y+1]=cambio;
                }
            }
            else if(ordenlibro==2)
            {
                if(datos[y+1].compare(datos[y],Qt::CaseInsensitive)>0)
                {

                    QString cambio=datos[y];
                    datos[y]=datos[y+1];
                    datos[y+1]=cambio;
                }
            }
        }
    }
    for(x=0;x<i;x++)
    {
        list<libro>::iterator iti=mislibros.begin();
        while(iti!=mislibros.end())
        {
            if(datos[x]==iti->getTitulo())
            {
                 addroot(iti->getTitulo(),iti->getAutor(),iti->getEditorial(),iti->getAnio(),iti->getTipo(),1);
            }
            iti++;
        }
    }
    ui->mislibrostreeWidget->resizeColumnToContents(0);
}

void menuPrincipal::on_ordenarautorMPB_clicked()
{
    ordenardatos(2,1);
}

void menuPrincipal::on_ordenaranioMPB_clicked()
{
    ordenardatos(2,2);
    ui->mislibrostreeWidget->resizeColumnToContents(0);
}

void menuPrincipal::on_ordenarpublishMPB_clicked()
{
    ordenardatos(2,3);
    ui->mislibrostreeWidget->resizeColumnToContents(0);
}

void menuPrincipal::on_ordenartipoMPB_clicked()
{
    ordenardatos(2,4);
    ui->mislibrostreeWidget->resizeColumnToContents(0);

}

void menuPrincipal::on_ordenarlibroFPB_clicked()
{
    if(ordenlibro==2)
        ordenlibro=1;
    else
        ordenlibro=2;
    ordenautor=2;
    ordenanio=2;
    ordenpublish=2;
    ordentipo=2;

    int i=0,x,y,z;
    QString datos[500];
    QTreeWidgetItemIterator it(ui->favoritostreeWidget,QTreeWidgetItemIterator::HasChildren);
    while(*it)
    {
        z=0;
        QVariant w;
        w = (*it)->data(0, 0);
        for(x=0;x<i;x++)
            if(datos[x]==w.toString())
                z=1;
        if(z==0)
            datos[i]=w.toString();
        i++;
        it++;
    }
    ui->favoritostreeWidget->clear();
    for(x=0;x<i-1;x++)
    {
        for(y=0;y<i-1-x;y++)
        {
            if(ordenlibro==1)
            {
                if(datos[y].compare(datos[y+1],Qt::CaseInsensitive)>0)
                {

                    QString cambio=datos[y];
                    datos[y]=datos[y+1];
                    datos[y+1]=cambio;
                }
            }
            else if(ordenlibro==2)
            {
                if(datos[y+1].compare(datos[y],Qt::CaseInsensitive)>0)
                {

                    QString cambio=datos[y];
                    datos[y]=datos[y+1];
                    datos[y+1]=cambio;
                }
            }
        }
    }
    for(x=0;x<i;x++)
    {
        list<libro>::iterator iti=favoritos.begin();
        while(iti!=favoritos.end())
        {
            if(datos[x]==iti->getTitulo())
            {
                 addroot(iti->getTitulo(),iti->getAutor(),iti->getEditorial(),iti->getAnio(),iti->getTipo(),2);
            }
            iti++;
        }
    }
    ui->favoritostreeWidget->resizeColumnToContents(0);
}

void menuPrincipal::on_ordenarautorFPB_clicked()
{
    ordenardatos(3,1);
    ui->favoritostreeWidget->resizeColumnToContents(0);
}

void menuPrincipal::on_ordenaranioFPB_clicked()
{
    ordenardatos(3,2);
    ui->favoritostreeWidget->resizeColumnToContents(0);

}

void menuPrincipal::on_ordenarpublishFPB_clicked()
{
    ordenardatos(3,3);
    ui->favoritostreeWidget->resizeColumnToContents(0);

}

void menuPrincipal::on_ordenartipoFPB_clicked()
{
    ordenardatos(3,4);
    ui->favoritostreeWidget->resizeColumnToContents(0);

}

void menuPrincipal::on_antologiaPB_clicked()
{
    buscarcategoria("Antología");
    cate=1;
}

void menuPrincipal::on_biografiaPB_clicked()
{
    buscarcategoria("Biografía");
    cate=2;
}

void menuPrincipal::on_clasicoPB_clicked()
{
    buscarcategoria("Clásico");
    cate=3;
}

void menuPrincipal::on_dramaPB_clicked()
{
    buscarcategoria("Drama");
    cate=4;
}

void menuPrincipal::on_expositivoPB_clicked()
{
    buscarcategoria("Expositivo");
    cate=5;
}

void menuPrincipal::on_epistolarPB_clicked()
{
    buscarcategoria("Epistolar");
    cate=6;
}

void menuPrincipal::on_narrativaPB_clicked()
{
    buscarcategoria("Narrativa");
    cate=7;
}

void menuPrincipal::on_obragraficaPB_clicked()
{
    buscarcategoria("Obra gráfica");
    cate=8;
}

void menuPrincipal::on_poesiaPB_clicked()
{
    buscarcategoria("Poesía");
    cate=9;
}

void menuPrincipal::on_referenciaPB_clicked()
{
    buscarcategoria("Referencia");
    cate=10;
}

void menuPrincipal::on_categoriasguardarPB_clicked()
{

    int x,y;
    QTreeWidgetItemIterator it(ui->categoriastreeWidget);
    while (*it)
    {
        x=1;
        y=1;
        if((*it)->checkState(1) == 2 &&
                (*it)->checkState(2) == 2)
        {
            QVariant w;
            w = (*it)->data(0, 0);
            list<libro>::iterator ite=libros.begin();
            while(ite!=libros.end())
            {
                if(ite->getTitulo() == w.toString())
                {
                    list<libro>::iterator iti=mislibros.begin();
                    while(iti!=mislibros.end())
                    {
                        if(ite->getTitulo()==iti->getTitulo())
                        {
                            y=0;
                        }
                        iti++;
                    }
                    iti=favoritos.begin();
                    while(iti!=favoritos.end())
                    {
                        if(ite->getTitulo()==iti->getTitulo())
                        {
                            x=0;
                        }
                        iti++;
                    }
                    if(x==1)
                    {
                        libro l;
                        l.setTitulo(ite->getTitulo());
                        l.setAutor(ite->getAutor());
                        l.setEditorial(ite->getEditorial());
                        l.setAnio(ite->getAnio());
                        l.setTipo(ite->getTipo());
                        favoritos.push_back(l);
                        if(y==1)
                        {
                            mislibros.push_back(l);
                        }
                    }
                }
                ite++;
            }
        }
        else if((*it)->checkState(1) == 2 && (*it)->checkState(2) == 0)
        {
            QVariant w;
            w = (*it)->data(0, 0);
            list<libro>::iterator ite=libros.begin();
            while(ite!=libros.end())
            {
                if(ite->getTitulo() == w.toString())
                {
                    list<libro>::iterator iti=mislibros.begin();
                    while(iti!=mislibros.end())
                    {
                        if(ite->getTitulo()==iti->getTitulo())
                        {
                            x=0;
                        }
                        iti++;
                    }
                    if(x==1)
                    {
                        libro l;
                        l.setTitulo(ite->getTitulo());
                        l.setAutor(ite->getAutor());
                        l.setEditorial(ite->getEditorial());
                        l.setAnio(ite->getAnio());
                        l.setTipo(ite->getTipo());
                        mislibros.push_back(l);
                    }
                }
                ite++;
            }
            list<libro>::iterator ito=favoritos.begin();
            while(ito!=favoritos.end())
            {
                if(ito->getTitulo() == w.toString())
                {
                    ito = favoritos.erase(ito);
                }
                else
                {
                    ito++;
                }
            }
        }
        else
        {
            QVariant p;
            p = (*it)->data(0, 0);
            list<libro>::iterator ito=mislibros.begin();
            while(ito!=mislibros.end())
            {
                if(ito->getTitulo() == p.toString())
                {
                    ito = mislibros.erase(ito);
                }
                else
                {
                    ito++;
                }
            }

            ito=favoritos.begin();
            while(ito!=favoritos.end())
            {
                if(ito->getTitulo() == p.toString())
                {
                    ito = favoritos.erase(ito);
                }
                else
                {
                    ito++;
                }
            }
        }
        ++it;
    }
    setmislibrostw();
    setfavoritostw();
}

void menuPrincipal::on_categoriastreeWidget_clicked(const QModelIndex &index)
{
    QTreeWidgetItemIterator it(ui->categoriastreeWidget);
    while (*it)
    {
        if ((*it)->checkState(1) == 0 &&(*it)->checkState(2) == 2)
        {
            (*it)->setCheckState(1,Qt::Checked);
        }
        ++it;
    }
}

void menuPrincipal::on_ordenarlibroCPB_clicked()
{
    if(ordenlibro==2)
        ordenlibro=1;
    else
        ordenlibro=2;
    ordenautor=2;
    ordenanio=2;
    ordenpublish=2;
    ordentipo=2;

    int i=0,x,y,z;
    QString datos[500];
    QTreeWidgetItemIterator it(ui->categoriastreeWidget,QTreeWidgetItemIterator::HasChildren);
    while(*it)
    {
        z=0;
        QVariant w;
        w = (*it)->data(0, 0);
        for(x=0;x<i;x++)
            if(datos[x]==w.toString())
                z=1;
        if(z==0)
            datos[i]=w.toString();
        i++;
        it++;
    }
    ui->categoriastreeWidget->clear();
    for(x=0;x<i-1;x++)
    {
        for(y=0;y<i-1-x;y++)
        {
            if(ordenlibro==1)
            {
                if(datos[y].compare(datos[y+1],Qt::CaseInsensitive)>0)
                {

                    QString cambio=datos[y];
                    datos[y]=datos[y+1];
                    datos[y+1]=cambio;
                }
            }
            else if(ordenlibro==2)
            {
                if(datos[y+1].compare(datos[y],Qt::CaseInsensitive)>0)
                {

                    QString cambio=datos[y];
                    datos[y]=datos[y+1];
                    datos[y+1]=cambio;
                }
            }
        }
    }
    for(x=0;x<i;x++)
    {
        QString catego;
        if(cate==1)
            catego="Antología";
        else if(cate==2)
            catego="Biografía";
        else if(cate==3)
            catego="Clásico";
        else if(cate==4)
            catego="Drama";
        else if(cate==5)
            catego="Expositivo";
        else if(cate==6)
            catego="Epistolar";
        else if(cate==7)
            catego="Narrativa";
        else if(cate==8)
            catego="Obra gráfica";
        else if(cate==9)
            catego="Poesía";
        else if(cate==10)
            catego="Referencia";
        list<libro>::iterator iti=libros.begin();
        while(iti!=libros.end())
        {
            if(datos[x]==iti->getTitulo()&&iti->getTipo()==catego)
            {
                 addroot(iti->getTitulo(),iti->getAutor(),iti->getEditorial(),iti->getAnio(),iti->getTipo(),3);
            }
            iti++;
        }
    }
    ui->categoriastreeWidget->resizeColumnToContents(0);
}

void menuPrincipal::on_ordenarautorCPB_clicked()
{
    ordenardatos(4,1);
    ui->categoriastreeWidget->resizeColumnToContents(0);
}

void menuPrincipal::on_ordenaranioCPB_clicked()
{
    ordenardatos(4,2);
    ui->categoriastreeWidget->resizeColumnToContents(0);
}

void menuPrincipal::on_ordenarpublishCPB_clicked()
{
    ordenardatos(4,3);
    ui->categoriastreeWidget->resizeColumnToContents(0);
}

void menuPrincipal::on_recomendadostreeWidget_clicked(const QModelIndex &index)
{
    QTreeWidgetItemIterator it(ui->recomendadostreeWidget);
    while (*it)
    {
        if ((*it)->checkState(1) == 0 &&(*it)->checkState(2) == 2)
        {
            (*it)->setCheckState(1,Qt::Checked);
        }
        ++it;
    }
}

void menuPrincipal::on_recomendarRPB_clicked()
{
    tam=0;
    cargarrecomendados();
    ui->recomendadostreeWidget->clear();
    int x,l=0;
    bool yaestoy;
    for(x=0;x<tam-1;x++)
    {
        yaestoy=false;
        list<libro>::iterator it=mislibros.begin();
        while(it!=mislibros.end())
        {
            if(recomendados[x].contains(it->getTitulo()))
            {
                yaestoy=true;
            }
            it++;
        }
        if(yaestoy==false)
        {
            it=libros.begin();
            while(it!=libros.end())
            {
                if(recomendados[x].contains(it->getTitulo())&&l<3)
                {
                    addroot(it->getTitulo(),it->getAutor(),it->getEditorial(),it->getAnio(),it->getTipo(),4);
                    l++;
                }
//                if(l==3)
//                {
//                    it=libros.end();
//                    x=tam;
//                }
                it++;
            }
        }


    }
    ui->recomendadostreeWidget->resizeColumnToContents(0);
}

void menuPrincipal::on_guardarRPB_clicked()
{
    int x,y;
    QTreeWidgetItemIterator it(ui->recomendadostreeWidget);
    while (*it)
    {
        x=1;
        y=1;
        if((*it)->checkState(1) == 2 &&
                (*it)->checkState(2) == 2)
        {
            QVariant w;
            w = (*it)->data(0, 0);
            list<libro>::iterator ite=libros.begin();
            while(ite!=libros.end())
            {
                if(ite->getTitulo() == w.toString())
                {
                    list<libro>::iterator iti=mislibros.begin();
                    while(iti!=mislibros.end())
                    {
                        if(ite->getTitulo()==iti->getTitulo())
                        {
                            y=0;
                        }
                        iti++;
                    }
                    iti=favoritos.begin();
                    while(iti!=favoritos.end())
                    {
                        if(ite->getTitulo()==iti->getTitulo())
                        {
                            x=0;
                        }
                        iti++;
                    }
                    if(x==1)
                    {
                        libro l;
                        l.setTitulo(ite->getTitulo());
                        l.setAutor(ite->getAutor());
                        l.setEditorial(ite->getEditorial());
                        l.setAnio(ite->getAnio());
                        l.setTipo(ite->getTipo());
                        favoritos.push_back(l);
                        if(y==1)
                        {
                            mislibros.push_back(l);
                        }
                    }
                }
                ite++;
            }
        }
        else if((*it)->checkState(1) == 2 && (*it)->checkState(2) == 0)
        {
            QVariant w;
            w = (*it)->data(0, 0);
            list<libro>::iterator ite=libros.begin();
            while(ite!=libros.end())
            {
                if(ite->getTitulo() == w.toString())
                {
                    list<libro>::iterator iti=mislibros.begin();
                    while(iti!=mislibros.end())
                    {
                        if(ite->getTitulo()==iti->getTitulo())
                        {
                            x=0;
                        }
                        iti++;
                    }
                    if(x==1)
                    {
                        libro l;
                        l.setTitulo(ite->getTitulo());
                        l.setAutor(ite->getAutor());
                        l.setEditorial(ite->getEditorial());
                        l.setAnio(ite->getAnio());
                        l.setTipo(ite->getTipo());
                        mislibros.push_back(l);
                    }
                }
                ite++;
            }
            list<libro>::iterator ito=favoritos.begin();
            while(ito!=favoritos.end())
            {
                if(ito->getTitulo() == w.toString())
                {
                    ito = favoritos.erase(ito);
                }
                else
                {
                    ito++;
                }
            }
        }
        else
        {
            QVariant p;
            p = (*it)->data(0, 0);
            list<libro>::iterator ito=mislibros.begin();
            while(ito!=mislibros.end())
            {
                if(ito->getTitulo() == p.toString())
                {
                    ito = mislibros.erase(ito);
                }
                else
                {
                    ito++;
                }
            }

            ito=favoritos.begin();
            while(ito!=favoritos.end())
            {
                if(ito->getTitulo() == p.toString())
                {
                    ito = favoritos.erase(ito);
                }
                else
                {
                    ito++;
                }
            }
        }
        ++it;
    }
    setmislibrostw();
    setfavoritostw();
}
