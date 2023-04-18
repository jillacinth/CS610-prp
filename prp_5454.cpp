//Jillian Jacinto: 5454
#include <iostream>
#include <fstream>
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
        this->sizeofA = this->N*15;
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
        char* temp = this->A;
        int oldsizeA = this->sizeofA;
        this->sizeofA = this->sizeofA*2 + 1;
        this->A = new char[this->sizeofA];
        for (int i = 0; i < oldsizeA; i++) {
            this->A[i] = temp[i];
        }
        return;
    }

   void increaseTSize() { // doubles size of T and rehashes existing keys and values
        int oldN = this->N;
        int* oldT = this->T;
    
        this->N *= 2;
        this->T = new int[this->N];
        for (int i = 0; i < this->N; i++) {
            this->T[i] = -1; // initialize new table to empty
        }
        this->slotsUsed = 0;

        char* oldA = this->A;
        this->A = new char[this->sizeofA * 2 + 1]; // double size of A

        // rehash existing keys and values into new 
        for (int i = 0; i < oldN; i++) {
            if (oldT[i] != -1 && oldT[i] != -2) {
                string key;
                int j = oldT[i];
                while (oldA[j] != '\0') {
                    key += oldA[j];
                    j++;
                }
                lexInsert(key); // insert existing key-value pair into new table
            }
        }

        this->sizeofA = this->sizeofA * 2 + 1;

        delete[] oldT;
        delete[] oldA;
    }

    int h(string key) {
        int sum = 0;
        for (int i = 0; i < key.length(); i++) {
            sum += key[i];
        }
        return sum - 4;
    }
    int QuadProbing(int h, int i) const { //h(k,i) = (h'(k) + i^2) mod N
        return (h + i*i) % this->N;
    }

    void lexInsert(string str) {
        if (lexSearch(str) == -1){
            if (lexFull()) {
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
    void lexDelete(string str) {
        int hashIndex = lexSearch(str);
        if (hashIndex != -1) {
            int aDelete = this->T[hashIndex];
        // set the string in A to '*' characters to mark it as deleted
            for (int i = aDelete; i < aDelete + str.length(); i++ ) {
                this->A[i] = '*';
            }
        // set the hash table value to -2 to indicate that the slot is deleted
            this->T[hashIndex] = -2;
        }
        return;
    }


    int lexSearch(string str) {
        for (int i = 0; i < this->N; i++) {
            int hashNum = QuadProbing(h(str), i);
            if (this->T[hashNum] == -1) {
                return -1;
            } else if (this->T[hashNum] >= 0) {
            // Get the string in A starting from the index in T
                string key;
                int j = this->T[hashNum];
                while (this->A[j] != '\0') {
                    key += this->A[j];
                    j++;
                } 
            // Compare the string in A with the search string
                if (key == str) {
                    return hashNum;
                }
            }
        }
        return -1;
    }


    string lexPrint() {
        string printHash = "T \tA:";
        for (int i = 0; i < this->indexA; i++){
            if (this->A[i]=='\0') {
                printHash += '\\';//replace /0 with //
        
            } else if (this->A[i]=='\n') {
              continue;
            } else {
                printHash += this->A[i];
            }
            
        }
        printHash += '\n';
        //something in this for loop above messes up T

        for (int i = 0; i < this->N; i++) {
           if (this->T[i] >= 0) {
                printHash += to_string(this->T[i]);
           }
           printHash += "\n";
        }
        return printHash;
    } 
    bool lexEmpty() {
        if (this->slotsUsed == 0) {
            return true;
        } else {
            return false;
        }
    }
    bool lexFull() {
        if (this->slotsUsed == N) {
            return true;
        } else {
            return false;
        }
    }
};
class Hashing{
    public:

        string filename;
        Lexicon* test;

        Hashing(string filename){
            this->filename = filename;
        }

        void Create(int N){
            test = new Lexicon(N);
            return;
        }

        int Search(string str){
            return(test->lexSearch(str));
        }

        string Print(){
            return(test->lexPrint());
        }

        bool Empty(){
            return(test->lexEmpty());
        }

        bool Full(){
            return(test->lexFull());
        }
        
        void Delete(string str){
            test->lexDelete(str);
            return;
        }

        void Insert(string str){
            test->lexInsert(str);
            return;
        }
        
        void Batch(){
            ifstream inputFile;
            //we have filename
            string line;
            inputFile.open(filename);
            if(inputFile.is_open()){
                while(getline(inputFile,line)){     
                    string command = line.substr(0, line.find(" "));
                    if(command.compare("10") == 0){
                        string str = line.substr(3, line.length() - command.length() - 2);
                        Insert(str);
                        int index = Search(str);
                        cout << str + "\tadded to slot " + to_string(index) << endl;
                    } else if(command.compare("11") == 0){
                        string str = line.substr(3, line.length() - command.length() - 2);
                        int index = Search(str);
                        Delete(str);
                        cout << str + "\tdeleted from slot " + to_string(index) << endl;
                    } else if(command.compare("12") == 0){
                        string str = line.substr(3, line.length() - command.length() - 2);
                        int index = Search(str);
                        if(index == -1){
                            cout << str + "\tnot found" << endl;
                        }
                        else{
                            cout << str + "\tfound at slot " + to_string(index) << endl;
                        }
                    } else if(command.compare("13") == 0){
                        cout << Print() << endl;
                    } else if(command.compare("14") == 0){
                        string str = line.substr(3, line.length() - command.length() - 2);
                        int N = stoi(str);
                        Create(N);
                    } else if(command.compare("15") == 0){
                        continue;
                    }
                }

                inputFile.close();
            }
            return;
        }
};


int main(int argc, char* argv[]){
    string filename = argv[1];
    Hashing* test = new Hashing(filename);
    test->Batch();
   return(0);
}