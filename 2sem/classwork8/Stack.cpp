#include <iostream>
using namespace std;

struct Node{
    int field;
    Node* next;
};

struct Stack {
    Node *top;

    Stack(){
        top = nullptr;
    }
    Stack(int field){
        top = new Node;
        top->field = field;
        top->next = nullptr;
    }

    void push(int value){
        Node* old_top = top;
        top = new Node;
        top->next = old_top;
        top->field = value;
    }

    void pop(){
        Node* to_delete = top;
        top = top->next;
        delete to_delete;
    }

    bool is_empty(){
        return (top == nullptr);
    }

    int Top(){
        return top->field;
    }
};

int main(){
    Stack stack = Stack(2);
    cout << stack.is_empty() << endl;
    cout << stack.Top() << endl;
    stack.pop();
    cout << stack.is_empty() << endl;
    for(int i = 0; i < 5; i++){
        stack.push(i + 3);
    }
    cout << stack.is_empty() << endl;
    for(int i = 0; i < 5; i++){
        cout << stack.Top() << " ";
        stack.pop();
    }
    cout << endl << stack.is_empty() << endl;
    return 0;
}
