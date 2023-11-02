#include "test_runner.h"
#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

struct NoncopyableInt {
  int value;

  NoncopyableInt(const NoncopyableInt&) = delete;
  NoncopyableInt& operator=(const NoncopyableInt&) = delete;

  NoncopyableInt(NoncopyableInt&&) = default;
  NoncopyableInt& operator=(NoncopyableInt&&) = default;
};


template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
//  vector<typename RandomIt::value_type> pool(first, last);
//  size_t cur_pos = 0;
//  while (!pool.empty()) {
//    *(first++) = pool[cur_pos];
//    pool.erase(pool.begin() + cur_pos);
//    if (pool.empty()) {
//      break;
//    }
//    cur_pos = (cur_pos + step_size - 1) % pool.size();
//  }
}

vector<int> MakeTestVector() {
  vector<int> numbers(10);
  iota(begin(numbers), end(numbers), 0);
  return numbers;
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

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»



bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
  return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
  return os << v.value;
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

template <typename RandomIt>
void make_joseph_permutation(RandomIt first, RandomIt last, uint32_t step_size) {
  auto size = distance(first, last);
  auto element_to_remove = first + step_size;
  size_t cur_pos = 0;

  while (size > 1) {
    auto element_to_remove = first + cur_pos;
    auto it = remove(first, last, *element_to_remove);
    last = it;
    cur_pos = (cur_pos + step_size - 1) % size;
    size--;
  }

}


int main() {

  vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  auto size = distance(v.begin(), v.end());
  auto first = v.begin();
  auto last = v.end();
  size_t step_size = 2;
  auto current = first;

  size_t cur_pos = 0;
  while (size > 1) {
    auto element_to_remove = v.begin() + cur_pos;
    cout << "Vector: " << v << endl;
    cout << "Element to remove: " << *element_to_remove << endl;
    //v.erase(element_to_remove);
    auto res = remove(v.begin(), v.end(), *element_to_remove);
    v.erase(res, v.end());
    size--;
    cout << "Updated vector: " << v << endl;

    cur_pos = (cur_pos + step_size - 1) % v.size();
  }

  cout << v << endl;

  cout << "################################" << endl;

  vector<int> v2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  cout << "Initial second vector: " << v2 << endl;
  make_joseph_permutation(v2.begin(), v2.end(), 0);
  cout << "After permutation: " << v2;

  cout << "#################################" << endl;

  v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Create an iterator to the element to be removed.
  auto it = std::find(v.begin(), v.end(), 5);

// Remove the element from the vector.
  cout << v << endl;
  it = std::remove(v.begin(), v.end(), *it);
  cout << v << endl;
// Erase the unused elements from the vector.
  v.erase(it, v.end());

// Print the remaining elements of the vector.
  for (auto& element : v) {
    std::cout << element << " ";
  }

  /*Initial tests
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  RUN_TEST(tr, TestAvoidsCopying);
  */

  return 0;
}