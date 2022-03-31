#include <iostream>
#include <assert.h>
using namespace std;

struct Node {
    int field;
    Node* next;
    Node* prev;
};

struct List {
    Node* head;
    Node* tail;

    List(int value) {
        head = new Node;
        head->field = value;
        head->next = nullptr;
        head->prev = nullptr;
        tail = head;
    }

    void append(int value){
        Node* tmp = new Node;
        tmp->field = value;
        tmp->next = nullptr;
        tmp->prev = tail;
        tail->next = tmp;
        tail = tmp;
    }

    void add(int value, int index){
        Node* current = head;
        int i = 0;
        while(i < index){
            current = current->next;
            i++;
        }
        if(current == tail){
            append(value);
        }
        else{
            Node* tmp = new Node;
            tmp->field = value;
            tmp->next = current->next;
            tmp->next->prev = tmp;
            current->next = tmp;
            tmp->prev = current;
        }
    }

    void pop(){
        Node* tmp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete tmp;
    }

    void print_list(){
        Node* current = head;
        while(current!=nullptr){
            cout << current->field << " ";
            current = current->next;
        }
    }

    void delete_list(){
        Node* current = head->next;
        while(current!=nullptr){
            delete current->prev;
            current = current->next;

        }
        delete tail;
    }
    Node* find_by_value(int value);
    Node* find_by_index(int index);
    Node* delete_by_value(int value);  // ->return pointer to node, else -- nullptr
    Node* delete_by_index(int index);  // ->return pointer to node, else -- nullptr
    int size();
};

int main(){
    List lst = List(3);
    lst.append(2);
    lst.append(5);
    lst.pop();
    lst.print_list();
    lst.pop();
    lst.print_list();
    lst.pop();
    lst.print_list();
    lst.delete_list();
    return 0;
}
