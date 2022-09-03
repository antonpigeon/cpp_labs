#include <iostream>
using namespace std;

struct Node {
  int field;
  Node* next;
};


struct List {
    Node* head;

    List(int value){
        head = new Node;
        head->field = value;
        head->next = nullptr;
    }

    void append(int value){
        Node* current = head;
        while(current->next != nullptr){
            current = current->next;
        }
        Node* tmp = new Node;
        tmp->field = value;
        tmp->next = nullptr;
        current->next = tmp;
    }

    void add(int value, int index){
        int i = 0;
        Node* current = head;
        Node* prev = nullptr;
        while (current != nullptr) {
            if (i == index) {
                break;
            }
            prev = current;
            current = current->next;
            i++;
        }
        Node* tmp = new Node;
        tmp->field = value;
        prev->next = tmp;
        tmp->next = current;
    }

    void pop(){
        Node* current = head;
        while(current->next->next != nullptr){
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }

    void print_list(){
        Node* current = head;
        while(current != nullptr){
            cout << current->field << " ";
            current = current->next;
        }
        cout << endl;
    }

    void delete_list(){
        Node* current = head;
        while(current->next != nullptr){
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    Node* find_by_value(int value){
        Node* current = head;
        while(current != nullptr){
            cout << current->field << " ";
            if(current->field == value){
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    Node* find_by_index(int index){
        Node* current = head;
        int i = 0;
        while(current != nullptr && i != index){
            current = current->next;
            i++;
        }
        return current;
    }

    Node* delete_by_value(int value){
        Node* current = head, *prev = nullptr;
        while(current != nullptr){
            if(current->field == value){
                if(prev == nullptr){
                    head = head->next;
                }
                else{
                    prev->next = current->next;
                }
                current->next = nullptr;
                return current;
            }
            prev = current;
            if(current->next == nullptr){
            }
            current = current->next;
            if(current == nullptr){
            }
        }
        return nullptr;
    }

    Node* delete_by_index(int index){
        if(index == 0){
            Node* ans = head;
            head = head->next;
            ans->next = nullptr;
            return ans;
        }
        Node* current = head, *prev = nullptr;
        int i = 0;
        while(current != nullptr){
            if (i == index){
                if(prev == nullptr){
                    head = head->next;
                }
                else{
                    prev->next = current->next;
                }
                current->next = nullptr;
                return current;
            }
            prev = current;
            current = current->next;
            i++;
        }
        return nullptr;
    }
};

int main(){
    List lst = List(2);
    lst.append(3);
    lst.append(7);
    lst.append(5);
    lst.print_list();
    cout << endl;
    cout << lst.find_by_value(7)->next << endl;
    lst.delete_by_value(5);
    lst.print_list();
    cout << endl;
    lst.delete_by_index(0);
    lst.print_list();
    cout << endl;
    cout << lst.find_by_value(7) << endl;
    lst.print_list();
    cout << endl;
    lst.delete_list();
    return 0;
}