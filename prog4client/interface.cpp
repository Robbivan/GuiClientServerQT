#include "interface.h"
#include "common.h"
#include "ui_interface.h"

#include <QPushButton>
#include <QMessageBox>
#include "addvaluematrixdialog.h"

TInterface::TInterface(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::TInterface)
{
    ui->setupUi(this);
    setWindowTitle(QStringLiteral("Лучшая прога для матрицы!!!"));
    connect(ui->inputValueButton, &QPushButton::clicked,
            this, &TInterface::formRequest);
    connect(ui->calcDeterminantButton, &QPushButton::clicked,
            this, &TInterface::formRequest);
    connect(ui->calcRangButton, &QPushButton::clicked,
            this, &TInterface::formRequest);
    connect(ui->outputTransposeButton, &QPushButton::clicked,
            this, &TInterface::formRequest);

//    updateMatrix();
}

TInterface::~TInterface() {
    delete ui;
}

//void TInterface::inputValues() {
//    AddValueMatrixDialog dialog(this);
//    if (dialog.exec() == QDialog::Accepted) {
////        matr = MatrixSquare(dialog.getSize(), dialog.getVector());
//    }
////    updateMatrix();
//}

//void TInterface::determinant() {
//    QMessageBox msg(this);
//    msg.setWindowTitle(QStringLiteral("Ответ на запрос"));
//    QString ans;
//    ans << matr.determinant();
//    msg.setText(QStringLiteral("Определитель матрицы равен ") + ans);
//    msg.exec();
//}

//void TInterface::rank() {
//    QMessageBox msg(this);
//    msg.setWindowTitle(QStringLiteral("Ответ на запрос"));
//    QString ans = QString().setNum(matr.rank());
//    msg.setText(QStringLiteral("Ранг матрицы равен ") + ans);
//    msg.exec();
//}

//void TInterface::transpose() {
//    QMessageBox msg(this);
//    msg.setWindowTitle(QStringLiteral("Ответ на запрос"));
//    QString ans;
//    ans << matr.transposed();
//    msg.setText(QStringLiteral("Транспонированная матрица:\n") + ans);
//    msg.exec();
//}

//void TInterface::updateMatrix() {
//    QString label;
//    label << matr;
//    ui->curMatrix->setText(label);
//}

void TInterface::formRequest()
{
    QString msg;

    QPushButton *btn = static_cast<QPushButton*>(sender());
    if (btn == ui->inputValueButton)
    {
        msg <<  QString().setNum(INPUT_VALUE_REQUEST);
        AddValueMatrixDialog dialog(this);
        if (dialog.exec() != QDialog::Accepted) {
            return;
        }
        auto arrNums = dialog.getVector();
        msg << QString().setNum(dialog.getSize());
        for (const auto& num:arrNums){
            msg << QString().setNum(num.first) << QString().setNum(num.second);
        }

    }
    else if (btn == ui->calcDeterminantButton){
        msg << QString().setNum(DETERMINANT_REQUEST);
    }
    else if (btn == ui->calcRangButton){
          msg << QString().setNum(RANK_REQUEST);
    }
    else if (btn == ui->outputTransposeButton){
         msg << QString().setNum(TRANSPOSE_REQUEST);
    }
    else{
        msg << QString().setNum(UPDATE_REQUEST);
    }

    emit request(msg);
}

void TInterface::answer(QString msg)
{
//    QString text;
//    int p = msg.indexOf(separator);
//    int t = msg.left(p).toInt();
//    msg = msg.mid(p+1,msg.length()-p-2);
//    switch (t)
//    {
//        case VALUE_ANSWER:
//            text = "p";
//            p = msg.indexOf(separator);
//            text += msg.left(p);
//            text += " = ";
//            text += msg.right(msg.length()-p-1);
//            output->setText(text);
//            break;
//        case PRINT_ANSWER:
//            text = "p(x) = ";
//            text += msg;
//            output->setText(text);
//            break;
//        default: break;
//    }
}
