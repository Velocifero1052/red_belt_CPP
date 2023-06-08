//#include "test_runner.h"
//#include "airline_ticket.h"
#include "test_runner.h"
#include <iomanip>
#include <sstream>

using namespace std;

#define S1(x) #x
#define S2(x) S1(x)

#define C() __

#define A(b) uniquename_##__LINE__

#define UNIQ_ID A(varabile)


#define LOCATION __FILE__ S2(__LINE__)

int main() {

    int UNIQ_ID = 0;
    cout << LOCATION << endl;
  //  string UNIQ_ID = "hello";

  /*  string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = {"hello", "world"};
    vector<int> UNIQ_ID = {1, 2, 3, 4};*/
  return 0;
}

