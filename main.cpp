#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include "test_runner.h"

using namespace std;

template <typename T> void Swap(T* first, T* second) {
  T value = *first;
  *first = *second;
  *second = value;
}

template <typename T> void SortPointers(vector<T*>& pointers) {
  sort(pointers.begin(), pointers.end(), [](T* elemFirst, T* elemSecond) -> bool {
    return *elemFirst < *elemSecond;
  });
}

template <typename T> void ReversedCopy(T* src, size_t count, T* dst) {
  bool overlap = false;
  size_t counter_left;
  for (counter_left = 0; counter_left < count; counter_left++) {
    if (src == dst) {
      overlap = true;
      break;
    }
    src++;
  }
  src -= counter_left;


  if (!overlap) {
    for (int i = 0; i < count; i++) {
      dst[i] = src[i];
    }

    for (int i = 0; i < count / 2; i++) {
      Swap(dst + i, dst + count - i - 1);
    }


  } else {

    /*T* copy = new T[count];

    for (int i = 0; i < count; i++) {
      copy[i] = src[i];
    }*/

/*

    for (size_t i = counter_left; i < counter_left + (count - counter_left) / 2; i++) {
      Swap(src + i, src + counter_left + (count - counter_left) / 2 - i - 1);
    }
*/

   /* delete[] copy;*/
  }

}

void TestSwap() {
  int a = 1;
  int b = 2;
  Swap(&a, &b);
  ASSERT_EQUAL(a, 2);
  ASSERT_EQUAL(b, 1);

  string h = "world";
  string w = "hello";
  Swap(&h, &w);
  ASSERT_EQUAL(h, "hello");
  ASSERT_EQUAL(w, "world");
}

void TestSortPointers() {
  int one = 1;
  int two = 2;
  int three = 3;

  vector<int*> pointers;
  pointers.push_back(&two);
  pointers.push_back(&three);
  pointers.push_back(&one);

  SortPointers(pointers);

  ASSERT_EQUAL(pointers.size(), 3u);
  ASSERT_EQUAL(*pointers[0], 1);
  ASSERT_EQUAL(*pointers[1], 2);
  ASSERT_EQUAL(*pointers[2], 3);
}

void TestReverseCopy() {
  const size_t count = 7;

  int* source = new int[count];
  int* dest = new int[count];

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  ReversedCopy(source, count, dest);
  const vector<int> expected1 = {7, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(dest, dest + count), expected1);

  // Области памяти могут перекрываться
  ReversedCopy(source, count - 1, source + 1);
  const vector<int> expected2 = {1, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(source, source + count), expected2);

  delete[] dest;
  delete[] source;
}

void TestReverseCopy2() {
  const size_t count = 5;
  const size_t count2 = 5;

  int* source = new int[count]{1, 2, 3, 4, 5 };
  int* dest = new int[count2]{ 6, 7, 8, 9, 10};

  ReversedCopy(source, 4, dest);

  const vector<int> expected = {4, 3, 2, 1, 10};
  ASSERT_EQUAL(vector<int>(dest, dest + count2), expected);

  delete[] dest;
  delete[] source;
}


void TestReverseCopy3() {
  const size_t count = 10;
  const size_t count2 = 5;

  int* source = new int[count]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  int* dest = new int[count]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  ReversedCopy(source, count2, dest);

  const vector<int> expected = {5, 4, 3, 2, 1, 6, 7, 8, 9, 10};
  ASSERT_EQUAL(vector<int>(dest, dest + count), expected);

  delete[] dest;
  delete[] source;
}

void TestReverseCopy4() {
  const size_t count = 10;
  const size_t count2 = 3;

  int* source = new int[count]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  int* dest = source + count2;

  ReversedCopy(source, 5, dest);

  const vector<int> expected = {5, 4, 3, 2, 1, 9, 10};
  ASSERT_EQUAL(vector<int>(dest, dest + 7), expected);

  delete[] dest;
  delete[] source;
}


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSwap);
  RUN_TEST(tr, TestSortPointers);
  RUN_TEST(tr, TestReverseCopy);
  RUN_TEST(tr, TestReverseCopy2);
  RUN_TEST(tr, TestReverseCopy3);
  //RUN_TEST(tr, TestReverseCopy4);
  return 0;
}