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
        if(tail == nullptr){
            return;
        }
        Node* tmp = tail;
        tail = tail->prev;
        delete tmp;
        if(tail == nullptr){
            head = nullptr;
            return;
        }
        tail->next = nullptr;
    }

    void print_list(){
        Node* current = head;
        while(current!=nullptr){
            cout << current->field << " ";
            current = current->next;
        }
        cout << endl;
    }

    void delete_list(){
        Node* current = head;
        while(current!=nullptr && current->next != nullptr){
            current = current->next;
            delete current->prev;
        }
        delete tail;
    }

    Node* find_by_value(int value){
        Node* current = head;
        while(current != nullptr){
            if (current->field == value){
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    Node* find_by_index(int index){
        int i = 0;
        Node* current = head;
        while(current != nullptr){
            if(i == index){
                return current;
            }
            current = current->next;
            i++;
        }
        return nullptr;
    }

    Node* delete_by_value(int value){
        Node* current = head;
        while(current != nullptr){
            if (current->field == value){
                if(!(current->prev == nullptr)){
                    current->prev->next = current->next;                    
                }
                else{
                    
                }
                if(!(current->next == nullptr)){
                    current->next->prev = current->prev;
                }
                current->next->prev = current->prev;
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    Node* delete_by_index(int index);  // ->return pointer to node, else -- nullptr
    int size();
};

int main(){
    List lst = List(3);
    lst.append(2);
    lst.append(5);
    lst.print_list();
    lst.pop();
    lst.print_list();
    lst.pop();
    lst.print_list();
    lst.pop();
    lst.print_list();
    lst.delete_list();
    return 0;
}
