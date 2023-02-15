#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <qmessagebox.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);
    
    this->partList = new ModelPartList("PartList");

    ui->treeView->setModel(this->partList);

    ModelPart* rootItem = this->partList->getRootItem();

    // Do variables outside of loop. Make life easier on the compiler for optimisation :)
    QString name, visible("true");
    for (size_t i = 0; i < 3; i++) {
        name = QString("TopLevel %1").arg(i);

        // This is more clean to read and makes work easier for compiler optimisation pass AFAIK.
        rootItem->appendChild(new ModelPart({ name,visible }));
    
        for (size_t j = 0; j < 5; j++) {
            name = QString("Item %1,%2").arg(i).arg(j);

            //rootItem[i].appendChild(new ModelPart({ name, visible }));
            rootItem->child(i)->appendChild(new ModelPart({ name, visible }));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleButton() {
    //QMessageBox msgBox;
    //msgBox.setText("Button was clicked.");
    //msgBox.exec();

    emit statusUpdateMessage(QString("Add button was clicked"), 0);

}