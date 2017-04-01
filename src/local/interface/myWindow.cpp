#include "myWindow.hpp"

#include "myWidgetGL.hpp"

#include <QTableView>
#include "myListModel.hpp"

#include <QStandardItemModel>
#include <QItemSelectionModel>

#include "../../lib/common/error_handling.hpp"
#include "ui_mainwindow.h"

#include <QDebug>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include <QLabel>

myWindow::myWindow(QWidget *parent)
    :QMainWindow(parent),ui(new Ui::MainWindow)
{
    try
    {
        //Setup window layout
        ui->setupUi(this);

        /** Open Gl context */
        //Create openGL context
        QGLFormat qglFormat;
        qglFormat.setVersion(1,2);

        //Create OpenGL Widget renderer
        glWidget=new myWidgetGL(qglFormat);

        //Add the OpenGL Widget into the layout
        ui->layout_scene->addWidget(glWidget);

        /** List Widget */
        //add the List into the layout made for
        myModel = new myListModel();


        QPixmap image("data/eye_anatomy.jpg");

        ui->imageView->setPixmap(image);
//ui->imageView->set






    }
    catch(cpe::exception_cpe const& e)
    {
        std::cout<<std::endl<<e.report_exception()<<std::endl;
    }

    //Connect slot and signals
    connect(ui->quit,SIGNAL(clicked()),this,SLOT(action_quit()));
    connect(ui->draw,SIGNAL(clicked()),this,SLOT(action_draw()));
    connect(ui->wireframe,SIGNAL(clicked()),this,SLOT(action_wireframe()));
    connect(myModel, SIGNAL(editCompleted(const QString &)), this, SLOT(setWindowTitle(const QString &)));
   /* connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &))); */
    connect(glWidget, SIGNAL(gl_loaded()), this, SLOT(set_model_list()));
    connect(myModel, SIGNAL(hide_button_pressed(const int &, const bool & )), this, SLOT(action_hide_button_pressed(const int , const bool & )));
    connect(ui->ResetButton,SIGNAL(clicked()),this,SLOT(action_reset()));
//    connect(myModel, SIGNAL(myListModel::hide_button_pressed(const int &, const bool &)), this, SLOT(aboutQt(const int &, const bool &)));
    connect(ui->debugBullet,SIGNAL(clicked()), this, SLOT(action_debug_bullet()));


}

myWindow::~myWindow()
{}



void myWindow::action_quit()
{
    close();
}

void myWindow::action_draw()
{
    glWidget->change_draw_state();
    //qDebug() << glWidget->isEnabled();
}

void myWindow::action_wireframe()
{
    bool const state_wireframe=ui->wireframe->isChecked();
    glWidget->wireframe(state_wireframe);
}

void myWindow::showWindowTitle(const QString & title)
{
    setWindowTitle("titl");
}

void myWindow::action_reset()
{
    glWidget->reset();
}

//void myWindow::selectionChangedSlot(const QItemSelection &, const QItemSelection &)
//{
//    //get the text of the selected item
//    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
//    QString selectedText = index.data(Qt::DisplayRole).toString();
//    //find out the hierarchy level of the selected item
//    int hierarchyLevel=1;
//    QModelIndex seekRoot = index;
//    while(seekRoot.parent() != QModelIndex())
//    {
//        seekRoot = seekRoot.parent();
//        hierarchyLevel++;
//    }
//    QString showString = QString("%1, Level %2").arg(selectedText)
//                         .arg(hierarchyLevel);
//    setWindowTitle(showString);
//}

void myWindow::set_model_list()
{
//    myModel->rowCount(glWidget->get_scene().get_meshes().size());
    myModel->fill_objects_names(glWidget->get_scene().get_meshes_names());
    ui->tableView->setModel( myModel );

}

void myWindow::action_hide_button_pressed(const int & index, const bool &state )
{
    qDebug() << index  ;
    qDebug() << state  ;
//    const QModelIndex index = myModel->hide_button.
    glWidget->change_draw_state_object(index,state);
}

void myWindow::action_debug_bullet()
{
    bool const state_debug_bullet = ui->debugBullet->isChecked();
    glWidget->set_bullet_debug(state_debug_bullet);
}
