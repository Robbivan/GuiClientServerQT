#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include "common.h"

namespace Ui {
    class TInterface;
}

class TInterface : public QWidget
{
    Q_OBJECT

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

private:
    Ui::TInterface *ui;
    numbers type = IS_COMPLEX;

public slots:
    void answer(QString);

private slots:
    void formRequest();

signals:
    void request(QString);
};
#endif // TINTERFACE_H
