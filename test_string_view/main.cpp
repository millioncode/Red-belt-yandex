#include <iostream>
#include <vector>
#include <string_view>
#include "profile.h"
using namespace std;
vector <string> SplitString (const string& words);
vector <string_view> SplitStringView (const string& words);
string Prepare(const size_t& number);
int main()
{
    string words = Prepare(100'000'000);
    {
        LOG_DURATION("SplitString");
        SplitString(words);
    }
    {
        LOG_DURATION("SplitStringView");
        SplitStringView(words);
    }
    return 0;
}
