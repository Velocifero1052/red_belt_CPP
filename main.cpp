#include "test_runner.h"

#include <iterator>
#include <numeric>
#include <vector>
#include <list>

using namespace std;

template <typename T>
struct Node {
  T item;
  Node<T>* next;
  Node(const T& item_, Node<T>* t): item(item_), next(t) {}
};


template <typename RandomIt>
void MakeJosephusPermutationV1(RandomIt first, RandomIt last, uint32_t step_size) {
  typedef Node<typename RandomIt::value_type>* link;
  link t;

  t = new Node<typename RandomIt::value_type>(*first, nullptr);
  t->next = t;
  link x = t;

  for (auto it = first + 1; it != last; it++) {
    x = (x->next = new Node<typename RandomIt::value_type>(*it, t));
  }

  while (x != x->next) {
    *(first++) = std::move(x->item);
    for (int i = 1; i < step_size; i++) {
      x = x->next;
    }
    x->next = x->next->next;
  }

}


//it works, 6th test fails on time
template<typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
  list<typename RandomIt::value_type> pool(make_move_iterator(first), make_move_iterator(last));
  size_t cur_pos = 0;
  while (!pool.empty()) {
    auto cur_pos_it = pool.begin();
    advance(cur_pos_it, cur_pos);
    *(first++) = std::move(*cur_pos_it);
    pool.erase(cur_pos_it);
    if (pool.empty()) {
      break;
    }
    cur_pos = (cur_pos + step_size - 1) % pool.size();
  }
}

template<typename RandomIt>
void MakeJosephusPermutationV3(RandomIt first, RandomIt last, uint32_t step_size) {

  list<typename RandomIt::value_type> pool(make_move_iterator(first), make_move_iterator(last));
  size_t cur_pos = 0, prev_pos = 0;
  auto cur_pos_it = pool.begin();
  while (!pool.empty()) {
    if (cur_pos >= prev_pos) {
      cout << "if condition----------------------";
      cout << "prev_pos: " << prev_pos << endl;
      cout << "cur_pos: " << cur_pos << endl;
      cout << "--------------------------------";

      //advance(cur_pos_it, prev_pos - cur_pos);
    } else {
      cout << "else condition--------------------";
      cout << "prev_pos: " << prev_pos << endl;
      cout << "cur_pos: " << cur_pos << endl;
      cout << "----------------------------------";
      cur_pos_it = pool.begin();
      advance(cur_pos_it, cur_pos);
    }

    //.erase(cur_pos_it);
    pool.erase(pool.begin());
    if (pool.empty()) break;

    cur_pos = (cur_pos + step_size - 1) % pool.size();
  }
}

template <typename RandomIt>
void MakeJosephusPermutationV0(RandomIt first, RandomIt last, uint32_t step_size) {
  vector<typename RandomIt::value_type> pool(make_move_iterator(first), make_move_iterator(last));
    size_t cur_pos = 0;
    while (!pool.empty()) {
      *(first++) = std::move(pool[cur_pos]);
      pool.erase(pool.begin() + cur_pos);
    if (pool.empty()) {
      break;
    }
    cur_pos = (cur_pos + step_size - 1) % pool.size();
  }
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

  ASSERT_EQUAL(numbers, expected)
}

int main() {

  /*TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  RUN_TEST(tr, TestAvoidsCopying);*/

  vector<int> v0 {1, 2, 3, 4, 5, 6, 7, 8, 9};
  size_t step_size = 5;

  MakeJosephusPermutationV3(v0.begin(), v0.end(), step_size);
  cout << "First, textbook example-----------------:" << endl;
  cout << v0 << endl;
  cout << "----------------------------------------" << endl;
  vector<int> v1{1, 2, 3, 4, 5};
  MakeJosephusPermutationV3(v1.begin(), v1.end(), 2);
  cout << "Basic test example----------------------:" << endl;
  cout << v1 << endl;
  cout << "----------------------------------------" << endl;

  return 0;
}
