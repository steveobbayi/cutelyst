/*
 * Copyright (C) 2013-2015 Daniel Nicoletti <dantti12@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <Cutelyst/plugin.h>

#include <Cutelyst/Plugins/authenticationuser.h>

namespace Cutelyst {

class AuthenticationStore;
class AuthenticationRealm;
class AuthenticationCredential : public QObject
{
    Q_OBJECT
public:
    explicit AuthenticationCredential(QObject *parent = 0);
    virtual ~AuthenticationCredential();

    virtual AuthenticationUser authenticate(Context *ctx, AuthenticationRealm *realm, const CStringHash &authinfo) = 0;
};

class AuthenticationPrivate;
class Authentication : public Plugin
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Authentication)
public:
    static char *defaultRealm;

    Authentication(Application *parent);
    virtual ~Authentication();

    void addRealm(AuthenticationRealm *realm, const QString &name = QLatin1String(defaultRealm));

    AuthenticationRealm *realm(const QString &name = QLatin1String(defaultRealm)) const;

    AuthenticationUser authenticate(Context *c, const CStringHash &userinfo = CStringHash(), const QString &realm = QLatin1String(defaultRealm));
    AuthenticationUser findUser(Context *c, const CStringHash &userinfo, const QString &realm = QLatin1String(defaultRealm));
    AuthenticationUser user(Context *c);
    void setUser(Context *c, const AuthenticationUser &user);
    bool userExists(Context *c);
    bool userInRealm(Context *c, const QString &realm = QLatin1String(defaultRealm));
    void logout(Context *c);

protected:
    void setAuthenticated(Context *c, const AuthenticationUser &user, const QString &realmName);
    void persistUser(Context *c, const AuthenticationUser &user, const QString &realmName);
    AuthenticationUser restoreUser(Context *c, const QVariant &frozenUser, const QString &realmName);
    AuthenticationRealm* findRealmForPersistedUser(Context *c);

    AuthenticationPrivate *d_ptr;
};

}

#endif // AUTHENTICATION_H
