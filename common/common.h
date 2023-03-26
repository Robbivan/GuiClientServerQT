#ifndef COMMON_H
#define COMMON_H

#include <QString>

//enum messages
//{
//    VALUE_REQUEST = 1,
//    VALUE_ANSWER,
//    PRINT_CLASSIC_REQUEST,
//    PRINT_CANONIC_REQUEST,
//    PRINT_ANSWER,
//};

enum messages{
    INPUT_VALUE_REQUEST = 1,
    INPUT_VALUE_ANSWER,
    UPDATE_REQUEST,
    UPDATE_ANSWER,
    DETERMINANT_REQUEST,
    DETERMINANT_ANSWER,
    RANK_REQUEST,
    RANK_ANSWER,
    TRANSPOSE_REQUEST,
    TRANSPOSE_ANSWER
};

extern const QChar separator;
QString& operator<< (QString&,const QString&);

#endif // COMMON_H
