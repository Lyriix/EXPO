#pragma once

#ifndef MY_WINDOW_HPP
#define MY_WINDOW_HPP


#include <QMainWindow>
#include <QListWidget>
#include <QAbstractTableModel>



//forward declaration
namespace Ui
{
class MainWindow;
}
class myWidgetGL;
class myListModel;

class QStandardItemModel;
class QItemSelection;

/** Declaration of the Window class */
class myWindow: public QMainWindow
{
    Q_OBJECT

public:

    myWindow(QWidget *parent=NULL);
    ~myWindow();



private slots:

    /** Quit the application */
    void action_quit();
    /** Enable the drawing of the meshes */
    void action_draw();
    /** Set the Wireframe mode for the meshes */
    void action_wireframe();


private:

    /** Layout for the Window */
    Ui::MainWindow *ui;
    /** The OpenGL Widget */
    myWidgetGL *glWidget;
    /** The list widget */
    //myTreeModel *myModel;
    QAbstractTableModel *myModel;
    /** The tree widget */
    QStandardItemModel *standardModel;
    QItemSelectionModel *selectionModel;

private slots:
    void selectionChangedSlot(const QItemSelection & newSelection, const QItemSelection & oldSelection);

public slots :
    void showWindowTitle(const QString& title);

};

#endif
