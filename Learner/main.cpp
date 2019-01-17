#include <iostream>
#include <string>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include "class.h"

using namespace std;
class Learner ;

int main() {
    Learner learner;
    string line;
    while (getline(cin, line)) {
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        cout << learner.Learn(words) << "\n";
    }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords()) {
        cout << word << "\n";
    }
}
