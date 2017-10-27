/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef LIBNITROSHARE_TRANSFERMODEL_H
#define LIBNITROSHARE_TRANSFERMODEL_H

#include <QAbstractListModel>

#include <nitroshare/config.h>

class Application;
class TransportServer;

class NITROSHARE_EXPORT TransferModelPrivate;

/**
 * @brief Model representing transfers in progress and completed
 */
class NITROSHARE_EXPORT TransferModel : public QAbstractListModel
{
    Q_OBJECT

public:

    /**
     * @brief Create a transfer model
     * @param application pointer to Application
     * @param parent QObject
     */
    TransferModel(Application *application, QObject *parent = nullptr);

    /**
     * @brief Add a transport server
     * @param server pointer to TransportServer
     */
    void addTransportServer(TransportServer *server);

    /**
     * @brief Remove a transport server
     * @param server pointer to TransportServer
     */
    void removeTransportServer(TransportServer *server);

    // Reimplemented virtual methods
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

private:

    TransferModelPrivate *const d;
    friend class TransferModelPrivate;
};

#endif // LIBNITROSHARE_TRANSFERMODEL_H
