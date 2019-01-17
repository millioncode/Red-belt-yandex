#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) \
  out << (x) << "\n" << (y) << "\n"

int main() {
  TestRunner tr;
  tr.RunTest([] {
      ostringstream output;
      PRINT_VALUES(output, 5, "red belt");
      ASSERT_EQUAL(output.str(), "5\nred belt\n");
    }, "PRINT_VALUES usage example");


  if ( PRINT_VALUES(cout, 1, 2) )
    PRINT_VALUES(cout, 3, 4);
  else PRINT_VALUES(cout, 5, 6);
}
