#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

class Point 
{
public:
    double x, y;
//Или конструктор по умолчанию
    Point(double x = 0, double y = 0) : 
// одной буквой 
    x(x), 
    y(y) 
    {

    } 
};

class Shape 
{
protected:
    double density;

public:
    Shape(double d) : 
    density(d) 
    {

    }

    virtual ~Shape() 
    {

    }

    virtual double S() const = 0;

    double mass() const 
    {
        return S() * density;
    }
};

class Circle : public Shape 
{
    double R;

public:
    Circle(double r, double d) : 
    Shape(d), 
    R(r) 
    {

    }

    double S() const override 
    {
        // Можно по-другому pi
        return M_PI * R * R;
    }
};

class Polygon : public Shape 
{
    // Можно по-другому
    Point* data;
    int n;

public:
    Polygon(Point* array, int N, double d) : 
    Shape(d), 
    n(N) 
    {
        data = new Point[n];
        for (int i = 0; i < n; ++i) 
        {
            data[i] = array[i];
        }
    }

    ~Polygon() override 
    {
        delete[] data;
    }

    double S() const override 
    {
         double area = 0;
       for (int i = 0; i < n; ++i)
       {
            int next = (i + 1) % n; // Xn = X0
            area += data[i].x * data[next].y - data[next].x * data[i].y;
       }
// abs(area) / 2 получим int
        return std::abs(area) / 2;
    }
};

double function(Shape* obj) 
{
    return obj->mass();
}

int main() 
{
    Shape* ptr = nullptr;
    bool a;

    std::cout << "Circle - 1, Polygon - 0: ";
    std::cin >> a;

    if (a) 
    {
        ptr = new Circle(5.0, 3);
    } else 
    {
        Point p[4];

        p[0].x = 0; p[0].y = 0;
        p[1].x = 3; p[1].y = 0;
        p[2].x = 2; p[2].y = 2;
        p[3].x = 0; p[3].y = 2;

        ptr = new Polygon(p, 4, 1.2);
    }

    std::cout << "m = " << function(ptr) << std::endl;

    delete ptr;
    
    return 0;
}
