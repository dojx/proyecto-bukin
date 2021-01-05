#include "usuario.h"

Usuario::Usuario()
{

}

QString Usuario::getNombre() const
{
    return nombre;
}

void Usuario::setNombre(const QString &value)
{
    nombre = value;
}

QString Usuario::getUser() const
{
    return user;
}

void Usuario::setUser(const QString &value)
{
    user = value;
}

QString Usuario::getContrasena() const
{
    return contrasena;
}

void Usuario::setContrasena(const QString &value)
{
    contrasena = value;
}

QString Usuario::getFecha() const
{
    return fecha;
}

void Usuario::setFecha(const QString &value)
{
    fecha = value;
}

QString Usuario::getCorreo() const
{
    return correo;
}

void Usuario::setCorreo(const QString &value)
{
    correo = value;
}
