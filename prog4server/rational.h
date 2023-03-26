#ifndef TRATIONAL_H
#define TRATIONAL_H
#include <iostream>
#include <QString>

class TRational
{
public:
    TRational();

    TRational(int _num);
    TRational(int _num, int _div);
    TRational(const TRational&) = default;
    TRational& operator =(const TRational& other) = default;
    TRational operator -() const;
    TRational operator +() const;
    TRational& operator +=(const TRational& other);
    TRational& operator -=(const TRational& other);
    TRational& operator *=(const TRational& other);
    TRational& operator /=(const TRational& other);

    int get_num() const{
        return num;
    }

    int get_div() const{
        return div;
    }

    friend TRational operator +(TRational left, const TRational& right);
    friend TRational operator -(TRational left, const TRational& right);
    friend TRational operator *(TRational left, const TRational& right);
    friend TRational operator /(TRational left, const TRational& right);
    friend bool operator ==(const TRational& left, const TRational& right);
    friend bool operator !=(const TRational& left, const TRational& right);

    friend std::ostream& operator<<(std::ostream& out, const TRational& num);
    friend std::istream& operator>>(std::istream& in, TRational& num);

    friend QString& operator<<(QString& out, const TRational& num);

private:
    void algorithmEuclidian();
    int num, div;
};

#endif // TRATIONAL_H
