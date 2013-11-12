#include "root.h"

#include <cutelystcontext.h>
#include <cutelystresponse.h>

#include <QDebug>

Root::Root()
{
    qDebug() << Q_FUNC_INFO;
}

void Root::hugeNameQuiteLong(const QString &nome, Local)
{

}

void Root::begin(const QString &name)
{
    qDebug() << Q_FUNC_INFO << name;
}

void Root::users(const QString &name, const QString &age, Args, CutelystController::Local)
{
    qDebug() << Q_FUNC_INFO << name << age;
}

void Root::admin(const QString &name, const QString &age, CutelystController::Global)
{
    qDebug() << Q_FUNC_INFO << name << age;
    QByteArray data;
    data = "<!DOCTYPE html>"
            "<html lang=\"en\">"
            "    <head>"
            "        <meta charset=\"utf-8\">"
            "        <title>Hello World</title>"
            "    </head>"
            "    <body>"
            "        <h1>Hello World</h1>"
            "        <p>"
            "            Jamie estava aqui."
            "        </p>"
            "    </body>"
            "</html>";
    c()->response()->setBody(data);
}

void Root::dispatchBegin()
{
    qDebug() << Q_FUNC_INFO;
}
