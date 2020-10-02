#include <iostream>
#include <string>
#include <vector>
#include <math.h>




struct Point
{
    Point(double x, double y) : _x(x), _y(y) {}
    double _x;
    double _y;
};

Point getMean(const std::vector<Point>& points)
{
    Point result(0,0);

    for(auto point : points)
    {
        result._x += point._x;
        result._y += point._y;
    }

    result._x /= points.size();
    result._y /= points.size();

    return result;
}

Point getSTD(const std::vector<Point>& points)
{
    Point result(0,0);
    Point mean = getMean(points);

    for(auto point : points)
    {
        result._x += pow( ( point._x - mean._x ), 2 );
        result._y += pow( ( point._y - mean._y ), 2 );
    }

    result._x = sqrt( result._x  / (points.size() - 1) );
    result._y = sqrt( result._y  / (points.size() - 1) );

    return result;
}

double getSxy(const std::vector<Point>& points)
{
    double result = 0;
    Point mean = getMean(points);

    for(auto point : points)
    {
        result += (point._x - mean._x ) * ( point._y - mean._y );
    }

    return result / (points.size() - 1);
}

double getRxy(const std::vector<Point>& points)
{
    double Sxy = getSxy(points);
    Point STD = getSTD(points);

    return (Sxy / (STD._x * STD._y));
}

double getSlope(const std::vector<Point>& points)
{
    double Rxy = getRxy(points);
    Point STD = getSTD(points);

    return Rxy * ( STD._y / STD._x );
}

double getOffset(const std::vector<Point>& points)
{
    double slope = getSlope(points);
    Point mean = getMean(points);

    return mean._y - slope * mean._x;
}

int main()
{
    std::cout << "ein x y Wertepaar pro Zeile durch Leerzeichen getrennt eingeben, \"end\" beendet die Eingabe" << std::endl;
    std::string x;
    std::string y;
    std::vector<Point> points;

    while(true)
    {
        std::cin >> x;
        if(x == "end") break;
        std::cin >> y;
        points.emplace_back(std::stod(x), std::stod(y));
    }

    Point mean = getMean(points);
    Point STD = getSTD(points);
    double Sxy = getSxy(points);
    double Rxy = getRxy(points);
    double k = getSlope(points);
    double d = getOffset(points);


    std::cout << "\n-------------------\n" << std::endl;
    std::cout << "Mittelwert(x):               " << mean._x << std::endl;
    std::cout << "Mittelwert(y):               " << mean._y << std::endl;
    std::cout << "StandardAbweichung(x):       " << STD._x << std::endl;
    std::cout << "StandardAbweichung(y):       " << STD._y << std::endl;
    std::cout << "Kovarianz Sxy:               " << Sxy << std::endl;
    std::cout << "Korrelationskoeffizient Rxy: " << Rxy << std::endl;
    std::cout << "Steigung k:                  " << k << std::endl;
    std::cout << "Verschiebung d:              " << d << std::endl;
    std::cout << "Regressionsgerade:           f(x) = " << k << "x + " << d << std::endl;


    return 0;
}
