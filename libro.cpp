#include "libro.h"

libro::libro()
{

}

QString libro::getTitulo() const
{
    return titulo;
}

void libro::setTitulo(const QString &value)
{
    titulo = value;
}

QString libro::getAutor() const
{
    return autor;
}

void libro::setAutor(const QString &value)
{
    autor = value;
}

QString libro::getEditorial() const
{
    return editorial;
}

void libro::setEditorial(const QString &value)
{
    editorial = value;
}

QString libro::getAnio() const
{
    return anio;
}

void libro::setAnio(const QString &value)
{
    anio = value;
}

QString libro::getTipo() const
{
    return tipo;
}

void libro::setTipo(const QString &value)
{
    tipo = value;
}

