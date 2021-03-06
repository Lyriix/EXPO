//mymodel.cpp

#include "myListModel.hpp"
#include <QDebug>
#include <QBrush>
#include <QFont>
#include <QTime>
#include <iostream>

myListModel::myListModel(QObject *parent)
    :QAbstractTableModel(parent)
{
}

myListModel::~myListModel()
{}

int myListModel::rowCount(const QModelIndex & /*parent*/) const
{
    return 15;//objects_name.size();
}

int myListModel::columnCount(const QModelIndex & /*parent*/) const
{
    return COLS;
}

QVariant myListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if( orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString("Object");
            case 1:
                return QString("Hide");
            }
        }
    }
    return QVariant();
}

QVariant myListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();


    if( role == Qt::DisplayRole )
    {
        if(  col == 0)
        {
            return objects_name.at(row);
        }
    }
    if(role == Qt::CheckStateRole )
    {
        if (col == 1 )
        {
                return hide_button.at(row);
        }
    }

    return QVariant();
}


bool myListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
   /* if (role == Qt::EditRole)
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
    }*/

    if( role == Qt::CheckStateRole)
    {
//            std::cout << index.row() << std::endl;
            hide_button.at(index.row()) = value;
            emit hide_button_pressed(index.row(), value.toBool());

    }

//    emit dataChanged(index,index);
    return true;
}

Qt::ItemFlags myListModel::flags(const QModelIndex &index) const
{

    if(index.isValid() && index.column() == 1 )
        return QAbstractTableModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEditable;
    return Qt::ItemIsEnabled;

}

void myListModel::fill_objects_names(std::vector<std::string> const& names)
{
    for(auto & obj_name : names)
    {
        QString qstr = QString::fromStdString(obj_name);
        objects_name.push_back(qstr);
        hide_button.push_back(0);
    }
}
