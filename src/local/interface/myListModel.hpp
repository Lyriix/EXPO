//We start with an application that uses a QTableViez to show data
// Tutorial http://doc.qt.io/qt-5/modelview.html

//mymodel.h
#pragma once
#ifndef MY_LIST_MODEL_HPP
#define MY_LIST_MODEL_HPP


#include <QAbstractTableModel>
#include <QString>

const int COLS = 1;
const int ROWS = 2;
class myListModel : public QAbstractTableModel //reauires the implementation of three abstract methods
{
    Q_OBJECT
public:
    myListModel(QObject *parent = 0);
    ~myListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //editing (acts like a wrapper and adapts m_gridData to to QAbstractItemModel
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void fill_objects_names(std::vector<std::string> const& names);



private:
    QString m_gridData[ROWS][COLS]; //holds text entered into QTable View // array Use to store our data
    std::vector<QString> objects_name;

signals:
    void editCompleted(const QString &); //transfer the modified text to the window title
};


#endif
