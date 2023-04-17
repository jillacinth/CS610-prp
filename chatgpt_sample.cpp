#include <iostream>
using namespace std;

const int TABLE_SIZE = 10;

class HashTable {
private:
    int* table;
    int size;
public:
    HashTable() {
        table = new int[TABLE_SIZE];
        size = 0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = -1;
        }
    }

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

    void insert(int key) {
        int hash = hashFunction(key);
        while (table[hash] != -1 && table[hash] != key) {
            hash = (hash + 1) % TABLE_SIZE;
        }
        if (table[hash] == -1) {
            size++;
            table[hash] = key;
        }
    }

    bool search(int key) {
        int hash = hashFunction(key);
        while (table[hash] != -1) {
            if (table[hash] == key) {
                return true;
            }
            hash = (hash + 1) % TABLE_SIZE;
        }
        return false;
    }

    void remove(int key) {
        int hash = hashFunction(key);
        while (table[hash] != -1) {
            if (table[hash] == key) {
                table[hash] = -1;
                size--;
                return;
            }
            hash = (hash + 1) % TABLE_SIZE;
        }
    }

    int getSize() {
        return size;
    }

    ~HashTable() {
        delete[] table;
    }
};

int main() {
    HashTable ht;
    ht.insert(5);
    ht.insert(2);
    ht.insert(7);
    ht.insert(10);
    cout << ht.search(2) << endl; // Output: 1 (true)
    ht.remove(7);
    cout << ht.getSize() << endl; // Output: 3
    return 0;
}