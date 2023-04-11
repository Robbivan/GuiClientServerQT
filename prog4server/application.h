#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include "matrix.h"
#include "communicator.h"

class TApplication : public QCoreApplication
{
    Q_OBJECT

    TCommunicator *comm;

public:

    TApplication(int, char**);
private:
    MatrixSquare matrix;


public slots:

    void recieve(QByteArray);

};

#endif // APPLICATION_H
