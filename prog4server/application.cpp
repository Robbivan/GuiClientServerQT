#include "application.h"
#include "matrix.h"
#include "common.h"


TApplication::TApplication(int argc, char *argv[])
            : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                         QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(pars, this);

    connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(recieve(QByteArray)));
}

QByteArray& operator>>(QByteArray& in, double& number) {
    int pos = in.indexOf(separator.toLatin1());
    pos = in.indexOf(separator.toLatin1(), pos + 1);

    if (pos > 0) {
        number = in.left(pos).toDouble();
        in = in.right(in.length() - (pos + 1));
    }
    return in;
}

QString& operator<<(QString& s, const double& number) {
    s += QString().setNum(number);
    return s;
}

template<typename number>
void inputValueRequest(QString& answer,QByteArray& msg, MatrixSquare<number>& matrix){
    QString s;

    int pos = msg.indexOf(separator.toLatin1()), posSep;
    int t = msg.left(pos).toInt();
    int size;

    std::vector<number> input;
    number x;
    QString tmp;

    switch (t)
    {
        case INPUT_VALUE_REQUEST:
             msg = msg.right(msg.length() - (pos + 1));
             pos = msg.indexOf(separator.toLatin1());
             size = msg.left(pos).toInt();
             msg = msg.right(msg.length() - (pos + 1));

             input.reserve(size);

             for (size_t i = 0; i < size * size; ++i) {
                 posSep = msg.indexOf(separator.toLatin1());
                 msg >> x;
                 input.push_back(x);
             }
             matrix = MatrixSquare(size, input);
             answer << QString().setNum(INPUT_VALUE_ANSWER);
             tmp << matrix;
             answer << tmp;
             break;
        case UPDATE_REQUEST:
             answer << QString().setNum(UPDATE_ANSWER);
             tmp << matrix;
             answer << tmp;
             break;
        case DETERMINANT_REQUEST:
             answer << QString().setNum(DETERMINANT_ANSWER);
             tmp << matrix.determinant();
             answer << (QStringLiteral("Определитель матрицы равен ") + tmp);
             break;
        case RANK_REQUEST:
             answer << QString().setNum(DETERMINANT_ANSWER);
             answer << (QStringLiteral("Ранг матрицы равен ") + QString().setNum(matrix.rank()));
             break;
        case TRANSPOSE_REQUEST:
             tmp = QStringLiteral("Транспонированная матрица равна:\n");
             tmp << matrix.transposed();
             answer << QString().setNum(TRANSPOSE_ANSWER);
             answer << tmp;
             break;
        default:
            return ;

    }
}


void TApplication::recieve(QByteArray msg)
{
    QString answer;

    int pos = msg.indexOf(separator.toLatin1());
    int flag = msg.left(pos).toInt();

    msg = msg.right(msg.length() - (pos + 1));
    switch(flag){
        case IS_DOUBLE:
            inputValueRequest<double>(answer, msg, matrixDouble);
            break;
        case IS_COMPLEX:
            inputValueRequest<TComplex>(answer, msg, matrixComplex);
            break;
        case IS_RATIONAL:
            inputValueRequest<TRational>(answer, msg, matrixRational);
            break;
        default:
            return;
    }
    comm->send(QByteArray().append(answer.toStdString()));

}
