#include "test_runner.h"

#include <iterator>
#include <numeric>
#include <vector>
#include <utility>
#include <list>

using namespace std;

struct NoncopyableInt {
  int value;

  NoncopyableInt(const NoncopyableInt&) = delete;
  NoncopyableInt& operator=(const NoncopyableInt&) = delete;

  NoncopyableInt(NoncopyableInt&&) = default;
  NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

template <typename RandomIt>
void MakeJosephusPermutationVector(RandomIt first, RandomIt last, uint32_t step_size) {
  vector<typename RandomIt::value_type> pool(make_move_iterator(first), make_move_iterator(last));
  size_t cur_pos = 0;
  size_t prev_pos;
  auto element_to_remove = pool.begin();
  while (!pool.empty()) {
    *(first++) = std::move(pool[cur_pos]);

    (prev_pos < cur_pos) ? element_to_remove += step_size - 1 : element_to_remove = pool.begin() + cur_pos;

    pool.erase(element_to_remove);
    if (pool.empty()) {
      break;
    }
    prev_pos = cur_pos;
    cur_pos = (cur_pos + step_size - 1) % pool.size();
  }
}

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
  list<typename RandomIt::value_type> pool(make_move_iterator(first), make_move_iterator(last));
  size_t cur_pos = 0;
  size_t prev_pos;
  auto element_to_remove = pool.begin();
  while (!pool.empty()) {

    auto it = pool.begin();
    advance(it, cur_pos);

    *(first++) = std::move(*it);

    if (prev_pos < cur_pos) {
      advance(element_to_remove, step_size - 1);
    } else {
      element_to_remove = pool.begin();
      advance(element_to_remove, cur_pos);
    }

    pool.erase(element_to_remove);
    if (pool.empty()) break;

    prev_pos = cur_pos;
    cur_pos = (cur_pos + step_size - 1) % pool.size();
  }

}

template <typename T>
struct Node {
  T item;
  Node* next;
  Node(T x, Node* t) {
    item = x;
    next = t;
  }
  Node() {
    next = nullptr;
  }
};



template <typename RandomIt>
void MakeJosephusPermutationCustomList(RandomIt first, RandomIt last, uint32_t step_size) {

  auto size = distance(first, last);
  if (size == 0 || size == 1) return;

  auto *head = new Node<typename RandomIt::value_type>();
  head->item = std::move(*first);
  head->next = nullptr;

  auto current_node = head;

  for (int i = 1; i < size; i++) {
    auto* new_node = new Node<typename RandomIt::value_type>();
    new_node->item = std::move(*(first + i));
    new_node->next = nullptr;

    current_node->next = new_node;
    current_node = new_node;
  }
  current_node->next = head;

  while (current_node != current_node->next) {
    for (int i = 1; i < step_size; i++) current_node = current_node->next;
    current_node->next = current_node->next->next;
  }
  cout << current_node->item << endl;

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

struct NodeCustom {
  int value;
  NodeCustom* next;
};

NodeCustom* create_singly_linked_list(const std::vector<int>& vec) {
  // Create a new head node for the linked list.
  NodeCustom* head = new NodeCustom();
  head->value = vec[0];
  head->next = nullptr;

  // Iterate over the vector and add each element to the linked list.
  NodeCustom* current_node = head;
  for (int i = 1; i < vec.size(); i++) {
    NodeCustom* new_node = new NodeCustom();
    new_node->value = vec[i];
    new_node->next = nullptr;

    current_node->next = new_node;
    current_node = new_node;
  }

  return head;
}

int main() {
/*  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  RUN_TEST(tr, TestAvoidsCopying);*/

  std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  MakeJosephusPermutationCustomList(vec.begin(), vec.end(), 5);

  return 0;
}
