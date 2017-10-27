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

#include <nitroshare/application.h>
#include <nitroshare/transfer.h>
#include <nitroshare/transfermodel.h>
#include <nitroshare/transport.h>
#include <nitroshare/transportserver.h>

#include "transfermodel_p.h"

TransferModelPrivate::TransferModelPrivate(TransferModel *model, Application *application)
    : QObject(model),
      q(model),
      application(application)
{
}

TransferModelPrivate::~TransferModelPrivate()
{
    // TODO: stop transfers gracefully (?)

    qDeleteAll(transfers);
}

void TransferModelPrivate::addTransfer(Transfer *transfer)
{
    // TODO: monitor transfer for changes & update models

    q->beginInsertRows(QModelIndex(), transfers.count(), transfers.count());
    transfers.append(transfer);
    q->endInsertRows();
}

void TransferModelPrivate::processTransport(Transport *transport)
{
    // Create a new transfer from the transport
    addTransfer(new Transfer(application, transport));
}

TransferModel::TransferModel(Application *application, QObject *parent)
    : QAbstractListModel(parent),
      d(new TransferModelPrivate(this, application))
{
}

void TransferModel::addTransportServer(TransportServer *server)
{
    connect(server, &TransportServer::transportReceived, d, &TransferModelPrivate::processTransport);
}

void TransferModel::removeTransportServer(TransportServer *server)
{
    disconnect(server, &TransportServer::transportReceived, d, &TransferModelPrivate::processTransport);
}

int TransferModel::rowCount(const QModelIndex &) const
{
    return d->transfers.count();
}

QVariant TransferModel::data(const QModelIndex &index, int role) const
{
    // Ensure the index points to a valid row
    if (!index.isValid() || index.row() < 0 ||
            index.row() >= d->transfers.count() || role != Qt::UserRole) {
        return QVariant();
    }
    return QVariant::fromValue(d->transfers.at(index.row()));
}
