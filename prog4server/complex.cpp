#include "complex.h"

TComplex::TComplex() : real(0.), image(0.) {

}

TComplex::TComplex(double _real) : real(_real), image(0.) {

}

TComplex::TComplex(double _real, double _image) : real(_real), image(_image) {

}

TComplex::TComplex(int _real) : real(_real), image(0.) {

}

TComplex TComplex::operator -() const {
    return TComplex(-real, -image);
}

TComplex TComplex::operator +() const {
    return *this;
}

TComplex& TComplex::operator +=(const TComplex& other) {
    real += other.real;
    image += other.image;
    return *this;
}

TComplex& TComplex::operator -=(const TComplex& other)  {
    real -= other.real;
    image -= other.image;
    return *this;
}

TComplex& TComplex::operator *=(const TComplex& other) {
    double cur_real = real, cur_image = image;
    real = cur_real * other.real - cur_image * other.image;
    image = cur_real * other.image + cur_image * other.real;
    return *this;
}

TComplex& TComplex::operator /=(const TComplex& other) {
    double cur_real = real, cur_image = image;

    real = (cur_real * other.real + cur_image * other.image) / (other.real * other.real + other.image * other.image);
    image = (-cur_real * other.image + cur_image * other.real) / (other.real * other.real + other.image * other.image);

    return *this;
}

TComplex operator +(TComplex left, const TComplex& right) {
    return left += right;
}

TComplex operator -(TComplex left, const TComplex& right) {
    return left -= right;
}

TComplex operator *(TComplex left, const TComplex& right) {
    return left *= right;
}

TComplex operator /(TComplex left, const TComplex& right) {
    return left /= right;
}

bool operator ==(const TComplex& left, const TComplex& right) {
    return (left.real == right.real) && (left.image == right.image);
}

bool operator !=(const TComplex& left, const TComplex& right) {
    return !(left == right);
}

std::ostream& operator<<(std::ostream& out, const TComplex& num) {
    out << num.real << " + " << num.image << "i";
    return out;
}

std::istream& operator>>(std::istream& in, TComplex& num) {
    in >> num.real >> num.image;
    return in;
}

QString& operator<<(QString& s, const TComplex& complex) {
    s += QString().setNum(complex.real);
    s += QStringLiteral(" + ");
    s += QString().setNum(complex.image);
    s += QStringLiteral("i");
    return s;
}

QByteArray& operator>>(QByteArray& in, TComplex& number) {
    int pos = in.indexOf(TComplex::SEPARATOR.toLatin1());
    pos = in.indexOf(TComplex::SEPARATOR.toLatin1(), pos + 1);
    if (pos > 0) {
        number = TComplex(in.left(pos));
        in = in.right(in.length() - (pos + 1));
    }
    return in;
}

TComplex::TComplex(const QByteArray& arr) {
    int pos = arr.indexOf(SEPARATOR.toLatin1());
    real = arr.left(pos).toDouble();
    image = arr.right(arr.length() - (pos + 1)).toDouble();
}



