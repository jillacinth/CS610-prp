//insert, delete, search, print, and create the Lexicon with a specified size.
#include <iostream>
#include <list>
#include <cstring>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

using std::vector;

class Lexicon {
    public:
        int N; // num of slots in hash table T
        int* T;
        char* A;
        int slotsUsed; //to prevent collision
        int indexA;
        int sizeofA;
    
    Lexicon(int N) { //initializes Lexicon
        this->N = N;
        this->slotsUsed = 0;
        this->T = new int[N];
        for (int i = 0; i < N; i++) {
            this->T[i] = -1; //-1 means empty
        }
        this->sizeofA = this->N*10;
        this->A = new char[this->sizeofA]; //will expand A
        // for (int i = 0; i < N; i++) {
        //     this->A[i] = '-'; //empty string
        // }
        this->indexA = 0;

    }

    ~Lexicon(){
        delete[] this->T;
    }

    void increaseASize() { //doubles size of A
        char* temp = new char[ this->sizeofA * 2 + 1];
        for (int i = 0; i < sizeofA; i++) {
            temp[i] = this->A[i];
        }
        delete[] this->A;
        this->A = temp;
        this->sizeofA = 2*this->sizeofA + 1;
        return;
    }

    void increaseTSize() { //doubles size of T
        int* temp = new int[this->N * 2];
        for (int i = 0; i < this->N; i++) {
            temp[i] = this->T[i];
        }
        delete[] this->T;
        this->T = temp;
        this->N *= 2;
        return;
    }

    int h(string key) {
        int sum = 0;
        for (int i = 0; i < key.length(); i++) {
            sum += key[i];
        }
        return sum;
    }
    int QuadProbing(int h, int i) const { //h(k,i) = (h'(k) + i^2) mod N
        return (h + i*i) % this->N;
    }

    void Insert(string str) {
        if (Search(str) == -1){
            if (Full()) {
                increaseTSize();
            }
            for (int i = 0; i < this->N; i++) {
                int hashNum = QuadProbing(h(str), i);
                if (this->T[hashNum] == -1 || this->T[hashNum] == -2 ) {
                    //means empty
                    this->T[hashNum] = this->indexA;
                    for (int count = 0; count < str.length(); count++) {
                        if (this->indexA >= this->sizeofA)
                        {
                            increaseASize();
                        }
                        this->A[indexA] = str[count];
                        this->indexA++;
                    }
                    this->A[this->indexA] = '\0';
                    this->indexA++;
                    this->slotsUsed++;
                    return;
                }
            }
        }
        return;
    }
    void Delete(string str) {
        int hashIndex = Search(str);
        if (hashIndex > -1){
            this->T[hashIndex] = -2;
        }
        return;
    }


    int Search(string str) {
        string strWithEnding = str + '\0';
       for (int i = 0; i < this->N; i++) {
            int hashNum = QuadProbing(h(str), i);
            if (this->T[hashNum] == -2) {
                return -1;
            } else if (this->T[hashNum] >= 0) {
                //means has value
                int stringEnd = this->T[hashNum]+strWithEnding.length();
                int strIndex = 0;
                for (int count = this->T[hashNum]; count <= stringEnd; count++) {
                    if (count == stringEnd && this->A[count] == '\0') {
                        return hashNum; //returns the index of hash
                    }
                    else if (this->A[count] != str[strIndex])
                    {
                        return -1; //means not found
                    }
                    strIndex++; 
                }
            }
        }
        return -1;
    }


    string Print() {
        string printHash = "T (hashes) \n";

        for (int i = 0; i < this->N; i++) {
           printHash += std::to_string(this->T[i]);
           printHash += "\n";
        }

        printHash += "A (chars)";

        for (int i = 0; i < this->indexA; i++){
            if (this->A[i]=='\0') {
                printHash += '\\';
            } else {
                printHash += this->A[i];
            }
        }

        return printHash;

    } 
    //Create
    bool Empty() {
        if (this->slotsUsed == 0) {
            return true;
        } else {
            return false;
        }
    }
    bool Full() {
        if (this->slotsUsed == N) {
            return true;
        } else {
            return false;
        }
    }
    //Batch
    //Comment



};

int main(int argc, char* argv[]) {
    Lexicon* test = new Lexicon(10);
    test->Insert("word");
    test->Insert("cum");
    test->Delete("cum");
    test->Insert("cum");
    //test->Insert("Patrick");
    //test->Insert("Jill");
    //test->Insert("googoogagaa");

    string tryprint = test->Print();
    
    cout << tryprint << endl;
    // test->Insert("word");
    // string testprint1 = test->Print();
    // cout << testprint1 << endl;
}
