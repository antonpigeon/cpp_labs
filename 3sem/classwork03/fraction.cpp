#include <iostream>
#include <cstdlib>

class Fraction {
    public:
        friend std::ostream& operator<<(std::ostream& out, const Fraction& obj);
        friend std::istream& operator>>(std::istream& is, Fraction& obj);
        
        Fraction& operator+=(const Fraction& other){
            numerator = numerator*other.denominator + denominator * other.numerator;
            denominator *= other.denominator;
            return *this;
        }

        Fraction& operator-=(const Fraction& other){
            numerator = numerator* other.denominator - denominator * other.numerator;
            denominator *= other.denominator;
            return *this;
        }

        Fraction& operator*=(const Fraction& other){
            numerator *= other.denominator;
            denominator *= other.denominator;
            return *this;
        }
    
        friend Fraction operator+(const Fraction& lha, const Fraction& rha);
        friend Fraction operator-(const Fraction& lha, const Fraction& rha);
        friend Fraction operator*(const Fraction& lha, const Fraction& rha);

        Fraction& operator++(){
            numerator += denominator;
            return *this;
        }

        Fraction operator++(int){
            Fraction old = *this;
            ++(*this);
            return old;
        }

        Fraction& operator--(){
            numerator -= denominator;
            return *this;
        }

        Fraction operator--(int){
            Fraction old = *this;
            --(*this);
            return old;
        }

        Fraction(int numerator, int denominator) : numerator(numerator), 
                                                   denominator(denominator){}
        
        Fraction(int numerator) : Fraction(numerator, 1) { }
        Fraction(): numerator(1), denominator(1){} 
    
        Fraction(const Fraction& other) : numerator(other.numerator), 
                                          denominator(other.denominator){}

        void fracSimplify() {
            int a = numerator, b = denominator;
            if (a < b){
                std::swap(a, b);
            }
            while(b != 0){
                a = a % b;
                std::swap(a, b);
            }
            if (a != 0){
                numerator /= a;
                denominator /= a;
            }
        }
        
        double calc() {
            return static_cast<double>(numerator) / static_cast<double>(denominator);
        }

        int getNumerator() {
            return numerator;
        }

        int getDenominator() {
            return denominator;
        }
    
    private:
        int numerator;
        int denominator;
};


std::ostream& operator<<(std::ostream& out, const Fraction& obj){
    out << obj.numerator << "/" << obj.denominator;
    return out;
}

std::istream& operator>>(std::istream& is, Fraction& obj){
    is >> obj.numerator >> obj.denominator;
    return is;
}

Fraction operator+(const Fraction& lha, const Fraction& rha){
    Fraction res = lha;
    res += rha;
    return res;
}

Fraction operator-(const Fraction& lha, const Fraction& rha){
    Fraction res = lha;
    res -= rha;
    return res;
}

Fraction operator*(const Fraction& lha, const Fraction& rha){
    Fraction res = lha;
    res *= rha;
    return res;
}

int main(){
    Fraction a, b;
    std::cin >> a >> b;
    Fraction c = (a + b)*b - a;
    std::cout << a << std::endl;
    a.fracSimplify();
    std::cout << c << std::endl;
    return 0;
}