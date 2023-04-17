//insert, delete, search, print, and create the Lexicon with a specified size.
#include <iostream>
#include <list>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

using std::vector;

class Lexicon {
    public:
        int N; // num of slots in hash table T
        int* T;
        char* A;
        int slotsUsed; //to prevent collision
        int indexA;
    
    Lexicon(int N) { //initializes Lexicon
        this->N = N;
        this->slotsUsed = 0;
        this->T = new int[N];
        for (int i = 0; i < N; i++) {
            this->T[i] = 0; //-1 means empty
        }
        this->A = new char[N]; //will expand A
        // for (int i = 0; i < N; i++) {
        //     this->A[i] = '-'; //empty string
        // }
        int indexA = 0;

    }

    void increaseASize(){ //doubles size of A
        char* temp = new char[sizeof(this->A)*2];
        for (int i = 0; i < sizeof(this->A); i++){
            temp[i] = this->A[i];
        }
        this->A = temp;
    }

    void increaseTSize(){ //doubles size of T
        int* temp = new int[N*2];
        for (int i = 0; i < N; i++){
            temp[i] = this->T[i];
        }
        this->T = temp;
        this->N *= 2;
    }

    int h(string key) {
        int sum = 0;
        for (int i = 0; i < key.length(); i++) {
            sum += key[i];
        }
        return sum;
    }
    int QuadProbing(int h, int i) const { //h(k,i) = (h'(k) + i^2) mod N
        return (h + i*i) % N;
    }

    void Insert(string str) {
        if (Search(str) == -1){
            if (Full()) {
                increaseTSize();
            }
            for (int i = 0; i < this->N; i++) {
                int hashNum = QuadProbing(h(str), i);
                if (this->T[hashNum] == -1) {
                    //means empty
                    this->T[hashNum] = this->indexA;
                    for (int count = 0; count < str.length(); count++) {
                        if (this->indexA >= sizeof(this->A))
                        {
                            increaseASize();
                        }
                        this->A[indexA] = str[count];
                        this->indexA++;
                    }
                    this->A[this->indexA] = '\0';
                    this->indexA++;
                    this->slotsUsed++;
                    break;
                }
            }
        }
    }
    void Delete(string str) {
        if (Search(str) > -1){
            int indexHash = Search(str);
            int indexChar = this->A[this->T[indexHash]];
            for (int i = indexChar+str.length()+1; i >= indexChar; i++){
                this->A[i] = '-';
                this->indexA--; //not sure if this is needed yet
                this->slotsUsed--;
            }
        }
    }


    int Search(string str) {
        string strWithEnding = str + '\0';
       for (int i = 0; i < this->N; i++) {
            int hashNum = QuadProbing(h(str), i);
            if (this->T[hashNum] <= 0) {
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
        string printT;
        string printA;

        for (int i = 0; i < this->N; i++) {
            printT += this->T[i];
        }

        for (int i = 0; i < this->indexA; i++){
            if (this->A[i]=='\0') {
                printA += '\\';
            } else {
                printA += this->A[i];
            }
        }

        return printT + '\n' + printA;
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
    test->Print();

}