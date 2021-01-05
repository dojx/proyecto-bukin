#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QMainWindow>
#include "libro.h"
#include <list>
#include "usuario.h"
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>

using namespace std;

namespace Ui {
class menuPrincipal;
}

class menuPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit menuPrincipal(QWidget *parent = 0);
    ~menuPrincipal();
    void setcurrentuser(QString n,QString u, QString co, QString f, QString c);
    void hideprincipal();
    void addroot(QString title,QString author, QString publish, QString year, QString genre,int tree);
    void addchild(QTreeWidgetItem *parent,QString info);
    void setmislibrostw();
    void cargarmislibros();
    void setfavoritostw();
    void cargarfavoritos();
    void setmislibrostxt();
    void setfavoritostxt();
    void buscarcategoria(QString categ);
    void ordenardatos(int l, int m);
    void generagrafo();
    void cargarrecomendados();
    void ordenarrecomendados();

signals:


private slots:
    void on_libroLE_textChanged(const QString &arg1);

    void on_autorLE_textChanged(const QString &arg1);

    void on_anioLE_textChanged(const QString &arg1);

    void on_editorialLE_textChanged(const QString &arg1);

    void on_categoriaLE_textChanged(const QString &arg1);

    void on_buscarPB_clicked();

    void on_editarperfilPB_clicked();

    void on_librostreeWidget_clicked(const QModelIndex &index);

    void on_guardarmlPB_clicked();

    void on_guardarbPB_clicked();

    void on_mislibrostreeWidget_clicked(const QModelIndex &index);

    void on_guardarfPB_clicked();

    void on_ordenarlibroBPB_clicked();

    void on_ordenarautorBPB_clicked();

    void on_ordenaranioBPB_clicked();

    void on_ordenarpublishBPB_clicked();

    void on_ordenartipoBPB_clicked();
    
    void on_ordenartituloMPB_clicked();

    void on_ordenarautorMPB_clicked();

    void on_ordenaranioMPB_clicked();

    void on_ordenarpublishMPB_clicked();

    void on_ordenartipoMPB_clicked();

    void on_ordenarlibroFPB_clicked();

    void on_ordenarautorFPB_clicked();

    void on_ordenaranioFPB_clicked();

    void on_ordenarpublishFPB_clicked();

    void on_ordenartipoFPB_clicked();

    void on_antologiaPB_clicked();

    void on_biografiaPB_clicked();

    void on_clasicoPB_clicked();

    void on_dramaPB_clicked();

    void on_expositivoPB_clicked();

    void on_epistolarPB_clicked();

    void on_narrativaPB_clicked();

    void on_obragraficaPB_clicked();

    void on_poesiaPB_clicked();

    void on_referenciaPB_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_categoriasguardarPB_clicked();

    void on_categoriastreeWidget_clicked(const QModelIndex &index);

    void on_ordenarlibroCPB_clicked();

    void on_ordenarautorCPB_clicked();

    void on_ordenaranioCPB_clicked();

    void on_ordenarpublishCPB_clicked();

    void on_ordenartipoCPB_clicked();

    void on_recomendadostreeWidget_clicked(const QModelIndex &index);

    void on_recomendarRPB_clicked();

    void on_guardarRPB_clicked();

private:
    Ui::menuPrincipal *ui;
    list<libro> libros;
    list<libro> mislibros;
    list<libro> favoritos;
    Usuario cuser;
    QHash<QString, QHash<QString, int> > grafo;
    QString recomendados[10000];
    int valores[10000];
    int tam=0;

    int ordenlibro=2;
    int ordenautor=2;
    int ordenanio=2;
    int ordenpublish=2;
    int ordentipo=2;
    int cate=0;
};

#endif // MENUPRINCIPAL_H
