#ifndef LIBRO_H
#define LIBRO_H
#include <QString>

using namespace std;


class libro
{
public:
    libro();

    QString getTitulo() const;
    void setTitulo(const QString &value);

    QString getAutor() const;
    void setAutor(const QString &value);

    QString getEditorial() const;
    void setEditorial(const QString &value);

    QString getAnio() const;
    void setAnio(const QString &value);

    QString getTipo() const;
    void setTipo(const QString &value);

private:
    QString titulo;
    QString autor;
    QString editorial;
    QString anio;
    QString tipo;
};

#endif // LIBRO_H
