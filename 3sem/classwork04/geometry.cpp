#include <iostream>
#include <vector>
#include <cmath>


struct Point{
    double x = 0.;
    double y = 0.;

    Point(double x, double y) : x(x), y(y) { }
};

double distance(Point const &p1, Point const &p2){
    return std::sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}


class Shape {
    public:
        Shape(std::vector<Point> a) : storage(a) { }
    protected:
        std::vector<Point> storage;
    public:
        virtual double area() = 0;
        virtual double perimeter() = 0;
        virtual Point center() = 0;
};

class Triangle: public Shape {
    private:
        double a, b, c, p;
        void Calculate_sides(){
            a = distance(storage[0], storage[1]);
            b = distance(storage[1], storage[2]);
            c = distance(storage[2], storage[0]);
            p = (a + b + c)/2;
        }

    public:
        Triangle(std::vector<Point> a) : Shape(a) { }
        double area() override{
            Calculate_sides();
            return std::sqrt(p*(p - a)*(p - b)*(p - c));
        }

        double perimeter() override{
            Calculate_sides();
            return a + b + c;
        }

        Point center() override{
            return Point(storage[0].x/3 + storage[1].x/3 + storage[2].x/3,
                         storage[0].y/3 + storage[1].y/3 + storage[2].y/3);
        }
};


class Square: public Shape {
    private:
        double side = 0;
        void Calculate_side(){
            side = distance(storage[0], storage[1]);
        }
    public:
        double area() override{
            Calculate_side();
            return side*side;
        }

        double perimeter() override{
            Calculate_side();
            return side*4;
        }

        Point center() override{
            return Point(storage[0].x/2 + storage[2].x/2, storage[0].y/2 + storage[2].y/2);
        }
};

class Line: public Shape {
    public:
        double area() override{
            return 0.;
        }

        double perimeter() override{
            return 2*distance(storage[0], storage[1]);
        }

        Point center() override{
            return Point(storage[0].x/2 + storage[1].x/2, storage[0].y/2 + storage[1].y/2);
        }
};

int main(){
    Point a(0, 0), b(5, 0), c(0, 5);
    std::vector <Point> points = {a, b, c};
    Triangle abc(points);
    std::cout << abc.area() << " " << abc.perimeter() << " (" << abc.center().x << ", " << abc.center().y << ")" << std::endl;
    return 0;
}