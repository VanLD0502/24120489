#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

const long long p = 31;

unsigned long long powP[21];

const long long m = 2000;
struct Company{
    string name;
    string profit_tax;
    string address;

    Company(string _name, string _profit, string _address) : name(_name), profit_tax(_profit), address(_address) {}
};

struct HashTable {
    int size = 2000;
    Company* table[2000];
};




void ComputePowP() {
    powP[0] = 1;
    for (int i = 1; i <= 20; i ++) {
        powP[i]= (powP[i - 1] * p) % m;
    }
}


int Hash(string s) {
    int res = 0;
    int j = 0;
    for (int i = max(0, (int)s.length() - 20); i < s.length(); i ++, j ++) {
        res = (res + (s[i] * powP[j]) % m) % m;
    }
    return res % m;
}

void Insert(HashTable* &hash_table, Company* company) {
    int probe = Hash(company->name);
    while (hash_table->table[probe] != nullptr) {
        probe = (probe + 1) % m;
    }    

    hash_table->table[probe] = company;
}



HashTable* createHashTable(vector<Company*> list_Company) {
    HashTable* newHashTable = new HashTable;
    for (int i = 0; i < newHashTable->size; i ++) {
        newHashTable->table[i] = nullptr;
    }
    for (auto company : list_Company) {
        Insert(newHashTable, company);
    }

    return newHashTable;
}



Company* Search (HashTable*& hash_table, string name) {
    int probe = Hash(name);
    while (hash_table->table[probe] != nullptr) {
        if (hash_table->table[probe]->name == name) {
            return hash_table->table[probe];
        }
        probe = (probe + 1) % m;
    }  

    return nullptr;
}




vector<Company*> readCompanyList(string file_name) {
    vector<Company*> list_Company;
    ifstream in(file_name);

    if (!in) {
        cout << "File khong ton tai" << '\n';
        return list_Company;
    }

    bool isFirstLine = true;
    string s;
    int cnt = 2;
    while (getline(in,s)) {
        if (isFirstLine) {
            isFirstLine = false;
        }
        else {
            stringstream ss(s);
            string word;
            vector<string> info;
            while (getline(ss, word, '|')) {
                info.push_back(word);
            }

            if (info.size() == 3) {
                list_Company.push_back(new Company(info[0], info[1], info[2]));
            }
            else {
                cout << "Loi vi khong du thong tin cong ty " <<  info[0];
            }
            
        }
    }

    return list_Company;

}



int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Thu tu thuc hien \n";
        std::cout << "g++ -std=c++11 *.cpp -o main or g++ 24120489.cpp -o main.exe\n";
        std::cout << "./main ./MST.txt ./input.txt ./output.txt : main(file exe), MST.txt(information file), input.txt(input file contain company's names need to search), output.txt(company's imfomation searched)\n";
        return 0;
    }
    ifstream in(argv[2]);
    if (!in) {
        cout << "input.txt khong ton tai\n";
        return 0;
    }
    ofstream out(argv[3]);
    if (!out) {
        cout << "output.txt khong ton tai\n";
        return 0;
    }

    vector<Company*> Companies = readCompanyList(argv[1]);

    ComputePowP();
    HashTable* hashTable = createHashTable(Companies);
    string s;
    while (getline(in, s)) {
        Company* company = Search(hashTable, s);

        if (company != nullptr) out << company->name << '|' << company->profit_tax << '|' << company->address << '\n';
        else {
            //out << "Don't find company with name : " << company->name << '\n';
        }
    }

    for (int i = 0; i < m; i ++) {
        if (hashTable->table[i] != nullptr) {
            delete hashTable->table[i];
        }
    }
    if (hashTable)
        delete hashTable;

    return 0;
}