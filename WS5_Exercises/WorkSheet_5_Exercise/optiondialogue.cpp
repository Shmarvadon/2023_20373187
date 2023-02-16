#include "optiondialogue.h"
#include "ui_optiondialogue.h"

OptionDialogue::OptionDialogue(QWidget *parent, ModelPart* pPart) :
    QDialog(parent),
    ui(new Ui::OptionDialogue),
    _pPart(pPart)

{

    if (_pPart == nullptr) { throw std::runtime_error("Can not call properties edit on nullptr"); }
    ui->setupUi(this);

    ui->lineEdit_2->setText(QString(std::to_string(pPart->getColourR()).c_str()));
    ui->lineEdit_3->setText(QString(std::to_string(pPart->getColourG()).c_str()));
    ui->lineEdit_4->setText(QString(std::to_string(pPart->getColourB()).c_str()));

    ui->lineEdit->setText(QString(pPart->getName().c_str()));

    ui->checkBox->setChecked(pPart->visible());
}

OptionDialogue::~OptionDialogue()
{
    uint8_t R, G, B;

    // get the values entered and set 0 if not in proper range (will add error checking later).
    R = (ui->lineEdit_2->text().toInt() < 256 && ui->lineEdit_2->text().toInt() >= 0) ? ui->lineEdit_2->text().toInt() : 0;
    G = (ui->lineEdit_3->text().toInt() < 256 && ui->lineEdit_3->text().toInt() >= 0) ? ui->lineEdit_3->text().toInt() : 0;
    B = (ui->lineEdit_4->text().toInt() < 256 && ui->lineEdit_4->text().toInt() >= 0) ? ui->lineEdit_4->text().toInt() : 0;

    // Set the values.
    _pPart->setColour(R,G,B);

    // Set the new name.
    _pPart->setName(ui->lineEdit->text().toStdString());

    // Set the new is visible thingy.
    _pPart->setVisible(ui->checkBox->isChecked());
   
    delete ui;
}
