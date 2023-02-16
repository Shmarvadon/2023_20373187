/********************************************************************************
** Form generated from reading UI file 'optiondialogue.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONDIALOGUE_H
#define UI_OPTIONDIALOGUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_OptionDialogue
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QCheckBox *checkBox;

    void setupUi(QDialog *OptionDialogue)
    {
        if (OptionDialogue->objectName().isEmpty())
            OptionDialogue->setObjectName("OptionDialogue");
        OptionDialogue->resize(400, 300);
        buttonBox = new QDialogButtonBox(OptionDialogue);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(OptionDialogue);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(10, 40, 221, 23));
        lineEdit_2 = new QLineEdit(OptionDialogue);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(10, 80, 41, 23));
        lineEdit_3 = new QLineEdit(OptionDialogue);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(100, 80, 41, 23));
        lineEdit_4 = new QLineEdit(OptionDialogue);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(190, 80, 41, 23));
        checkBox = new QCheckBox(OptionDialogue);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(100, 130, 70, 21));

        retranslateUi(OptionDialogue);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, OptionDialogue, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, OptionDialogue, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(OptionDialogue);
    } // setupUi

    void retranslateUi(QDialog *OptionDialogue)
    {
        OptionDialogue->setWindowTitle(QCoreApplication::translate("OptionDialogue", "Dialog", nullptr));
        checkBox->setText(QCoreApplication::translate("OptionDialogue", "IsVisible", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OptionDialogue: public Ui_OptionDialogue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONDIALOGUE_H
