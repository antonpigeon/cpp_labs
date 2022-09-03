#include <iostream>
using namespace std;

struct Node {
    Node* parent;
    Node* left;
    Node* right;
    int value;
};

void pre_order(Node* n) {
    if(n == nullptr){
        return;
    }
    std::cout << n->value << ' ';
    pre_order(n->left);
    pre_order(n->right);
}

void in_order(Node* n){
    if(n == nullptr){
        return;
    }
    in_order(n->left);
    std::cout << n->value << ' ';
    in_order(n->right);
}

void post_order(Node* n){
    if(n == nullptr){
        return;
    }
    post_order(n->left);
    post_order(n->right);
    std::cout << n->value << ' ';
}

Node* find(Node* n, int target){
    Node* curr = n;
    while(true){
        if(curr == nullptr){
            return nullptr;
        }
        if(target == curr->value){
            return curr;
        }
        if(target < curr->value){
            curr = curr->left;
        }
        else if (target > curr->value){
            curr = curr->right;
        }
    }
}

void add(Node* root, int value){
    Node* pre = nullptr;
    Node* current = root;
    while (current != nullptr){
        pre = current;
        if (pre->value > value){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }
    // Проработать случай с pre == nullptr
    Node* tmp = new Node;
    tmp->value = value;
    tmp->parent = pre;
    tmp->left = nullptr;
    tmp->right = nullptr;
    if (pre->value > value){
        pre->left = tmp;
    }
    else{
        pre->right = tmp;
    }
}

void remove(Node* root, int value){
    Node* current = root;
    while(current != nullptr){
        if(current->value == value){

        }
    }
}

Node* min(Node* root){
    Node* curr = root;
    if(curr == nullptr){
        return nullptr;
    }
    while(curr->left != nullptr){
        curr = curr->left;
    }
    return curr;
}

Node* max(Node* root){
    Node* curr = root;
    if(curr == nullptr){
        return nullptr;
    }
    while(curr->right != nullptr){
        curr = curr->right;
    }
    return curr;
}

int main(){
    Node* root = new Node;
    root->parent = nullptr;
    root->value = 3;
    root->left = nullptr;
    root->right= nullptr;
    add(root, 2);
    add(root, 100);
    add(root, 5);
    add(root, 4);
    in_order(root);
    cout << endl;
    pre_order(root);
    cout << endl;
    post_order(root);
    cout << endl;
    cout << root->value << endl << root->left->value << " "  << root->right->value << endl;
    cout << root->right->left->left->value << endl;
    cout << (find(root, 8) == nullptr) << endl;
    cout << (find(root, 100) == nullptr) << endl;
    return 0;
}