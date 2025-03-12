#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <cstring>


class HashHashTable {

private:

    class HashTable {
    private:
        struct Node{
            std::pair<int, int> key_indx;
            int amount;
            bool del;

            Node() : key_indx(std::make_pair(0, -1)), amount(0), del(false) {}
        };

        int a;
        int b;
        int size;
        Node* table;
        int capacity;

        void toChangeCapacity() {
            if (capacity == 0 || workload < ((double)size) / ((double)capacity)) {

                int newCapacity = (capacity == 0) ? 1 : capacity * 2;

                Node* tmp = new Node[newCapacity];

                for (int index = 0; index < capacity; ++index) {

                    if (!table[index].del) {
                        int newIndx = hash(a, b, newCapacity, table[index].key_indx.first);

                        while (0 < table[newIndx].amount) {
                            newIndx = (newIndx + 1) % newCapacity;
                        }

                        tmp[newIndx] = table[index];
                    }

                }
                delete[] table;

                table = tmp;
                capacity = newCapacity;
            }
        }
        int findHashTable(int key) const{

            if (size == 0) { 
                return -1;
            }

            int indx = hash(a, b, capacity, key);
            int counter = size;

            while (0 < counter && (table[indx].del || 0 < table[indx].amount && table[indx].key_indx.first != key))
            {
                indx = (indx + 1) % capacity;
                --counter;
            }

            return table[indx].del || table[indx].key_indx.first != key ? -1 : indx;
        }
        

    public:
        HashTable() : size(0), capacity(0), table(nullptr), a(rand() % (p - 1) + 1), b(rand() % p) {}
        

        void insert(const std::pair<int, int>& _key_indx) {

            toChangeCapacity();

            int hashIndx = hash(a, b, capacity, _key_indx.first);
            
            while (0 < table[hashIndx].amount && table[hashIndx].key_indx.first != _key_indx.first)
            {
                hashIndx = (hashIndx + 1) % capacity;
            }

            if (table[hashIndx].key_indx.first != _key_indx.first || table[hashIndx].del)
            {
                ++size;
                table[hashIndx].key_indx = _key_indx;
                table[hashIndx].del = false;
            }
            ++table[hashIndx].amount;
        }
        void erase(int key) {

            int hashIndx = findHashTable(key);

            if (hashIndx < 0) { 
                return; 
            }

            --table[hashIndx].amount;

            if (table[hashIndx].amount == 0){
                --size;
                table[hashIndx].del = true;
            }

        }
        int find(int key) const {

            int index = findHashTable(key);
            return index < 0 ? index : table[index].key_indx.second;

        }

        void toChangeIndx(int key, int newIndx)
        {
            int indx = findHashTable(key);

            if (indx < 0) { 
                insert(std::make_pair(key, newIndx));
            }
            else {
                table[indx].key_indx.second = newIndx;
                table[indx].del = false;
            }
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

    HashHashTable(int capacity) : capacity(capacity), a(rand() % (p - 1) + 1), b(rand() % p) {
        table = new HashTable * [capacity] { nullptr };
    }

    void insert(const std::pair<int32_t, int32_t>& _key_index) {

        int hashIndx = hash(a, b, capacity, _key_index.first);
        
        if (table[hashIndx] == nullptr){
            table[hashIndx] = new HashTable;
        }

        table[hashIndx]->insert(_key_index);
    }

    void erase(int key) {
        int hashIndx = hash(a, b, capacity, key);

        if (table[hashIndx] == nullptr) {
            throw "Bruh";
        }

        table[hashIndx]->erase(key);
    }

    int find(int key) const
    {
        int index = hash(a, b, capacity, key);
        return table[index] != nullptr ? table[index]->find(key) : -1;
    }

    void toChangeIndx(int key, int new_index)
    {
        int hashIndx = hash(a, b, capacity, key);

        if (table[hashIndx] == nullptr){
            table[hashIndx] = new HashTable;
        }

        table[hashIndx]->toChangeIndx(key, new_index);
    }

    ~HashHashTable() {
        for (int index = 0; index < capacity; ++index) {
            delete table[index];
        }
        delete[] table;
    }
};

const int HashHashTable::p = 2'147'483'647;
const double HashHashTable::workload = 0.8;



class Heap {

    std::pair<int, int>* heap;

    int size;
    int capacity;

    HashHashTable indx;

    void toChangeCapacity() {

        if (size == capacity) {

            capacity = (capacity == 0) ? 1 : capacity * 2;

            std::pair<int, int>* tmp = new std::pair<int, int>[capacity];

            for (int32_t index = 0; index < size; ++index) {
                tmp[index] = heap[index];
            }

            delete[] heap;
            heap = tmp;
        }
    }

    void Up(int index) {

        int indxParent = (index - 1) / 2;

        while (0 < index && heap[index].first < heap[indxParent].first) {

            indx.toChangeIndx(heap[indxParent].first, index);

            std::swap(heap[index], heap[indxParent]);

            index = indxParent;

            indxParent = (index - 1) / 2;
        }
        indx.toChangeIndx(heap[index].first, index);
    }

    void Down(int index) {

        while ( size > index * 2 + 1)
        {
            int indxMinChild = ((heap[index * 2 + 1].first < heap[index * 2 + 2].first) || (size == index * 2 + 2)) ? index * 2 + 1 : index * 2 + 2;

            if (heap[indxMinChild].first >= heap[index].first) {
                break;
            }

            indx.toChangeIndx(heap[indxMinChild].first, index);

            std::swap(heap[index], heap[indxMinChild]);

            index = indxMinChild;

        }
    }

public:

    Heap() : heap(nullptr), size(0), capacity(0), indx(100000) {}

    int toSize() const {
        return size;
    }

    int extractMin() {

        int result = heap[0].first;

        indx.erase(heap[0].first);
        --heap[0].second;

        if (heap[0].second == 0) {

            --size;
            heap[0] = heap[size];
            Down(0);
        }

        return result;
    }

    void insert(int num) {
        int index = indx.find(num);

        if (index < 0) {

            toChangeCapacity();

            heap[size].first = num;

            heap[size].second = 1;

            Up(size++);
        }
        else {
            ++heap[index].second;
        }
    }

    void decrease_key(int num, int newNum) {

        int indxFound = indx.find(num);

        heap[indxFound].first = newNum;

        Up(indxFound);
    }

    ~Heap() {
        delete[] heap;
    }

};

class vector
{
    std::pair<int, int>* mas;
    int size;
    int capacity;

public:

    vector() : size(0), capacity(0), mas(nullptr) {}

    vector(int capacity) : size(0), capacity(capacity) {
        mas = new std::pair<int, int>[capacity];
    }

    void toPush(const std::pair<int, int>& num) {

        if (size == capacity) {

            capacity = (capacity == 0) ? 1 : capacity * 2;

            std::pair<int, int>* tmp = new std::pair<int, int>[capacity];

            for (int index = 0; index < size; ++index) {
                tmp[index] = mas[index];
            }

            delete[] mas;
            mas = tmp;
        }

        mas[size++] = num;
    }

    int binSearch(int key) {

        int left = 0;
        int right = size - 1;

        while (left < right) {

            int middle = (right - left) / 2 + left;

            if (mas[middle].first < key) {
                left = middle + 1;
            }
            else {
                right = middle;
            }
        }

        if (mas[left].first != key) {
            throw "bruh";
        }

        return left;
    }

    std::pair<int, int>& operator[](int indx) {

        if (indx < 0 || size <= indx) {
            throw "Bruh";
        }

        return mas[indx];
    }

    ~vector() {
        delete[] mas;
    }
};


int main(int argc, const char* argv[]){
    
    std::ifstream inFile(argv[1]);
    
    std::ofstream outFile(argv[2]);
    
    char command[16];
    vector pushing;
    Heap heap;
    int counter = 0;

    while (!inFile.eof())
    {
        inFile >> command;
        
        ++counter;
        
        if (strcmp(command, "push") == 0)
        {
            int number;
            inFile >> number;

            heap.insert(number);
            pushing.toPush(std::make_pair(counter, number));
        }
        else if (strcmp(command, "extract-min") == 0)
        {
            
            if (heap.toSize() == 0){
                outFile << "*\n";
            }

            else{
           
                outFile << heap.extractMin() << '\n';
            }
        }
        else if (strcmp(command, "decrease-key") == 0){

            int numRow;
            int newVal;

            inFile >> numRow >> newVal;

            heap.decrease_key(pushing[pushing.binSearch(numRow)].second, newVal);
        }

        while (isalpha(inFile.peek()) == 0 && inFile.get() != EOF) {}
    }

    inFile.close();
    outFile.close();
    return 0;
}
