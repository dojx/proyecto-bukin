#ifndef USUARIO_H
#define USUARIO_H
#include <QString>
#include <list>

class Usuario
{
public:
    Usuario();

    QString getNombre() const;
    void setNombre(const QString &value);

    QString getUser() const;
    void setUser(const QString &value);

    QString getContrasena() const;
    void setContrasena(const QString &value);

    QString getFecha() const;
    void setFecha(const QString &value);

    QString getCorreo() const;
    void setCorreo(const QString &value);

private:
    QString nombre;
    QString fecha;
    QString user;
    QString contrasena;
    QString correo;

};

#endif // USUARIO_H
