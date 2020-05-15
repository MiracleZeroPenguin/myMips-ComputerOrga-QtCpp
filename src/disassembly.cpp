#include "disassembly.h"

Disassembly::Disassembly(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant Disassembly::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex Disassembly::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex Disassembly::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int Disassembly::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int Disassembly::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant Disassembly::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
