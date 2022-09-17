#include <iostream>
#include <cstdlib>

class Fraction {
    public:
        Fraction(int numerator, int denominator) : numerator(numerator), 
                                                   denominator(denominator){}
        
        Fraction(int numerator) : Fraction(numerator, 1) { }
        Fraction() = delete; 
    
        Fraction(const Fraction& other) : numerator(other.numerator), 
                                          denominator(other.denominator){}
    
        void printFraction() const {
            std::cout << numerator << " / " << denominator << std::endl;
        }

        void fracReverse(){
            int tmp = numerator;
            numerator = denominator;
            denominator = tmp;
        }

        void fracSimplify() {
            for(int i = std::min(numerator, denominator)/2 + 1; i >= 2; i--){
                if(numerator % i == 0 and denominator % i == 0){
                    numerator /= i;
                    denominator /= i;
                    break;
                }
            }
        }

        void multByNumber(int value){
            numerator *= value;
        }
        
        void multByFrac(const Fraction& other){
            numerator *= other.numerator;
            denominator *= other.denominator;
        }

        Fraction multByFracReturn(const Fraction& other) const{
            return Fraction(numerator*other.numerator, denominator*other.denominator);
        }
        
        void sumFrac(const Fraction& other){
            numerator = numerator*other.denominator + denominator*other.numerator;
            denominator *= other.denominator;
        }

        Fraction sumFracReturn(const Fraction& other) const{
            return Fraction(numerator*other.denominator + denominator*other.numerator, denominator*other.denominator);
        }

        void diffFrac(const Fraction& other){
            numerator = numerator*other.denominator - denominator*other.numerator;
            denominator *= other.denominator;
        }
        
        Fraction diffFracReturn(const Fraction& other) const{
            return Fraction(numerator*other.denominator - denominator*other.numerator, denominator*other.denominator);
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