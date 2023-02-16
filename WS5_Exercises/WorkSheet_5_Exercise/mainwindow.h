#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <qfiledialog.h>
#include "optiondialogue.h"
#include "ModelPart.h"
#include "ModelPartList.h"

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
