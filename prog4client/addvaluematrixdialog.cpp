#include "addvaluematrixdialog.h"
#include "ui_addvaluematrixdialog.h"
#include <QMessageBox>

AddValueMatrixDialog::AddValueMatrixDialog(QWidget *parent) :
    QDialog(parent),
    valNum(new QIntValidator(0, INT_MAX, this)),
    valDiv(new QIntValidator(0, INT_MAX, this)),
    valSize(new QIntValidator(0, INT_MAX, this)),
    ui(new Ui::AddValueMatrixDialog)
{
    ui->setupUi(this);

    ui->numeratorLineEdit->setValidator(valNum);
    ui->dividerLineEdit->setValidator(valDiv);
    ui->sizeLineEdit->setValidator(valSize);
    connect(ui->sizeButton, &QPushButton::clicked,
            this, &AddValueMatrixDialog::inputSize);
    connect(ui->nextValueButton, &QPushButton::clicked,
            this, &AddValueMatrixDialog::addValue);

    setWindowTitle(QStringLiteral("Ввод матрицы:"));

}

void AddValueMatrixDialog::accept(){
    if (size == 0 || size * size != arrNums.size()) {
        QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Не до конца введены данные!!!"));
        return;
    }

    QDialog::accept();
}

std::vector<std::pair<int,int>> AddValueMatrixDialog::getVector() {
    return arrNums;
}

size_t AddValueMatrixDialog::getSize() {
    return size;
}

AddValueMatrixDialog::~AddValueMatrixDialog() {
    delete ui;
    delete valNum;
    delete valDiv;
    delete valSize;
}

void AddValueMatrixDialog::inputSize() {
    size = ui->sizeLineEdit->text().toInt();
    if (size == 0) {
        QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Размер не может быть равен 0!!!"));
        return;
    }
    arrNums.reserve(size * size);
    ui->numeratorLineEdit->setEnabled(true);
    ui->dividerLineEdit->setEnabled(true);
    ui->nextValueButton->setEnabled(true);
    ui->isNegativeCheckBox->setEnabled(true);
    ui->sizeButton->setEnabled(false);
    ui->sizeLineEdit->setEnabled(false);
    ui->mainLabel->setText(QStringLiteral("Ввести значение a[0][0]:"));
}

void AddValueMatrixDialog::addValue() {
    int div = ui->dividerLineEdit->text().toInt(),
        num = ui->numeratorLineEdit->text().toInt();
    size_t cur_size = arrNums.size();
    bool is_neg = ui->isNegativeCheckBox->isChecked();

    if (size * size == cur_size) {
        QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Все значения уже заполнены!"));
        return;
    }
    if (div == 0) {
        QMessageBox::warning(this, QStringLiteral("ОШИБКА"), QStringLiteral("Число не может делиться на ноль!!!"));
        return;
    }
    arrNums.emplace_back(is_neg ? -num : num, div);
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
