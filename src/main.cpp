/*
 * Copyright 2019  Linus Jahn <lnj@kaidan.im>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QtQml>

#include <KLocalizedContext>

#include "contactimporter.h"
#include "declarativeaddressee.h"
#include "imppmodel.h"
#include "phonesmodel.h"

#ifdef Q_OS_ANDROID
#include <QtAndroid>
#endif

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName(QStringLiteral("KDE"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("kde.org"));
    QCoreApplication::setApplicationName(QStringLiteral("plasma-phonebook"));

    // back-end
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));

    qmlRegisterType<Addressee>("org.kde.kcontacts", 1, 0, "Addressee");
    qmlRegisterUncreatableType<PhonesModel>("org.kde.kcontacts", 1, 0, "PhonesModel", QStringLiteral("Get it from the Addressee"));
    qmlRegisterUncreatableType<ImppModel>("org.kde.kcontacts", 1, 0, "ImppModel", QStringLiteral("Get it from the Addressee"));
    qmlRegisterType<ContactImporter>("org.kde.phonebook", 1, 0, "ContactImporter");
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    qmlRegisterAnonymousType<QAbstractItemModel>("org.kde.phonebook", 1);
#else
    qmlRegisterType<QAbstractItemModel>();
#endif

#ifdef Q_OS_ANDROID
    QtAndroid::requestPermissionsSync({"android.permission.WRITE_EXTERNAL_STORAGE"});
#endif

    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
