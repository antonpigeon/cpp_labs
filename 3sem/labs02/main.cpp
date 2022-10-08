#include <random>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using State = int;


class GeneralState{
    public:
        virtual bool contains(int s) = 0;
};

class DescreteState : public GeneralState{
    private:
        State s0 = 0;
    
    public:
        DescreteState(State s0) : s0(s0) { }
        DescreteState() : DescreteState(0) { }
        
        bool contains(State s) override {
            return s == s0;
        }
};

class SegmentState : public GeneralState{
    private:
        State beg, end;
    
    public:
        SegmentState(State beg, State end) : beg(beg), end(end) { }
        SegmentState() : SegmentState(0, -1) { }
        bool contains(State s) override {
            return s >= beg and s < end;
        }
};

class UnionState : public GeneralState{
    private:
        GeneralState &s1, &s2;
    public:
        UnionState(GeneralState &s1, GeneralState &s2) : s1(s1), s2(s2) { }
        bool contains(State s) override{
            return s1.contains(s) or s2.contains(s);
        }
};

class IntersectionState : public GeneralState{
    private:
        GeneralState &s1, &s2;
    public:
        IntersectionState(GeneralState &s1, GeneralState &s2) : s1(s1), s2(s2) { }
        bool contains(State s) override{
            return s1.contains(s) and s2.contains(s);
        }
};

class InvertedState : public GeneralState{
    private:
        GeneralState &s1;
    public:
        InvertedState(GeneralState &s1) : s1(s1) { }
        bool contains(State s) override{
            return !s1.contains(s);
        }
};


class ProbabilityTest{
    private:
        State const E_min, E_max;

    public:
        ProbabilityTest(State E_min, State E_max) : E_min(E_min), E_max(E_max) { }
        float test(GeneralState &system, unsigned test_count, unsigned seed) const {
            std::default_random_engine reng(seed);
            std::uniform_int_distribution<int> distr (E_min, E_max);

            unsigned good = 0;
            for (unsigned cnt = 0; cnt < test_count; cnt++){
                std::cout << cnt << " ";
                if(system.contains(distr(reng))){
                    good++;
                }
            }
            return static_cast<float> (good) / static_cast<float> (test_count);
        }
};

int main(){
    std::fstream f1("data.txt", std::ios::out);
    ProbabilityTest test(-1000, 1000);
    SegmentState seg(-501, 501);
    std::cout << 1 << " ";
    std::vector<UnionState> unions;
    std::cout << 2 << " ";
    DescreteState a(-1000), b(998);
    unions.push_back(UnionState(a, b));
    std::cout << 3 << " ";
    for(int i = 2; i < 1000; i++){
        DescreteState c((i - 500)*2);
        unions.push_back(UnionState(unions[i - 1], c)); 
    }
    /*unsigned tests_for_each = 10, seed = 1;
    unsigned max_test_count = 2000;
    for (unsigned test_count = 1; test_count <= max_test_count; test_count++){
        float sum = 0;
        for (unsigned i = 0; i < tests_for_each; i++){
            sum += test.test(seg, test_count, seed);
            seed++;
        }
        sum /= tests_for_each;
        f1 << sum << std::endl;
    }*/

    std::fstream f2("data2.txt", std::ios::out);
    unsigned tests_for_each = 50, seed = 1;
    unsigned max_test_count = 2000;
    std::cout << 4 << " ";
    for (unsigned test_count = 1; test_count <= max_test_count; test_count++){
        float sum = 0.;
        for (unsigned i = 0; i < tests_for_each; i++){
            std::cout << i << " ";
            sum += test.test(unions.back(), test_count, seed);
            std::cout << i << " ";
            seed++;
        }
        sum /= tests_for_each;
        f2 << sum << std::endl;
    }
    f1.close();
    f2.close();
    std::cout << "Program finished" << std::endl;
    return 0;
}