#pragma once

#ifndef MY_WINDOW_HPP
#define MY_WINDOW_HPP


#include <QMainWindow>
#include <QListWidget>
#include <QAbstractTableModel>
#include <QString>


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

    //std::vector<std::string> get_object_names();


private slots:

    /** Quit the application */
    void action_quit();
    /** Enable the drawing of the meshes */
    void action_draw();
    /** Set the Wireframe mode for the meshes */
    void action_wireframe();
    /** Fill the list model with object names */
    void set_model_list();
    /** hide or not some objects of the gl view */
    void action_hide_button_pressed(const int &index, const bool &state);
    /** Action reset the drawing to its original drawn position/orientation */
    void action_reset();
    /** Enable/Disbale debug bullet drawing */
    void action_debug_bullet();


private:

    /** Layout for the Window */
    Ui::MainWindow *ui;
    /** The OpenGL Widget */
    myWidgetGL *glWidget;
    /** The list widget */
    //myTreeModel *myModel;
    //QAbstractTableModel *myModel;
    myListModel *myModel;
    /** The tree widget */
    QStandardItemModel *standardModel;
    QItemSelectionModel *selectionModel;

//private slots:
//    void selectionChangedSlot(const QItemSelection & newSelection, const QItemSelection & oldSelection);

public slots :
    void showWindowTitle(const QString& title);

};

#endif
