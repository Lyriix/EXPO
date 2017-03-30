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



        /** Tree Widget */
        standardModel = new QStandardItemModel ;
        QStandardItem *rootNode = standardModel->invisibleRootItem();
        //defining a couple of items
        QStandardItem *americaItem = new QStandardItem("America");
        QStandardItem *mexicoItem =  new QStandardItem("Canada");
        QStandardItem *usaItem =     new QStandardItem("USA");
        QStandardItem *bostonItem =  new QStandardItem("Boston");
        QStandardItem *europeItem =  new QStandardItem("Europe");
        QStandardItem *italyItem =   new QStandardItem("Italy");
        QStandardItem *romeItem =    new QStandardItem("Rome");
        QStandardItem *veronaItem =  new QStandardItem("Verona");

        //building up the hierarchy
        rootNode->    appendRow(americaItem);
        rootNode->    appendRow(europeItem);
        americaItem-> appendRow(mexicoItem);
        americaItem-> appendRow(usaItem);
        usaItem->     appendRow(bostonItem);
        europeItem->  appendRow(italyItem);
        italyItem->   appendRow(romeItem);
        italyItem->   appendRow(veronaItem);

        //register the model
        ui->treeView->setModel(standardModel);
        ui->treeView->expandAll();
        selectionModel = ui->treeView->selectionModel();



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



void myWindow::selectionChangedSlot(const QItemSelection &, const QItemSelection &)
{
    //get the text of the selected item
    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QString selectedText = index.data(Qt::DisplayRole).toString();
    //find out the hierarchy level of the selected item
    int hierarchyLevel=1;
    QModelIndex seekRoot = index;
    while(seekRoot.parent() != QModelIndex())
    {
        seekRoot = seekRoot.parent();
        hierarchyLevel++;
    }
    QString showString = QString("%1, Level %2").arg(selectedText)
                         .arg(hierarchyLevel);
    setWindowTitle(showString);
}

void myWindow::set_model_list()
{
//    myModel->rowCount(glWidget->get_scene().get_meshes().size());
    myModel->fill_objects_names(glWidget->get_scene().get_meshes_names());
    ui->tableView->setModel( myModel );

}
