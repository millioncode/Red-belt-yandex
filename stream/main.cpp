#include <iostream>
#include <string>
#include <fstream>
#include "profile.h"
using namespace std;
#define MAX 1'000'000
int main()
{
    cout << __cplusplus << endl;
    const string words {"Let's go rock'n'roll."};
    {
        LOG_DURATION("endl:");
        ofstream out("output1.txt");
        for(int i=0; i<MAX; i++) {
            out << words << endl;
        }
    }
    {
        LOG_DURATION("w/o endl:");
        ofstream out("output2.txt");
        for(int i=0; i<MAX; i++) {
            out << words << '\n';
        }
    }
    cout << __cplusplus << endl;
    return 0;
}
