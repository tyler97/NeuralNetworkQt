#ifndef POINT_H
#define POINT_H
#include <QString>

class Point
{
public:
    Point();
    Point(double,double, QString);
    double x;
    double y;
    QString Class;
};

#endif // POINT_H
