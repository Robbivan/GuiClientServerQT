#ifndef ADDVALUEMATRIXDIALOG_H
#define ADDVALUEMATRIXDIALOG_H

#include <QDialog>
#include <QIntValidator>
#include <vector>

#include "common.h"

namespace Ui {
    class AddValueMatrixDialog;
}

class AddValueMatrixDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddValueMatrixDialog(QWidget *parent = nullptr);
    ~AddValueMatrixDialog();

    std::vector<std::pair<int,int>> getVectorRational();
    std::vector<std::pair<double,double>> getVectorComplex();
    std::vector<double> getVectorDouble();

    size_t getSize();
    numbers getType();

public slots:
    void inputSize();
    void addValue();

    void isRationalClick();
    void isComlexClick();
    void isDoubleClick();

private:

    numbers elem;

    QIntValidator *valNum, *valDiv, *valSize;
    QDoubleValidator *valReal, *valImg;
    Ui::AddValueMatrixDialog *ui;
    size_t size = 0;
    std::vector<std::pair<int,int>> arrRationalNums;
    std::vector<double> arrDoubleNums;
    std::vector<std::pair<double,double>> arrComplexNums;
protected:
    void accept() override;
};

#endif // ADDVALUEMATRIXDIALOG_H
