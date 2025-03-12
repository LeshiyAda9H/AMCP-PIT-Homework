#include <iostream>
#include <fstream>

struct Node{
    int number;
    int lvl;
    Node* parent;
    Node* left;
    Node* right;

    Node(int num) : number(num), lvl(1), parent(nullptr), left(nullptr), right(nullptr)  {}
    
    ~Node(){
        delete left;
        delete right;
        left = right = nullptr;
    }

    Node* minimum(){
        
        Node* cur = this;
        
        while (cur->left != nullptr) { 
            cur = cur->left;
        }
        
        return cur;
    }
};

class AAtree{
private:
    Node* root;
public:

    AAtree() : root(nullptr) {}

    ~AAtree() { delete root; }


    void skew(Node* cur) {
        if (cur->left != nullptr && cur->left->lvl >= cur->lvl)
        {
            if (cur->parent == nullptr){

                cur->parent = cur->left;
                cur->left = cur->left->right;
                
                if (cur->parent->right != nullptr) { 
                    cur->parent->right->parent = cur;
                }
                
                cur->parent->parent = nullptr;
                cur->parent->right = cur;
                root = cur->parent;

            }
            else if (cur->parent->left == cur){
                cur->parent->left = cur->left;
               
                if (cur->left->right != nullptr) { 
                    cur->left->right->parent = cur;
                }
                
                cur->left = cur->left->right;
                cur->parent->left->right = cur;
                cur->parent->left->parent = cur->parent;
                cur->parent = cur->parent->left;
            }
            else{

                cur->parent->right = cur->left;
                
                if (cur->left->right != nullptr) { 
                    cur->left->right->parent = cur; 
                }
                
                cur->left = cur->left->right;
                cur->parent->right->right = cur;
                cur->parent->right->parent = cur->parent;
                cur->parent = cur->parent->right;
            }
        }

    }

    void split(Node* cur) {
        if (cur->right != nullptr && cur->right->right != nullptr && cur->lvl <= cur->right->right->lvl){
            
            if (cur->parent == nullptr){

                cur->parent = cur->right;
                
                if (cur->right->left != nullptr) { 
                    cur->right->left->parent = cur;
                }
                
                cur->right = cur->right->left;
                cur->parent->left = cur;
                cur->parent->parent = nullptr;
                root = cur->parent;
            }
            else if (cur->parent->left == cur){

                cur->parent->left = cur->right;
                
                if (cur->right->left != nullptr){ 
                    cur->right->left->parent = cur;
                }
               
                cur->right = cur->right->left;
                cur->parent->left->left = cur;
                cur->parent->left->parent = cur->parent;
                cur->parent = cur->parent->left;
            }
            else{

                cur->parent->right = cur->right;
                
                if (cur->right->left != nullptr) { 
                    cur->right->left->parent = cur; 
                }
                
                cur->right = cur->right->left;
                cur->parent->right->left = cur;
                cur->parent->right->parent = cur->parent;
                cur->parent = cur->parent->right;
            }
            
            ++cur->parent->lvl;
        }

    }

    void insert(int num){

        if (root == nullptr){
            
            root = new Node(num);
            
            return;
        }

        Node* cur = root;
        Node* p = nullptr;
        bool to_left = false;

        do {
            p = cur;
            
            if (num < cur->number) {
                cur = cur->left;
                to_left = true;
            }
            else{
                cur = cur->right;
                to_left = false;
            }

        } while (cur != nullptr);

        cur = new Node(num);
        cur->parent = p;

        if (to_left) { 
            p->left = cur;
        }
        else { 
            p->right = cur;
        }

        do{
            cur = cur->parent;
            skew(cur);
            split(cur);

        } while (cur != root);
    }

    Node* find(int number) {
        
        Node* cur = root;
        
        while (cur) {
            
            if (number == cur->number) {
                break;
            }
            
            if (number < cur->number) {
                cur = cur->left;
            }
            else {
                cur = cur->right;
            }
        }

        return cur;

    }

    void erase(int number)
    {
        Node* toDelete = find(number);
        
        if (toDelete == nullptr) { 
            return;
        }
        
        Node* alt = nullptr;
        Node* cur = nullptr;

        if (toDelete->right == nullptr){
            
            alt = toDelete->left;
            cur = toDelete->parent;
        }
        else if (toDelete->left == nullptr){
            
            alt = toDelete->right;
            cur = toDelete->parent;
        }
        else{
            
            alt = toDelete->right->minimum();

            if (alt->parent == toDelete){
                cur = alt;
            }
            else{
                cur = alt->parent;
                alt->parent->left = alt->right;

                if (alt->right) {
                    alt->right->parent = alt->parent;
                }

                alt->right = toDelete->right;
                toDelete->right->parent = alt;
            }

            alt->left = toDelete->left;
            toDelete->left->parent = alt;
        }

        if (toDelete->parent != nullptr) { 
            
            if (toDelete->parent->left != toDelete) {
                toDelete->parent->right = alt;
            }
            else {
                toDelete->parent->left = alt;
            }
        }
        else{
            root = alt;
        }

        if (alt != nullptr){
            alt->parent = toDelete->parent;
            alt->lvl = toDelete->lvl;
        }

        toDelete->left = nullptr;
        toDelete->right = nullptr;
        
        delete toDelete;

        while (cur != nullptr){
            
            int lvl = (cur->right && cur->left) ? std::min(cur->right->lvl, cur->left->lvl) : 0;

            if (cur->lvl - lvl >= 2) { 
                --cur->lvl;
            }
            
            if (cur->right != nullptr && cur->lvl < cur->right->lvl) { 
                cur->right->lvl = cur->lvl;
            }

            skew(cur);
            
            if (cur->right != nullptr) { 
                skew(cur->right);
            }
            
            if (cur->right != nullptr && cur->right->right != nullptr) {
                skew(cur->right->right);
            }
            
            split(cur);
            
            if (cur->parent != nullptr && cur->parent->right != nullptr) {
                split(cur->parent->right);
            }

            cur = cur->parent;
        }
    }

    int balance() const { 
        return ((root != nullptr) ? root->lvl : 0); 
    }

};




int main(int argc, const char* argv[]){

    std::ifstream inFile(argv[1]);
    std::ofstream outFile(argv[2]);

    int n;
    inFile >> n;

    AAtree aatree;
    for (int i = 0; i < n; ++i)
    {
        char command;
        inFile >> command;

        int number;
        inFile >> number;

        switch (command){
        
        case '?':
            outFile << ((aatree.find(number) != nullptr) ? "true" : "false") << '\n';
            break;

        case '+':
            aatree.insert(number);
            outFile << aatree.balance() << '\n';
            break;

        case '-':
            aatree.erase(number);
            outFile << aatree.balance() << '\n';
            break;

        }
    }

    inFile.close();
    outFile.close();

    return 0;


}
