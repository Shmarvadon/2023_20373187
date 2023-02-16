#ifndef OPTIONDIALOGUE_H
#define OPTIONDIALOGUE_H

#include <QDialog>

namespace Ui {
class OptionDialogue;
}

class OptionDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialogue(QWidget *parent = nullptr);
    ~OptionDialogue();

private:
    Ui::OptionDialogue *ui;
};

#endif // OPTIONDIALOGUE_H
