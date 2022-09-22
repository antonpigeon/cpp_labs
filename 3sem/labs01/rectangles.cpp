#include <iostream>
#include <string>

struct Point{
    unsigned long long x , y ;
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
        Rectangle(Point const &p) : top_right(p), is_dummy(false){}

        Rectangle() : Rectangle({0, 0}){}

        Rectangle operator+(Rectangle const &rha) const{
            if(is_dummy or rha.is_dummy){
                std::cout << "You are adding a dummy rectangle!";
            }
            return Rectangle(Point(top_right.maxx(rha.top_right).x, top_right.maxy(rha.top_right).y));
        }

        Rectangle operator*(Rectangle const &rha){
            if(is_dummy or rha.is_dummy){
                std::cout << "You are multiplying a dummy rectangle!";
            }
            return Rectangle(Point(top_right.minx(rha.top_right).x, top_right.miny(rha.top_right).y));
        }

        Rectangle& operator=(Rectangle const &other){
            top_right = Point(other.top_right.x, other.top_right.y);
            return *this;
        }

        void print() const{
            top_right.print();
        }

        bool is_dummy;
};


int Str_to_int(std::string s){
    int mult = 1, res = 0;
    for(int i = s.length() - 1; i >= 0; i--){
        res += (s[i] - '0')*mult;
        mult *= 10;
    }
    return res;
}


Rectangle Read_rectangle(std::string source, int index){ // index - место, на котором находится скобка
    if (index < 0 or index >= source.length()){
        std::cout << "ALARM! Reading from outside of the source. How did this happen?\n";
        return Rectangle();    
    }

    if (source[index] != '('){
        std::cout << "You fool! There is no rectangle starting at index " << index << "!" << std::endl;
    }

    int j = index + 1;
    std::string x_str = "";

    while(source[j] != ',' and source[j] != ' '){ // reading x
        x_str += source[j];
        j++;
    }
    
    int x = Str_to_int(x_str);
    while(source[j] == ' ' or source[j] == ','){
        j++;
    }

    std::string y_str = "";
    
    while(source[j] != ' ' and source[j] != ')'){ // reading y
        y_str += source[j];
        j++;
    }
    
    int y = Str_to_int(y_str);
    return Rectangle(Point(x, y));
}


Rectangle rectangles[50];
int operators[50];

int main(){
    std::string expr;
    std::getline(std::cin, expr);
    int r = 0, op = 0;
    for(int i = 0; i < expr.length(); i++){
        if (expr[i] == ' '){
            continue;
        }
        if (expr[i] == '('){
            rectangles[r] = Read_rectangle(expr, i);
            r++;        
        }
        if(expr[i] == '+'){
            operators[op] = 1;
            op++;
        }
        if(expr[i] == '*'){
            operators[op] = 2;
            op++;
        }
    }

    if(r != op + 1){
        std::cout << "Wrong ratio of operands and operators?" << std::endl;
    }

    for(int i = 0; i < op; i++){
        if(operators[i] == 2){
            rectangles[i + 1] = rectangles[i] * rectangles[i + 1];
            rectangles[i].is_dummy = true;
        }
    }

    int curr_rect = 0;
    bool added_at_least_once = false;
    int last_result_of_addition_index = 0;

    for(int i = 0; i < op; i++){
        while(rectangles[curr_rect].is_dummy){
            curr_rect++;
        }
        if(operators[i] == 1){
            added_at_least_once= true;
            int next = curr_rect + 1;
            while(rectangles[next].is_dummy){
                next++;
            }
            rectangles[next] = rectangles[curr_rect] + rectangles[next];
            rectangles[curr_rect].is_dummy = true;
            last_result_of_addition_index = next;
        }
        curr_rect++;
    }

    if(added_at_least_once){
        rectangles[last_result_of_addition_index].print();
    }
    else{
        rectangles[op].print();
    }
    return 0;
}