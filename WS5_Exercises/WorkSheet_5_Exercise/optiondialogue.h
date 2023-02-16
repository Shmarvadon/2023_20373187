#ifndef OPTIONDIALOGUE_H
#define OPTIONDIALOGUE_H

#include <QDialog>

#include <stdexcept>

#include "ModelPart.h"

namespace Ui {
class OptionDialogue;
}

class OptionDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialogue(QWidget *parent = nullptr, ModelPart* pPart = nullptr);
    ~OptionDialogue();

private:
    Ui::OptionDialogue *ui;
    ModelPart* _pPart;
};

#endif // OPTIONDIALOGUE_H
