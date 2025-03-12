#include <iostream>
#include <fstream>
#include <random>
#include <cmath>



class HashHashTable {
private:
    class HashTable {
    private:
        struct Node
        {
            int key;
            int amount;
            bool del;

            Node() : key(0), amount(0), del(false) {}
        };

        int a;
        int b;
        int size;
        Node* table;
        int capacity;

        void toChangeCapacity() {
            if (capacity == 0 || workload < ((double)size) / ((double)capacity)){

                int newCapacity = (capacity == 0) ? 1: capacity * 2;

                Node* tmp = new Node[newCapacity];

                for (int index = 0; index < capacity; ++index){

                    int newIndx = hash(a, b, newCapacity, table[index].key);

                    while (0 < table[newIndx].amount){
                        newIndx = (newIndx + 1) % newCapacity;
                    }

                    tmp[newIndx] = table[index];
                }
                delete[] table;

                table = tmp;
                capacity = newCapacity;
            }
        }

    public:
        HashTable() : size(0), capacity(0), table(nullptr), a(rand() % (p - 1) + 1), b(rand() % p) {}

        HashTable(int capacity) : size(0), capacity(capacity), a(rand() % (p - 1) + 1), b(rand() % p) {
            table = new Node[capacity];
        }

        void insert(int X) {

            toChangeCapacity();

            int hashIndx = hash(a, b, capacity, X);
            int indx_freePlace = hashIndx;

            while ((table[indx_freePlace].key != X) && (0 < table[indx_freePlace].amount )){
                indx_freePlace = (indx_freePlace + 1) % capacity;
            }

            if (table[indx_freePlace].key != X){
                ++size;
                table[indx_freePlace].key = X;
                table[indx_freePlace].del = false;
            }

            ++table[indx_freePlace].amount;
        }
        void erase(int X) {

            int index = hash(a, b, capacity, X);
            
            while (table[index].del || (table[index].amount > 0 && table[index].key != X)){
                index = (index + 1) % capacity;
            }

            if ((table[index].del) || (table[index].key != X)) {
                throw "bruh"; 
            }

            --table[index].amount;
            
            if (table[index].amount == 0){
                --size;
                table[index].del = true;
            }

        }
        bool find(int X) const {
            
            int index = hash(a, b, capacity, X);
            int size2 = size;
           
            while (( (0 < table[index].amount && table[index].key != X) || table[index].del) && size2 > 0){
                index = (index + 1) % capacity;
                --size2;
            }

            return table[index].key == X && !table[index].del;
        }

        ~HashTable() {
            delete[] table;
        }
    };

    static const int p;
    static const double workload;

    int a;
    int b;
    int capacity;
    HashTable** table;



    static int hash(int a, int b, int m, int k) {
        return abs(((a * k + b) % p) % m);
    }

public:

    HashHashTable() : capacity(0), table(nullptr), a(rand() % (p - 1) + 1), b(rand() % p) {}

    HashHashTable(int capacity) : capacity(capacity), a(rand() % (p - 1) + 1), b(rand() % p) {
        table = new HashTable * [capacity] { nullptr };
    }

    void insert(int X) {
        int index_hash_table = hash(a, b, capacity, X);
        if (table[index_hash_table] == nullptr)
        {
            table[index_hash_table] = new HashTable;
        }
        table[index_hash_table]->insert(X);
    }
    
    void erase(int X) {
        int index_hash_table = hash(a, b, capacity, X);
        
        if (table[index_hash_table] == nullptr) {
            return;
        }

        table[index_hash_table]->erase(X);
    }
    
    bool find(int X) const {
        int indxHashTable = hash(a, b, capacity, X);
        return ((table[indxHashTable] != nullptr) && table[indxHashTable]->find(X));
    }

    ~HashHashTable() {
        for (int index = 0; index < capacity; ++index){
            delete table[index];
        }
        delete[] table;
    }
};

const int HashHashTable::p = 2'147'483'647;
const double HashHashTable::workload = 0.8;

int main(int argc, const char* argv[]) {

    std::ifstream inFile(argv[1]);
    std::ofstream outFile(argv[2]);

    int n;
    inFile >> n;

    HashHashTable table(100000);

    for (int i = 0; i < n; ++i)
    {
        char command;
        inFile >> command;

        int number;
        inFile >> number;

        switch (command) {

        case '?':
            outFile << ((table.find(number)) ? "true" : "false") << '\n';
            break;

        case '+':
            table.insert(number);
            break;
        
        case '-':
            table.erase(number);
            break;

        }
    }

    inFile.close();
    outFile.close();

    return 0;


}
