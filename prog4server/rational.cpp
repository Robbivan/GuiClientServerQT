#include "rational.h"
#include "common.h"
QChar TRational::SEPARATOR = separator;

TRational::TRational():num(0),div(1){

}

TRational::TRational(int _num):num(_num),div(1) {

}


TRational::TRational(int _num, int _div) : num(_num), div(_div) {
    algorithmEuclidian();
}


TRational TRational::operator -() const {
    return TRational(-num, div);
}

TRational TRational::operator +() const {
    return *this;
}

TRational& TRational::operator +=(const TRational& other) {
    num = num*other.div+other.num*div;
    div*=other.div;

    algorithmEuclidian();
    return *this;
}

TRational& TRational::operator -=(const TRational& other)  {
    num = num*other.div-other.num*div;
    div*=other.div;
    algorithmEuclidian();
    return *this;
}

TRational& TRational::operator *=(const TRational& other) {
    num*=other.num;
    div*=other.div;
    algorithmEuclidian();
    return *this;
}

TRational& TRational::operator /=(const TRational& other) {
    num*=other.div;
    div*=other.num;
    algorithmEuclidian();
    return *this;
}

TRational operator +(TRational left, const TRational& right) {
    return left += right;
}

TRational operator -(TRational left, const TRational& right) {
    return left -= right;
}

TRational operator *(TRational left, const TRational& right) {
    return left *= right;
}

TRational operator /(TRational left, const TRational& right) {
    return left /= right;
}

bool operator ==(const TRational& left, const TRational& right) {
    return ((left.num == right.num) && (left.div == right.div)) ||
            ((left.num == 0) && (right.num == 0));
}

bool operator !=(const TRational& left, const TRational& right) {
    return !(left == right);
}

std::ostream& operator<<(std::ostream& out, const TRational& rational) {
    out << rational.num << " / " << rational.div;
    return out;
}

QString& operator<<(QString& s, const TRational& rational) {
    s += QString().setNum(rational.num);
    s += QStringLiteral(" / ");
    s += QString().setNum(rational.div);
    return s;
}

std::istream& operator>>(std::istream& in, TRational& rational) {
    in >> rational.num >> rational.div;
    return in;
}

void TRational::algorithmEuclidian(){
    int a = abs(num), b = abs(div);
    if (a == 0) {
        num = 0;
        div = 1;
        return;
    }

    if (a < b) {
        std::swap(a, b);
    }
    while (a % b != 0) {
        a = a % b;
        std::swap(a, b);
    }
    num /= b;
    div /= b;

    if (num < 0 && div < 0) {
        num *= -1;
        div *= -1;
    } else if (num < 0 || div < 0) {
        num = -1 * abs(num);
        div = abs(div);
    }

}

TRational::TRational(const QByteArray& arr) {
    int pos = arr.indexOf(SEPARATOR.toLatin1());
    num = arr.left(pos).toInt();
    div = arr.right(arr.length() - (pos + 1)).toInt();
    algorithmEuclidian();
}

QByteArray& operator>>(QByteArray& in, TRational& number) {
    int pos = in.indexOf(TRational::SEPARATOR.toLatin1());
    pos = in.indexOf(TRational::SEPARATOR.toLatin1(), pos + 1);
    if (pos > 0) {
        number = TRational(in.left(pos));
        in = in.right(in.length() - (pos + 1));
    }

    return in;
}
