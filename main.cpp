#include "test_runner.h"
#include "profile.h"

#include <iterator>
#include <numeric>
#include <vector>
#include <list>

using namespace std;

/*template <typename T>
struct Node {
  T item;
  Node<T>* next;
  Node(const T& item_, Node<T>* t): item(std::move(item_)), next(t) {}
};


template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
  typedef Node<typename RandomIt::value_type>* link;
  link t;

  t = new Node<typename RandomIt::value_type>(*first, nullptr);
  t->next = t;
  link x = t;

  for (auto it = first + 1; it != last; it++) {
    x = (x->next = new Node<typename RandomIt::value_type>(*it, t));
  }

  while (x != x->next) {
    //*(first++) = std::move(x->item);
    auto cur_pos = 0;
    for (int i = 1; i < step_size; i++) {
      x = x->next;
      cur_pos++;
    }
    x->next = x->next->next;
  }

}*/


//it works, 6th test fails on time
template<typename RandomIt>
void MakeJosephusPermutation_(RandomIt first, RandomIt last, uint32_t step_size) {
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
    std::cout << "cur_pos: " << cur_pos << ", cur_pos_it distance from begin: " << std::distance(pool.begin(), cur_pos_it) << std::endl;
  }
}

template<typename T>
string list_as_string(list<T> l) {
  bool first = true;
  stringstream ss;
  ss << '[';
  for (auto elem: l) {
    if (!first) {
      ss << ", " << elem;
    } else {
      first = false;
      ss << elem;
    }
  }
  ss << ']';
  return ss.str();
}

template<typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
  list<typename RandomIt::value_type> pool(make_move_iterator(first), make_move_iterator(last));
  size_t cur_pos = 0;
  auto cur_pos_it = pool.begin();
  while (!pool.empty()) {
    *(first++) = std::move(*cur_pos_it);
    auto prev_pos_it = pool.erase(cur_pos_it);
    cur_pos_it = prev_pos_it;

    if (pool.empty()) {
      break;
    }

    auto prev_pos = cur_pos;
    cur_pos = (cur_pos + step_size - 1) % pool.size();

    if (cur_pos < prev_pos) {
      cur_pos_it = pool.begin();
      advance(cur_pos_it, cur_pos);
    } else {
      advance(cur_pos_it, cur_pos - prev_pos);
    }
  }
}

template <typename RandomIt>
void MakeJosephusPermutationV0(RandomIt first, RandomIt last, uint32_t step_size) {
  vector<typename RandomIt::value_type> pool(make_move_iterator(first), make_move_iterator(last));
    size_t cur_pos = 0;
    while (!pool.empty()) {
      auto cur_pos_it = pool.begin() + cur_pos;
      *(first++) = std::move(pool[cur_pos]);
      pool.erase(cur_pos_it);
    if (pool.empty()) {
      break;
    }
    cur_pos = (cur_pos + step_size - 1) % pool.size();
    //std::cout << "cur_pos: " << cur_pos << ", cur_pos_it distance from begin: " << std::distance(pool.begin(), cur_pos_it) << std::endl;
  }
}

vector<int> MakeTestVector() {
  vector<int> numbers(10);
  iota(begin(numbers), end(numbers), 0);
  return numbers;
}

vector<int> MakeTestVector(size_t vector_size) {
  vector<int> numbers(vector_size);
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

  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  RUN_TEST(tr, TestAvoidsCopying);
  //RUN_TEST(tr, TestIntVector2);

  /*vector<int> v0 {1, 2, 3, 4, 5, 6, 7, 8, 9};
  size_t step_size = 2;

  cout << "V3 version:" << endl;
  MakeJosephusPermutationV3(v0.begin(), v0.end(), step_size);
  cout << v0 << endl;
  cout << "----------------------------------------" << endl;


  cout << "V0 version:" << endl;
  MakeJosephusPermutationV0(v0.begin(), v0.end(), step_size);
  cout << v0 << endl;
  cout << "----------------------------------------" << endl;*/

  /*vector<int> v1{1, 2, 3, 4, 5};
  cout << "Basic test example----------------------:" << endl;
  MakeJosephusPermutationV3(v1.begin(), v1.end(), 2);
  cout << v1 << endl;
  cout << "----------------------------------------" << endl;*/


  /*auto v = MakeTestVector(10);
  cout << v << endl;

  auto it = v.begin();
  advance(it, v.size() - 1);
  cout << *v.end() << endl;
  cout << "Before erase: " << *it << endl;
  auto next_it = v.erase(it);
  cout << "Element after removal of the last: " << *next_it << endl;
  cout << (next_it == v.end()) << endl;*/
  auto v = MakeTestVector(100'000);
  MakeJosephusPermutationV0(v.begin(), v.end(), 100);
  cout << v << endl;

  auto v2 = MakeTestVector(100'000);
  MakeJosephusPermutation(v2.begin(), v2.end(), 100);

  for (int i = 0; i < v.size(); ++i) {
    if (v[i] != v2[i]) {
      cout << "At index v[" << i << "] != v2[" << i << "]: " << v[i] << "!= "<< v2[i] << endl;
    }
  }


  return 0;
}
