#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <qmessagebox.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);

    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);
    
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleSecondButton);

    ui->treeView->addAction(ui->actionItem_Options);

    this->partList = new ModelPartList("PartList");

    ui->treeView->setModel(this->partList);

    ModelPart* rootItem = this->partList->getRootItem();

    // Made some changes to the below code from the example due to bad practices such as redefining variables multiple times, more explicit for compiler optimisation & to compact the code a bit.

    // Do variables outside of loop. Make life easier on the compiler for optimisation :)
    QString name, visible("true");
    for (size_t i = 0; i < 3; i++) {
        name = QString("TopLevel %1").arg(i);

        // This is more clean to read and makes work easier for compiler optimisation pass AFAIK.
        rootItem->appendChild(new ModelPart({ name,visible }));
    
        for (size_t j = 0; j < 5; j++) {
            name = QString("Item %1,%2").arg(i).arg(j);
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

void MainWindow::handleTreeClicked() {
    QModelIndex index = ui->treeView->currentIndex();

    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    QString text = selectedPart->data(0).toString();

    emit statusUpdateMessage(QString("The selected item is: " + text),0);
}

void MainWindow::on_actionOpenFile_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C:\\", tr("STL Files(*.stl);;Text Files(*.txt)"));
    emit statusUpdateMessage(QString("Open File action triggered, Opening: ") + fileName, 0);

    QModelIndex index = ui->treeView->currentIndex();

    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    QList splitName = fileName.split("/");

    selectedPart->setName(splitName.at(splitName.size()-1).toStdString());

}

void MainWindow::handleSecondButton() {
    OptionDialogue dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        emit statusUpdateMessage(QString("Dialog accepted "), 0);
    }
    else {
        emit statusUpdateMessage(QString("Dialog rejected "), 0);
    }
}

void MainWindow::on_actionItem_Options_triggered() {
    QModelIndex index = ui->treeView->currentIndex();

    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    QString text = selectedPart->data(0).toString();

    emit statusUpdateMessage(QString("The selected item is: " + text), 0);

    OptionDialogue dialog(this, selectedPart);

    if (dialog.exec() == QDialog::Accepted) {
        emit statusUpdateMessage(QString("Dialog accepted "), 0);
    }
    else {
        emit statusUpdateMessage(QString("Dialog rejected "), 0);
    }
}