#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <qfiledialog.h>
#include "optiondialogue.h"
#include "ModelPart.h"
#include "ModelPartList.h"

#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkCylinder.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkCamera.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ModelPartList* partList;

signals:

    void statusUpdateMessage(const QString& message, int timeout);

private slots:
    void handleButton();

    void handleTreeClicked();

    void on_actionOpenFile_triggered();

    void handleSecondButton();

    void on_actionItem_Options_triggered();

private:
    Ui::MainWindow *ui;

    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;


    void updateRenderFromTree(const QModelIndex& index);
};
#endif // MAINWINDOW_H
