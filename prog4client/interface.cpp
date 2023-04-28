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
    connect(ui->updateButton, &QPushButton::clicked,
            this, &TInterface::formRequest);
}

TInterface::~TInterface() {
    delete ui;
}


void TInterface::formRequest()
{
    QString msg;

    QPushButton *btn = static_cast<QPushButton*>(sender());
    if (btn == ui->inputValueButton)
    {
        AddValueMatrixDialog dialog(this);
        if (dialog.exec() != QDialog::Accepted) {
            return;
        }

        type = dialog.getType();
        decltype(dialog.getVectorComplex()) arrComplexNums;
        decltype(dialog.getVectorDouble()) arrDoubleNums;
        decltype(dialog.getVectorRational()) arrRationalNums;

        msg << QString().setNum(type);
        msg << QString().setNum(INPUT_VALUE_REQUEST);
        switch(type) {
            case IS_COMPLEX:
                arrComplexNums = dialog.getVectorComplex();
                msg << QString().setNum(dialog.getSize());
                for (const auto& num: arrComplexNums){
                    msg << QString().setNum(num.first) << QString().setNum(num.second);
                }
                break;
            case IS_DOUBLE:
                arrDoubleNums = dialog.getVectorDouble();
                msg << QString().setNum(dialog.getSize());
                for (const auto& num: arrDoubleNums){
                    msg << QString().setNum(num);
                }
                break;
            case IS_RATIONAL:
                arrRationalNums = dialog.getVectorRational();
                msg << QString().setNum(dialog.getSize());
                for (const auto& num: arrRationalNums){
                    msg << QString().setNum(num.first) << QString().setNum(num.second);
                }
                break;
        }

    }
    else if (btn == ui->calcDeterminantButton){
        msg << QString().setNum(type);
        msg << QString().setNum(DETERMINANT_REQUEST);
    }
    else if (btn == ui->calcRangButton){
        msg << QString().setNum(type);
        msg << QString().setNum(RANK_REQUEST);
    }
    else if (btn == ui->outputTransposeButton){
        msg << QString().setNum(type);
        msg << QString().setNum(TRANSPOSE_REQUEST);
    }
    else {
        msg << QString().setNum(type);
        msg << QString().setNum(UPDATE_REQUEST);
    }

    emit request(msg);
}

void TInterface::answer(QString msg)
{
    QString text;
    int pos = msg.indexOf(separator);
    if (pos == -1) {
        QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Сервер не отвечает!"));
        return;
    }

    int t = msg.left(pos).toInt(), pos2 = msg.indexOf(separator, pos + 1);
    text = msg.mid(pos + 1, pos2 - (pos + 1));
    QMessageBox msgBox(this);
    switch (t)
    {
        case INPUT_VALUE_ANSWER:
        case UPDATE_ANSWER:
            ui->curMatrix->setText(text);
            break;
        case DETERMINANT_ANSWER:
        case RANK_ANSWER:
        case TRANSPOSE_ANSWER:
            msgBox.setWindowTitle(QStringLiteral("Ответ на запрос"));
            msgBox.setText(text);
            msgBox.exec();
            break;
        default:
            QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Сервер ответил неизвестной командой!"));
            return;
    }
}
