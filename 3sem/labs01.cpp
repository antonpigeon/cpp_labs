#include <iostream>

struct Point{
    unsigned long long const x , y ;
    Point (unsigned long long x , unsigned long long y ) : x ( x ) , y ( y ) {}
    
    Point minx (Point const &rha ) const {
        return Point ( rha.x < x ? rha.x : x , y ) ;
    }

    Point miny ( Point const &rha ) const {
        return Point ( x , rha.y < y ? rha.y : y ) ;
    }

    Point maxx ( Point const &rha ) const {
        return Point ( rha.x > x ? rha.x : x , y ) ;
    }  

    Point maxy ( Point const &rha ) const {
        return Point ( x , rha.y > y ? rha.y : y ) ;
    }   

    void print ( ) const {
        std::cout << "(" << x << ", " << y << ")" ;
    }
};


class Rectangle{
    private:
        Point top_right;
    
    public:
        Rectangle(Point const &p) : top_right(p){}

        Rectangle() : Rectangle({0, 0}){}

        Rectangle operator+(Rectangle const &rha) const{
            return Rectangle(Point(top_right.maxx(rha.top_right).x, top_right.maxy(rha.top_right).y));
        }

        Rectangle operator*(Rectangle const &rha){
            return Rectangle(Point(top_right.minx(rha.top_right).x, top_right.miny(rha.top_right).y));
        }

        void print() const{
            top_right.print();
        }
};


int main(){
    Point a = {7, 4}, b = {5, 6};
    Rectangle A(a), B(b);
    A.print();
    std::cout << std::endl;
    B.print();
    std::cout << std::endl;
    Rectangle res = B * A;
    res.print();
    std::cout << std::endl;
    return 0;
}