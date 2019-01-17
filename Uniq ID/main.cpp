#include <string>
#include <vector>
using namespace std;

// Реализуйте этот макрос так, чтобы функция main компилировалась

#define MAC1(number_str) a##number_str
#define MAC2(number_str) MAC1(number_str)
#define UNIQ_ID MAC2(__LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};

}
