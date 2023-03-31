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

void TApplication::recieve(QByteArray msg)
{
    QString answer, s;

    int pos = msg.indexOf(separator.toLatin1()), posSep;
    int t = msg.left(pos).toInt();
    size_t size;
    std::vector<number> input;
    number x;

    switch (t)
    {
        case INPUT_VALUE_REQUEST:
            msg = msg.right(msg.length() - (pos + 1));
            size = msg.toInt();
            msg = msg.right(1);
            input.reserve(size);
            for (size_t i = 0; i < size; ++i) {
                posSep = msg.indexOf(separator.toLatin1());
                msg >> x;
            }
            matrix = MatrixSquare(size, input);
            break;
        case UPDATE_REQUEST:
            break;
        case DETERMINANT_REQUEST:
            break;
        case RANK_REQUEST:
            break;
        case TRANSPOSE_REQUEST:
            break;
        default:
            return;

//            msg = msg.right(msg.length()-pos-1);
//            msg>>x;
//            v = p.value(x);
//            s<<(QString)x<<(QString)v;
//            answer<<QString().setNum(VALUE_ANSWER);
//            answer += s;
//            break;
//        case PRINT_CLASSIC_REQUEST:
//            p.setPrintMode(EPrintModeClassic);
//            s<<p;
//            answer<<QString().setNum(PRINT_ANSWER)<<s;
//            break;
//        default: return;
    }
    comm->send(QByteArray().append(answer.toStdString()));
}
