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

    // VTK stuff.

    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    ui->widget->setRenderWindow(renderWindow);

    // Add a renderer

    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);

    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    vtkNew<vtkActor> cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(1.0,0.0,0.35);
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);

    renderer->AddActor(cylinderActor);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();
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

    // Ensuring that the open dialogue actually returns a string of which is a file name that can be loaded.
    if (splitName.at(splitName.size() - 1) != "") {
        QString name, visible("true");
        partList->appendChild(index, { splitName.at(splitName.size() - 1), visible });
        static_cast<ModelPart*>(index.internalPointer())->loadSTL(fileName);

        renderer->RemoveAllViewProps();
        updateRenderFromTree(partList->index(0, 0, QModelIndex()));
        renderer->Render();
        
    }
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

void MainWindow::updateRenderFromTree(const QModelIndex& index) {
    if (index.isValid()) {
        ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());


        renderer->AddActor(selectedPart->getActor());
    }

    // Check to see if the part has any children and update them in the renderer.
    if (!partList->hasChildren(index) || (index.flags() & Qt::ItemNeverHasChildren)) return;

    // If it has children loop through re adding them to render.
    int rows = partList->rowCount(index);
    for (int i = 0; i < rows; i++) {
        updateRenderFromTree(partList->index(i, 0, index));
    }
}