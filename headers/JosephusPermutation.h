//
// Created by Rakhmon Radjabov on 13/02/24.
//

#ifndef RED_BELT_C___JOSEPHUSPERMUTATION_H
#define RED_BELT_C___JOSEPHUSPERMUTATION_H

#include "../test_runner.h"
#include "profile.h"

#include <iterator>
#include <numeric>
#include <vector>
#include <list>


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

template <typename Container, typename ForwardIt>
ForwardIt LoopIterator(Container& container, ForwardIt pos) {
  return pos == container.end() ? container.begin() : pos;
}

template <typename RandomIt>
void MakeJosephusPermutationAuthors(RandomIt first, RandomIt last,
                             uint32_t step_size) {
  list<typename RandomIt::value_type> pool;
  for (auto it = first; it != last; ++it) {
    pool.push_back(move(*it));
  }
  auto cur_pos = pool.begin();
  while (!pool.empty()) {
    *(first++) = move(*cur_pos);
    if (pool.size() == 1) {
      break;
    }
    const auto next_pos = LoopIterator(pool, next(cur_pos));
    pool.erase(cur_pos);
    cur_pos = next_pos;
    for (uint32_t step_index = 1; step_index < step_size; ++step_index) {
      cur_pos = LoopIterator(pool, next(cur_pos));
    }
  }
}

#endif //RED_BELT_C___JOSEPHUSPERMUTATION_H
