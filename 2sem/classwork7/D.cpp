#include <iostream>
#include <cmath>
using namespace std;

const float eps = 1e-9;

struct street{
    int x1, y1, x2, y2;

    float k(){
        float res = 1.0*(y2 - y1)/(x2 - x1);
        return res;
    }

    float b(){
        float res = -1.0*(x1*y2 + x2*y1)/(x2 - x1);
        return res;
    }

    bool contains_point(float px, float py){
        return ((abs((px-x1)*(y2-y1) - (x2-x1)*(py - y1)) < eps)
        // && (abs(abs(px - x1) + abs(px - x2) - abs(x2 - x1)) < eps)
        )
        ; 
    }

    bool crosses(street &other){
        float crossing_point_x, crossing_point_y;
        crossing_point_x = (other.b() - b())/(k() - other.k());
        crossing_point_y = (k()*crossing_point_x + b());
        cout << crossing_point_x << " " << crossing_point_y << endl;
        return (contains_point(crossing_point_x, crossing_point_y) && other.contains_point(crossing_point_x, crossing_point_y));
    }
};

int main(){
    street s1, s2;
    cin >> s1.x1 >> s1.y1 >> s1.x2 >> s1.y2 >> s2.x1 >> s2.y1 >> s2.x2 >> s2.y2;
    cout << s1.crosses(s2);
    cout << endl;
    return 0;

}