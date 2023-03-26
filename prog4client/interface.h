#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
//#include "matrix.h"

namespace Ui {
    class TInterface;
}

class TInterface : public QWidget
{
    Q_OBJECT

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();
public slots:
    void inputValues();
//    void transpose();
//    void rank();
//    void determinant();

private:
    Ui::TInterface *ui;
    //MatrixSquare matr;

    //void updateMatrix();

public slots:
    void answer(QString);

private slots:
    void formRequest();

signals:
    void request(QString);
};
#endif // TINTERFACE_H
