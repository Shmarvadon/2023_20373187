#include "optiondialogue.h"
#include "ui_optiondialogue.h"

OptionDialogue::OptionDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionDialogue)
{
    ui->setupUi(this);
}

OptionDialogue::~OptionDialogue()
{
    delete ui;
}
