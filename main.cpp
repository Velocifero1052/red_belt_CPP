#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <unordered_map>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

bool have_same_letters(const string& s1, const string& s2) {
  std::string sorted1 = s1;
  std::string sorted2 = s2;

  std::sort(sorted1.begin(), sorted1.end());
  std::sort(sorted2.begin(), sorted2.end());

  // Remove duplicates
  sorted1.erase(std::unique(sorted1.begin(), sorted1.end()), sorted1.end());
  sorted2.erase(std::unique(sorted2.begin(), sorted2.end()), sorted2.end());

  return sorted1 == sorted2;
}


template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {

  vector<Group<String>> res;
  while (!strings.empty()) {
    auto it = std::move(*strings.begin());
    Group<String> g;
    g.push_back(it);
    for (int i = 1; i < strings.size(); i++) {
      if (have_same_letters(it, strings[i])) {

      }
    }

  }


  return {};
}


void TestGroupingABC() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}




int main() {

  /*TestRunner tr;
  RUN_TEST(tr, TestGroupingABC);
  RUN_TEST(tr, TestGroupingReal);*/

  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  string word1 = "laptop";
  string word2 = "paloalto";
  cout << have_same_letters(word1, word2) << endl;

  return 0;
}
