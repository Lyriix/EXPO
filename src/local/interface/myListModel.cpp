//mymodel.cpp

#include "myListModel.hpp"
#include <QDebug>
#include <QBrush>
#include <QFont>
#include <QTime>

myListModel::myListModel(QObject *parent)
    :QAbstractTableModel(parent)
{
}

myListModel::~myListModel()
{}

int myListModel::rowCount(const QModelIndex & /*parent*/) const
{
    return ROWS;
}

int myListModel::columnCount(const QModelIndex & /*parent*/) const
{
    return COLS;
}

QVariant myListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();


    if( role == Qt::DisplayRole )
    {
        return QString("Row%1,Column%2").arg(row).arg(col);
    }

    return QVariant();
}


bool myListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        //save value from editor to member m_gridData
        m_gridData[index.row()][index.column()] = value.toString();
        //for presentation purposes only : build and emit a joined string
        QString result;
        for(int row=0; row < ROWS; row++)
        {
            for(int col=0; col<COLS; col++)
            {
                result+= m_gridData[row][col] + ' ';
            }
        }
        emit editCompleted(result);
    }
    return true;
}

Qt::ItemFlags myListModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}