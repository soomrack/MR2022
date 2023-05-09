#include <iostream>
#include "Aho_Corasick.h"
#include <ctime>
#include <fstream>

using namespace std;

int main() {

    class AC automat;

    ifstream file;
    char text[100];
    file.open("book.txt");
    string book;
    if(file) {
        while (!file.eof()) {
            file >> text;
            book.append(text);
            book.append(" ");
        }
        file.close();
    }
//    int N = 15;
    int words = 1000;

    file.open("book.txt");


    string source;

    cout << "Size of one book " << book.length() << endl;
    for(auto j = 0; j < 10; j++){
        source.append(book);
    }
    for (auto i = 0; i <= words; i+=100) {


        unsigned long long before = time(nullptr);
        automat.Find(source);
        unsigned long long after = time(nullptr);
        cout << "N: " << 10 << " Words: " << i << " Seconds: " << after - before << endl;
        for(int k = 0; k < words; k++){
            string temp;
            file >> temp;
            automat.AddString(temp);
        }
    }
    file.close();
    return 0;
}


