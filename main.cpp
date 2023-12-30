#include "test_runner.h"

#include <iterator>
#include <numeric>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>

using namespace std;

struct NoncopyableInt {
  int value;

  NoncopyableInt(const NoncopyableInt &) = delete;

  NoncopyableInt &operator=(const NoncopyableInt &) = delete;

  NoncopyableInt(NoncopyableInt &&) = default;

  NoncopyableInt &operator=(NoncopyableInt &&) = default;
};

template<typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size);

void print_list(const list<int> &l) {
  for (auto it = l.begin(); it != l.end(); ) {
    cout << *it << " ";
    advance(it, 1);
  }
}


vector<int> MakeTestVector();

void TestIntVector();

bool operator==(const NoncopyableInt &lhs, const NoncopyableInt &rhs);

ostream &operator<<(ostream &os, const NoncopyableInt &v);

template<typename RandomIt>
void MakeJosephusPermutation2(RandomIt first, RandomIt last, uint32_t step_size);

void TestAvoidsCopying();

int main() {
  vector<int> v{1, 2, 3, 4, 5};
  MakeJosephusPermutation2(v.begin(), v.end(), 2);

  return 0;
}

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

bool operator==(const NoncopyableInt &lhs, const NoncopyableInt &rhs) {
  return lhs.value == rhs.value;
}

template<typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
  vector<typename RandomIt::value_type> pool(make_move_iterator(first), make_move_iterator(last));
  size_t cur_pos = 0;
  size_t prev_pos;
  auto element_to_remove = pool.begin();
  while (!pool.empty()) {
    *(first++) = std::move(pool[cur_pos]);
    (prev_pos < cur_pos) ? element_to_remove += step_size - 1 : element_to_remove = pool.begin() + cur_pos;
    pool.erase(element_to_remove);
    if (pool.empty()) break;
    prev_pos = cur_pos;
    cur_pos = (cur_pos + step_size - 1) % pool.size();
  }
}

ostream &operator<<(ostream &os, const NoncopyableInt &v) {
  return os << v.value;
}

template<typename RandomIt>
void MakeJosephusPermutation2(RandomIt first, RandomIt last, uint32_t step_size) {

  list<typename RandomIt::value_type> pool(make_move_iterator(first), make_move_iterator(last));

  size_t cur_pos = 0;
  size_t prev_pos;
  auto element_to_remove = pool.begin();

  while (!pool.empty()) {
    auto curr = element_to_remove;
    cout << " " << *curr << endl;
    pool.erase(curr);
    advance(element_to_remove, 1);
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

vector<int> MakeTestVector() {
  vector<int> numbers(10);
  iota(begin(numbers), end(numbers), 0);
  return numbers;
}