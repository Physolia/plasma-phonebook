/*
 *   SPDX-FileCopyrightText: 2021 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include <QImage>
#include <QObject>

#include <KContacts/Addressee>
#include <KContacts/Email>
#include <KContacts/Impp>
#include <KContacts/PhoneNumber>
#include <KContacts/Picture>

#include <memory>

class QFileDialog;

class ContactController : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE KContacts::Addressee addresseeFromVCard(const QByteArray &vcard);
    Q_INVOKABLE QByteArray addresseeToVCard(const KContacts::Addressee &addressee);
    Q_INVOKABLE KContacts::Addressee emptyAddressee();
    Q_INVOKABLE KContacts::Picture preparePhoto(const QUrl &url);
    Q_INVOKABLE KContacts::Email createEmail(const QString &email);
    Q_INVOKABLE KContacts::PhoneNumber createPhoneNumber(const QString &number);
    Q_INVOKABLE KContacts::Impp createImpp(const QString &address);
};