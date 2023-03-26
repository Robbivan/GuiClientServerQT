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

    std::vector<std::pair<int,int>> getVector();
    size_t getSize();

public slots:
    void inputSize();
    void addValue();
private:
    QIntValidator *valNum, *valDiv, *valSize;
    Ui::AddValueMatrixDialog *ui;
    size_t size = 0;
    std::vector<std::pair<int,int>> arrNums;
protected:
    void accept() override;
};

#endif // ADDVALUEMATRIXDIALOG_H
