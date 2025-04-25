// hw01.cpp
// Created by Junyu (Leo) Zhao on 1/26/2025
// The program aims to decrypt files that are encoded by a certain format
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


char decryChar(char& encryChar, int step);
string decryStr(string& encryStr, int step);


int main() {
    ifstream ifs;
    ifs.open("encrypted.txt");
    if (!ifs) {
        cerr << "Fail to open file" << endl;
        exit(1);
    }
    int step;
    ifs >> step;
    string line;
    vector<string> lines;
    while (getline(ifs, line)) {
        lines.push_back(decryStr(line, step));
    } ifs.close();
    for (size_t i = lines.size(); i > 1; i--) {
        cout << lines[i-1] << endl;
    }
}


char decryChar(char& encryChar, int step) {
    if (encryChar >= 'A' && encryChar <= 'Z') {
        encryChar -= step;
        if (encryChar < 'A') {
            encryChar += 26;
        } else if (encryChar > 'Z') {
            encryChar -= 26;
        }
    } return encryChar;
}


string decryStr(string& encryStr, int step) {
    for (char& encryChar : encryStr) {
        decryChar(encryChar, step);
    } return encryStr;
}
