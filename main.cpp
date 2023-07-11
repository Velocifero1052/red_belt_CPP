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
  bool left_overlap = false, right_overlap = false;
  size_t counter_left;

  for (counter_left = 0; counter_left < count; counter_left++) {
    if (src == dst) {
      left_overlap = true;
      break;
    }
    src++;
  }

  src -= counter_left;

  if (!left_overlap) {
    for (counter_left = 0; counter_left < count; counter_left++) {
      if (dst == src) {
        right_overlap = true;
        break;
      }
      dst++;
    }
    dst -= counter_left;
  }


  if (!left_overlap && !right_overlap) {
    for (int i = 0; i < count; i++) {
      dst[i] = src[count - i - 1];
    }

  } else if (left_overlap) {

    size_t counter_right = count - counter_left;

    for (size_t i = 0; i < counter_right / 2; i++) {
      Swap(dst + i, dst + counter_right - i - 1);
    }

    for (size_t i = 0; i < counter_left; i++) {
      dst[count - i - 1] = src[i];
    }

  } else {
    cout << "##################" << endl;

    size_t counter_right = count - counter_left;

    for (size_t i = 0; i < counter_right / 2; i++) {
      Swap(src + i, src + counter_right - i - 1);
    }

    for (size_t i = 0; i < counter_left; i++) {
      dst[count - i - 1] = src[i];
    }
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

void TestReverseCopy2NO() {
  const size_t count = 7;

  int* source = new int[count];
  int* dest = new int[count]{0,0,0,0,0, 0, 0};

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  ReversedCopy(source, 3, dest);
  const vector<int> expected1 = {3, 2, 1, 0, 0, 0, 0};
  ASSERT_EQUAL(vector<int>(dest, dest + count), expected1);


  delete[] dest;
  delete[] source;
}

void TestReverseCopy3NO() {
  const size_t count = 7;
  const size_t copy_count = 3;

  int* source = new int[count];
  int* dest = new int[copy_count];

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  ReversedCopy(source, copy_count, dest);

  const vector<int> expected1 = { 3, 2, 1 };
  auto actual = vector<int>(dest, dest + copy_count);
  ASSERT_EQUAL(actual, expected1);

  delete[] dest;
  delete[] source;
}

void TestReverseCopy4NO() {
  const size_t count = 7;
  const size_t copy_count = 0;

  int* source = new int[count];
  int* dest = new int[copy_count];

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  ReversedCopy(source, copy_count, dest);

  const vector<int> expected1 = {  };
  auto actual = vector<int>(dest, dest + copy_count);
  ASSERT_EQUAL(actual, expected1);

  delete[] dest;
  delete[] source;
}

void TestReverseCopy5NO() {
  const size_t count = 7;
  const size_t copy_count = 5;

  int* source = new int[count];
  int* dest = new int[copy_count];

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  ReversedCopy(source, copy_count, dest);

  const vector<int> expected1 = { 5, 4, 3, 2, 1 };
  auto actual = vector<int>(dest, dest + copy_count);
  ASSERT_EQUAL(actual, expected1);

  delete[] dest;
  delete[] source;
}

void TestReverseCopy6Overlap() {
  const size_t count = 7;
  const size_t copy_count = 5;

  int* source = new int[count];
  int* dest = source + 2;

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  ReversedCopy(source, copy_count, dest);

  const vector<int> expected1 = { 5, 4, 3, 2, 1 };
  auto actual = vector<int>(dest, dest + copy_count);
  ASSERT_EQUAL(actual, expected1);

  //delete[] dest;
  delete[] source;
}

void TestReverseCopy7Overlap() {
  const size_t count = 7;
  const size_t copy_count = 6;

  int* source = new int[count];
  int* dest = source + 1;

  //[1, 2, 3, 4, 5, 6, 7]
  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  ReversedCopy(source, copy_count, dest);

  const vector<int> expected1 = { 6, 5, 4, 3, 2, 1 };
  auto actual = vector<int>(dest, dest + copy_count);
  ASSERT_EQUAL(actual, expected1);

  //delete[] dest;
  delete[] source;
}

void TestReverseCopy8Overlap() {
  const size_t count = 7;
  const size_t copy_count = 2;

  int* source = new int[count];
  int* dest = source;

  //[1,2,3,4,5,6,7]
  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  source += 2;

  ReversedCopy(source, copy_count, dest);

  const vector<int> expected1 = { 4, 3, 3, 4, 5, 6, 7 };
  auto actual = vector<int>(dest, dest + count);
  ASSERT_EQUAL(actual, expected1);

  //delete[] dest;
  delete[] dest;
}

void TestReverseCopy9Overlap() {
  const size_t count = 7;
  const size_t copy_count = 3;

  int* source = new int[count];
  int* dest = source + 1;

  //[1, 2, 3, 4, 5, 6, 7]
  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  source += 4;

  ReversedCopy(source, copy_count, dest);

  const vector<int> expected1 = { 1, 7, 6, 5, 5, 6, 7 };
  dest--;
  auto actual = vector<int>(dest, dest + count);
  ASSERT_EQUAL(actual, expected1);

  delete[] dest;
}

void TestReverseCopy10Overlap() {
  const size_t count = 10;
  const size_t copy_count = 4;

  int* source = new int[count];
  int* dest = source;

  //[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  //[4, 5, 6, 7, 8, 9, 10]
  source += 3;

  for (int i = 0; i < count - 3; i++) {
    cout << source[i] << " ";
  }
  cout << endl;

  //should be [7, 6, 5, 4, 5, 6, 7, 8, 9, 10]
  ReversedCopy(source, copy_count, dest);

  const vector<int> expected1 = { 7, 6, 5, 4, 5, 6, 7, 8, 9, 10 };

  auto actual = vector<int>(dest, dest + count);
  ASSERT_EQUAL(actual, expected1);

  delete[] dest;
}

int main() {
  TestRunner tr;
  //standard
  RUN_TEST(tr, TestSwap);
  RUN_TEST(tr, TestSortPointers);
  RUN_TEST(tr, TestReverseCopy);
  //no overlapping tests
  RUN_TEST(tr, TestReverseCopy2NO);
  RUN_TEST(tr, TestReverseCopy3NO);
  RUN_TEST(tr, TestReverseCopy4NO);
  RUN_TEST(tr, TestReverseCopy5NO);
  //overlapping tests
  RUN_TEST(tr, TestReverseCopy6Overlap);
  RUN_TEST(tr, TestReverseCopy7Overlap);
  RUN_TEST(tr, TestReverseCopy8Overlap);
  RUN_TEST(tr, TestReverseCopy9Overlap);
  RUN_TEST(tr, TestReverseCopy10Overlap);
  return 0;
}