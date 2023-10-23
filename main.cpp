#include "test_runner.h"

#include <iterator>
#include <numeric>
#include <vector>
#include <list>

using namespace std;

struct NoncopyableInt {
  int value;

  NoncopyableInt(const NoncopyableInt&) = delete;
  NoncopyableInt& operator=(const NoncopyableInt&) = delete;

  NoncopyableInt(NoncopyableInt&&) = default;
  NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
  return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
  return os << v.value;
}

/*template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
  vector<typename RandomIt::value_type> pool(first, last);
  size_t cur_pos = 0;
  while (!pool.empty()) {
    *(first++) = pool[cur_pos];
    pool.erase(pool.begin() + cur_pos);
    if (pool.empty()) {
      break;
    }
    cur_pos = (cur_pos + step_size - 1) % pool.size();
  }
}*/

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
  auto size = distance(first, last);
  size_t cur_pos = 0;
  while(size > 1) {
    auto it = first + cur_pos;
    remove(it);
    size = distance(first, last);
    cur_pos = (cur_pos + step_size - 1) % size;
  }
}

vector<int> MakeTestVector() {
  vector<int> numbers(10);
  iota(begin(numbers), end(numbers), 0);
  return numbers;
}

/*
void TestIntVector() {
  const vector<int> numbers = MakeTestVector();
  {
    vector<int> numbers_copy = numbers;
    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
    ASSERT_EQUAL(numbers_copy, numbers);
  }
  {
    vector<int> numbers_copy = numbers;
    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
    ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
  }
}

void TestAvoidsCopying() {
  vector<NoncopyableInt> numbers;
  numbers.push_back({1});
  numbers.push_back({2});
  numbers.push_back({3});
  numbers.push_back({4});
  numbers.push_back({5});

  MakeJosephusPermutation(begin(numbers), end(numbers), 2);

  vector<NoncopyableInt> expected;
  expected.push_back({1});
  expected.push_back({3});
  expected.push_back({5});
  expected.push_back({4});
  expected.push_back({2});

  ASSERT_EQUAL(numbers, expected);
}
*/

template <typename RandomIt>
void SwapListElements(list<int>& list, RandomIt iterator1, RandomIt iterator2) {



}


int main() {
/*
  vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  auto size = distance(v.begin(), v.end());
  auto first = v.begin();
  auto last = v.end();
  size_t step_size = 2;
  auto current = first;

  size_t cur_pos = 0;
  while (v.size() > 1) {
    auto element_to_remove = v.begin() + cur_pos;
    cout << "Vector: " << v << endl;
    cout << "Element to remove: " << *element_to_remove << endl;
    v.erase(element_to_remove);
    cout << "Updated vector: " << v << endl;

    cur_pos = (cur_pos + step_size - 1) % v.size();
  }

  cout << v << endl;*/

  list<int> l = {1, 2, 3, 4, 5, 6, 7, 8};
  auto it = l.begin();
  auto it2 = l.begin();

  advance(it, 2);
  advance(it2, 3);

  int& it_ref = *it;
  int& it2_ref = *it2;

  cout << it_ref << endl;
  cout << it2_ref << endl;


  return 0;
}
