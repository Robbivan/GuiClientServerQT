#include "addvaluematrixdialog.h"
#include "ui_addvaluematrixdialog.h"
#include <QMessageBox>

AddValueMatrixDialog::AddValueMatrixDialog(QWidget *parent) :
    QDialog(parent),
    valNum(new QIntValidator(0, INT_MAX, this)),
    valDiv(new QIntValidator(0, INT_MAX, this)),
    valSize(new QIntValidator(0, INT_MAX, this)),
    valReal(new QDoubleValidator(-1'000'000, 1'000'000, 4)),
    valImg(new QDoubleValidator(-1'000'000, 1'000'000, 4)),

    ui(new Ui::AddValueMatrixDialog)
{
    ui->setupUi(this);

    ui->sizeLineEdit->setValidator(valSize);

    connect(ui->sizeButton, &QPushButton::clicked,
            this, &AddValueMatrixDialog::inputSize);
    connect(ui->nextValueButton, &QPushButton::clicked,
            this, &AddValueMatrixDialog::addValue);

    connect(ui->rationalButton, &QRadioButton::clicked,
            this, &AddValueMatrixDialog::isRationalClick);
    connect(ui->complexButton, &QPushButton::clicked,
            this, &AddValueMatrixDialog::isComlexClick);
    connect(ui->doubleButton, &QPushButton::clicked,
            this, &AddValueMatrixDialog::isDoubleClick);

    setWindowTitle(QStringLiteral("Ввод матрицы:"));
}
void AddValueMatrixDialog::isRationalClick() {
    ui->numeratorLineEdit->setValidator(valNum);
    ui->dividerLineEdit->setValidator(valDiv);
    elem = IS_RATIONAL;
    ui->sizeLineEdit->setEnabled(true);
    ui->sizeButton->setEnabled(true);

    ui->separator->setText(QStringLiteral(" / "));

    ui->complexButton->setEnabled(false);
    ui->doubleButton->setEnabled(false);
    ui->rationalButton->setEnabled(false);
}

void AddValueMatrixDialog::isComlexClick() {
    ui->numeratorLineEdit->setValidator(valReal);
    ui->dividerLineEdit->setValidator(valImg);
    elem = IS_COMPLEX;
    ui->sizeLineEdit->setEnabled(true);
    ui->sizeButton->setEnabled(true);

    ui->separator->setText(QStringLiteral(" + "));
    ui->forComplexLabel->setText("i");

    ui->complexButton->setEnabled(false);
    ui->doubleButton->setEnabled(false);
    ui->rationalButton->setEnabled(false);
}

void AddValueMatrixDialog::isDoubleClick() {
    ui->numeratorLineEdit->setValidator(valReal);
    elem = IS_DOUBLE;
    ui->sizeLineEdit->setEnabled(true);
    ui->sizeButton->setEnabled(true);

    ui->separator->setText(QStringLiteral(""));

    ui->complexButton->setEnabled(false);
    ui->doubleButton->setEnabled(false);
    ui->rationalButton->setEnabled(false);
}

void AddValueMatrixDialog::accept(){
    if (size == 0 ||
        (elem == IS_COMPLEX && (size * size != arrComplexNums.size())) ||
        (elem == IS_RATIONAL && (size * size != arrRationalNums.size())) ||
        (elem == IS_DOUBLE && (size * size != arrDoubleNums.size()))) {
        QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Не до конца введены данные!!!"));
        return;
    }

    QDialog::accept();
}

std::vector<std::pair<int,int>> AddValueMatrixDialog::getVectorRational() {
    return arrRationalNums;
}

std::vector<double> AddValueMatrixDialog::getVectorDouble() {
    return arrDoubleNums;
}

std::vector<std::pair<double,double>> AddValueMatrixDialog::getVectorComplex() {
    return arrComplexNums;
}

size_t AddValueMatrixDialog::getSize() {
    return size;
}

numbers AddValueMatrixDialog::getType() {
    return elem;
}

AddValueMatrixDialog::~AddValueMatrixDialog() {
    delete ui;
    delete valNum;
    delete valDiv;
    delete valSize;
    delete valReal;
    delete valImg;
}

void AddValueMatrixDialog::inputSize() {
    size = ui->sizeLineEdit->text().toInt();
    if (size == 0) {
        QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Размер не может быть равен 0!!!"));
        return;
    }

    switch(elem) {
        case IS_COMPLEX:
            arrComplexNums.reserve(size * size);
            ui->dividerLineEdit->setEnabled(true);
            break;
        case IS_DOUBLE:
            arrDoubleNums.reserve(size * size);
            break;
        case IS_RATIONAL:
            arrRationalNums.reserve(size * size);
            ui->isNegativeCheckBox->setEnabled(true);
            ui->dividerLineEdit->setEnabled(true);
            break;
    }

    ui->numeratorLineEdit->setEnabled(true);
    ui->nextValueButton->setEnabled(true);
    ui->sizeButton->setEnabled(false);
    ui->sizeLineEdit->setEnabled(false);
    ui->mainLabel->setText(QStringLiteral("Ввести значение a[0][0]:"));
}

void AddValueMatrixDialog::addValue() {
    int div, num;
    double real, img;
    size_t cur_size;
    bool is_neg;

    switch(elem) {
        case IS_COMPLEX:
            real = ui->numeratorLineEdit->text().toDouble();
            img = ui->dividerLineEdit->text().toDouble();
            cur_size = arrComplexNums.size();
            if (size * size == cur_size) {
                QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Все значения уже заполнены!"));
               return;
            }
            arrRationalNums.emplace_back(real, img);
            break;
        case IS_DOUBLE:
            real = ui->numeratorLineEdit->text().toDouble();
            cur_size = arrDoubleNums.size();
            if (size * size == cur_size) {
                QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Все значения уже заполнены!"));
                return;
            }
            arrDoubleNums.emplace_back(real);
            break;
        case IS_RATIONAL:

            div = ui->dividerLineEdit->text().toInt();
            num = ui->numeratorLineEdit->text().toInt();
            is_neg = ui->isNegativeCheckBox->isChecked();
            cur_size = arrRationalNums.size();
            if (size * size == cur_size) {
                QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Все значения уже заполнены!"));
                return;
            }
            if (div == 0) {
                QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Число не может делиться на ноль!!!"));
                return;
            }
            arrRationalNums.emplace_back(is_neg ? -num : num, div);
            break;
    }

    ++cur_size;
    ui->dividerLineEdit->clear();
    ui->numeratorLineEdit->clear();
    if (size * size == cur_size) {
        ui->mainLabel->setText(QStringLiteral("Ввести значение a[*][*]:"));
        ui->dividerLineEdit->setEnabled(false);
        ui->numeratorLineEdit->setEnabled(false);
        ui->nextValueButton->setEnabled(false);
        ui->isNegativeCheckBox->setEnabled(false);
    } else {
        ui->mainLabel->setText(QString("Ввести значение a[%1][%2]:").arg(cur_size / size).arg(cur_size % size));
    }
}
