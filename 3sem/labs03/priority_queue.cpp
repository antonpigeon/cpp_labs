#include <iostream>
#include <vector>

template <typename T>
struct Comparator{
    virtual bool operator()(T const &, T const &) = 0;
};

template <typename T>
class PriorityQueue{
    private:
        std::vector<T> vec;
        Comparator<T> &comp;

        int parent(int i){ return (i - 1)/2; }
        int left_child(int i){ return (2 * i + 1); }
        int right_child(int i){ return (2 * i + 2); }

        void ShiftUp(int i){
            while(i > 0 and comp(vec[parent(i)], vec[i])){
                std::swap(vec[parent(i)], vec[i]);
                i = parent(i);
            }
        }

        void ShiftDown(int i){
            if(right_child(i) < vec.size() and comp(vec[i], vec[right_child(i)])){
                std::swap(vec[right_child(i)], vec[i]);
                ShiftDown(right_child(i));
            }
            else if(left_child(i) < vec.size() and comp(vec[i], vec[left_child(i)])){
                std::swap(vec[left_child(i)], vec[i]);
                ShiftDown(left_child(i));
            }
            else return;
        }

    public:
        void push(T element){
            vec.push_back(element);
            ShiftUp(vec.size() - 1);
        }

        T peek(){
            return vec[0];
        }

        void poll(){
            if(is_empty()){
                return;
            }
            vec[0] = vec.back();
            vec.pop_back();
            ShiftDown(0);
        }
        
        bool is_empty(){
            return vec.empty();
        }

    PriorityQueue(): comp(std::less()) { }
    PriorityQueue(Comparator<T> &comp): comp(comp) { }
    PriorityQueue(std::vector<T> arr, Comparator<T> &comp): PriorityQueue(comp){
        for(int i = 0; i < arr.size(); i++){
            push(arr[i]);
        }
    }
};

struct Complex_number{
    float abs, arg;
};


struct ComplexComparator final: Comparator<Complex_number>{
    bool operator()(Complex_number const &lha, Complex_number const &rha) override{
        return (lha.abs < rha.abs) ? true : ((lha.abs > rha.abs) ? false : (lha.arg < rha.arg));
    }
};

int main(){
    float pi = 3.1415;
    ComplexComparator comp;
    std::vector<Complex_number> arr = {{2, pi}, {3, pi/2}, {3, pi}};
    PriorityQueue<Complex_number> queue(arr, comp);
    std::cout << queue.peek().abs << " " << queue.peek().arg <<std::endl;
    queue.poll();
    std::cout << queue.peek().abs << " " << queue.peek().arg <<std::endl;
    queue.poll();
    std::cout << queue.peek().abs << " " << queue.peek().arg <<std::endl;
    queue.poll();
    std::cout << queue.peek().abs << " " << queue.peek().arg <<std::endl;
    //queue.poll();
    //queue.poll();
}