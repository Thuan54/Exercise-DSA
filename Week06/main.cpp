#include <iostream> 
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

#define MAXTABLESIZE 2000
using namespace std;

struct Company{
    string name;
    string taxCode;
    string address;
};

struct HashTable{
    int size;
    vector<Company*> table;
    HashTable(vector<Company*> data);
    ~HashTable();
    long long hashFunction(string s);
    long long collisionFunction(int hash);
    void insert(Company* data);
    Company* search(string key);
};

vector<Company*> readCompaniesList(string fileName);

int main(int argc, char* argv[]){
    string dataFileName = argv[1];
    string inputFileName = argv[2];
    string outputFileName = argv[3];
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);
    if(!inputFile){
        cout<<"Error opening file"<<endl;
        return 1;
    }
    vector<Company*> companies = readCompaniesList(dataFileName);
    HashTable hashTable(companies);
    
    string line;
    while(getline(inputFile,line)){
        Company* company = hashTable.search(line);
        if(company){
            outputFile<<company->name<<'|'<<company->taxCode<<'|'<<company->address<<endl;
        }
    }
    return 0;
}

vector<Company*> readCompaniesList(string fileName){
    vector<Company*> companies;
    ifstream file(fileName);
    if(!file){
        cout<<"Error opening file"<<endl;
        return companies;
    }
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        Company* company = new Company();
        getline(ss, company->name, '|');
        getline(ss, company->taxCode, '|');
        getline(ss, company->address, '|');
        companies.push_back(company);
    }
    return companies;
}
HashTable::HashTable(vector<Company*> data){
    if(data.size() > MAXTABLESIZE){
        cout<<"Data size exceed table size"<<endl;
        return;
    }
    size = 0;
    table.resize(MAXTABLESIZE,nullptr);
    for(int i = 0; i < data.size(); i++){
        insert(data[i]);
    }
}
HashTable::~HashTable(){
    for(int i = 0; i < MAXTABLESIZE; i++){
        if(table[i] != nullptr){
            delete table[i];
        }
    }
    table.clear();
    table.resize(0);
}
long long HashTable::hashFunction(string s){
    int P = 31;
    long long p = 1;
    long long hash = 0;
    for(int i = 0; i < s.length(); i++){
        hash += ((s[i]%MAXTABLESIZE)*(p%MAXTABLESIZE))%MAXTABLESIZE;
        p = (p%MAXTABLESIZE)*(P%MAXTABLESIZE);
    }
    hash %= MAXTABLESIZE;
    return hash;
}
long long HashTable::collisionFunction(int i){
    return (i+1)%MAXTABLESIZE;
}
void HashTable::insert(Company* data){
    if(size >= MAXTABLESIZE){
        cout<<"Error: table is full"<<endl;
        return;
    }
    size++;
    long long hash = hashFunction(data->name);
    int index = hash % MAXTABLESIZE;
    if(table[index] == nullptr){
        table[index] = data;
    } 
    else {
        while(table[index] != nullptr){
            index = collisionFunction(index);
        }
        table[index] = data;
    }
}
Company* HashTable::search(string key){
    long long hash = hashFunction(key);
    int i = hash % MAXTABLESIZE;
    while(table[i] != nullptr){
        if(table[i]->name == key){
            return table[i];
        }
        i = collisionFunction(i);
    }
    return nullptr;
}