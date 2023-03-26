#ifndef ADDVALUEMATRIXDIALOG_H
#define ADDVALUEMATRIXDIALOG_H

#include <QDialog>
#include <QIntValidator>
#include <vector>
//#include "number.h"

namespace Ui {
    class AddValueMatrixDialog;
}

class AddValueMatrixDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddValueMatrixDialog(QWidget *parent = nullptr);
    ~AddValueMatrixDialog();

//    std::vector<number> getVector();
    size_t getSize();

public slots:
    void inputSize();
    void addValue();
private:
    QIntValidator *valNum, *valDiv, *valSize;
    Ui::AddValueMatrixDialog *ui;
    size_t size = 0;
//    std::vector<number> arrNums;
protected:
    void accept() override;
};

#endif // ADDVALUEMATRIXDIALOG_H
