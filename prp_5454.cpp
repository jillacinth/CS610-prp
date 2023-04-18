//insert, delete, search, print, and create the Lexicon with a specified size.
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
        // int* temp = new int[this->N * 2];
        // for (int i = 0; i < this->N; i++) {
        //     temp[i] = this->T[i];
        // }
        // for (int i = this->N; i < this->N*2; i++) {
        //     temp[i] = -1;
        // }
        // delete[] this->T;
        // this->T = temp;
        // this->N *= 2;
        // return;

        this->N *= 2;
        delete this->T;
        this->T = new int[this->N];
        for(int i = 0; i < this->N; i++){
            this->T[i] = -1;
        }
        this->slotsUsed = 0;
        char* aTemp = new char[this->sizeofA];
        for(int i = 0; i<this->sizeofA; i++){
            aTemp[i] = this->A[i];
        }
        int max = this->indexA;
        this->indexA = 0;
        this->A = new char[this->indexA];
           
        string wordsUsed = "";
        for(int i = 0; i<max; i++){
            if(aTemp[i] != '\0'){
                wordsUsed += aTemp[i];
            }
            else{
               int len = wordsUsed.length();
                if(wordsUsed[0] == '*'){
                    int limit = this->indexA + len;
                    for(; this->indexA<limit; this->indexA++){
                        this->A[this->indexA] = '*';
                    }
                    this->A[this->indexA] = '\0';
                    this->indexA++;
                    wordsUsed = "";
                }
                else{
                    this->Insert(wordsUsed);
                    wordsUsed = "";
                }
            }
        }
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
        int aDelete = this->T[hashIndex];
        //cout << this->A[aDelete] << endl;
        for (int i = aDelete; i < aDelete + str.length(); i++ ) {
            this->A[i] = '*';
        }
        if (hashIndex > -1){
            this->T[hashIndex] = -2;
        }
        return;
    }


    int Search(string str) {
        //string strWithEnding = str + '\0';
       for (int i = 0; i < this->N; i++) {
            int hashNum = QuadProbing(h(str), i);
            if (this->T[hashNum] == -2) {
                return -1;
            } else if (this->T[hashNum] >= 0) {
                //means has value
                cout << hashNum << endl;
                cout << this->T[hashNum] << endl;
                int stringEnd = this->T[hashNum]+str.length();
                int strIndex = 0;
                for (int count = this->T[hashNum]; count <= stringEnd; count++) {
                    cout << this->A[count] << endl;
                    cout << count << endl;
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
            return(test->Search(str));
        }

        string Print(){
            return(test->Print());
        }

        bool Empty(){
            return(test->Empty());
        }

        bool Full(){
            return(test->Full());
        }
        
        void Delete(string str){
            test->Delete(str);
            return;
        }

        void Insert(string str){
            test->Insert(str);
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
                        string str = line.substr(command.length() + 1, line.length() - 1);
                        Insert(str);
                        int index = Search(str);
                        cout << str + "\tadded to slot " + to_string(index) << endl;
                    } else if(command.compare("11") == 0){
                        string str = line.substr(command.length() + 1, line.length() - 1);
                        int index = Search(str);
                        Delete(str);
                        cout << str + "\tdeleted from slot " + to_string(index) << endl;
                    } else if(command.compare("12") == 0){
                        string str = line.substr(command.length() + 1, line.length() - 1);
                        int index = Search(str);
                        cout << str + " ";
                        if(index == -1){
                            cout << "\tnot found" << endl;
                        }
                        else{
                            cout << "\tfound at slot " + to_string(index) << endl;
                        }
                    } else if(command.compare("13") == 0){
                        cout << Print() << endl ;
                    } else if(command.compare("14") == 0){
                        string str = line.substr(command.length() + 1, line.length() - 1);
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

int main(int argc, char* argv[]) {
    Lexicon* test = new Lexicon(10);
    test->Insert("word");
    test->Insert("cum");
    test->Delete("cum");
    test->Insert("cum");
    test->Insert("Patrick");
    test->Insert("Jill");
    test->Insert("googoogagaa");
    test->Insert("happybirthday");
    test->Insert("hello");
    test->Insert("phrase");
    test->Insert("school");
    test->Insert("car");
    test->Insert("school");
    test->Insert("television");
    
    cout << "find hello" << endl;
    cout << test->Search("hello") << endl;

    // test->Delete("hello");
    // test->Insert("cheese");

    string tryprint = test->Print();
    
    cout << tryprint << endl;
    // test->Insert("word");
    // string testprint1 = test->Print();
    // cout << testprint1 << endl;
}
