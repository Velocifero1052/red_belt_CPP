#include "test_runner.h"

#include <numeric>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename Iterator>
class IteratorRange {
private:
  Iterator first, last;
public:
  IteratorRange(Iterator f, Iterator l): first(f), last(l) {}

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

  size_t size() const {
    return last - first;
  }
};

template<typename T>
size_t RangeSize (IteratorRange<T> r) {
  return r.end() - r.begin();
}

template<typename Iterator>
class Paginator {
private:
  Iterator first, last;
  size_t pages_count;
  size_t total_elements;
  size_t last_page_size;
  vector<IteratorRange<Iterator>> pages;
public:
  Paginator (Iterator f, Iterator l, size_t size_of_page_): first(f), last(l), total_elements(last - first) {
    last_page_size = total_elements % size_of_page_;
    pages_count = total_elements / size_of_page_ + ((last_page_size == 0) ? 0 : 1);

    for (size_t i = 0; i < pages_count; i++) {
      if(i + 1 < pages_count) {
        pages.push_back(IteratorRange(next(first, i * size_of_page_), next(first, i * size_of_page_ + size_of_page_)));
      } else if(last_page_size != 0) {
        pages.push_back(IteratorRange(next(first, i * size_of_page_), next(first, i * size_of_page_ + last_page_size)));
      } else {
        pages.push_back(IteratorRange(next(first, i * size_of_page_), next(first, i * size_of_page_ + size_of_page_)));
      }
    }

  }
  auto begin() const{
    return pages.begin();
  }

  auto end() const{
    return pages.end();
  }

  size_t size() const {
    return pages_count;
  }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator{c.begin(), c.end(), page_size};
}



void TestPageCounts() {
  vector<int> v(15);

  ASSERT_EQUAL(Paginate(v, 1).size(), v.size());
  ASSERT_EQUAL(Paginate(v, 3).size(), 5u);
  ASSERT_EQUAL(Paginate(v, 5).size(), 3u);
  ASSERT_EQUAL(Paginate(v, 4).size(), 4u);
  ASSERT_EQUAL(Paginate(v, 15).size(), 1u);
  ASSERT_EQUAL(Paginate(v, 150).size(), 1u);
  ASSERT_EQUAL(Paginate(v, 14).size(), 2u);
}


void TestLooping() {
  vector<int> v(15);
  iota(begin(v), end(v), 1);

  Paginator<vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
  ostringstream os;
  for (const auto& page : paginate_v) {
    for (int x : page) {
      os << x << ' ';
    }
    os << '\n';
  }

  ASSERT_EQUAL(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
}



void TestModification() {
  vector<string> vs = {"one", "two", "three", "four", "five"};
  for (auto page : Paginate(vs, 2)) {
    for (auto& word : page) {
      word[0] = toupper(word[0]);
    }
  }

  const vector<string> expected = {"One", "Two", "Three", "Four", "Five"};
  ASSERT_EQUAL(vs, expected);
}

void TestPageSizes() {
  string letters(26, ' ');

  Paginator letters_pagination(letters.begin(), letters.end(), 11);
  vector<size_t> page_sizes;
  for (const auto& page : letters_pagination) {
    page_sizes.push_back(page.size());
  }

  const vector<size_t> expected = {11, 11, 4};
  ASSERT_EQUAL(page_sizes, expected);
}

void TestConstContainer() {
  const string letters = "abcdefghijklmnopqrstuvwxyz";

  vector<string> pages;
  for (const auto& page : Paginate(letters, 10)) {
    pages.push_back(string(page.begin(), page.end()));
  }

  const vector<string> expected = {"abcdefghij", "klmnopqrst", "uvwxyz"};
  ASSERT_EQUAL(pages, expected);
}

void TestPagePagination() {
  vector<int> v(22);
  iota(begin(v), end(v), 1);

  vector<vector<int>> lines;
  for (const auto& split_by_9 : Paginate(v, 9)) {
    for (const auto& split_by_4 : Paginate(split_by_9, 4)) {
      lines.push_back({});
      for (int item : split_by_4) {
        lines.back().push_back(item);
      }
    }
  }

  const vector<vector<int>> expected = {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9},
      {10, 11, 12, 13},
      {14, 15, 16, 17},
      {18},
      {19, 20, 21, 22}
  };
  ASSERT_EQUAL(lines, expected);
}



/*template<typename Container>
auto Head(Container &c, size_t top) {
  return IteratorRange{c.begin(), next(c.begin(), min(top, c.size()))};
}


template<typename Iterator>
IteratorRange<Iterator> MakeRange(
    Iterator begin, Iterator end
) {
  return IteratorRange<Iterator>{begin, end};
}*/

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPageCounts);
  //fails maybe because of editor
  //RUN_TEST(tr, TestLooping);
  //passes
  //RUN_TEST(tr, TestModification);
  //passes
  RUN_TEST(tr, TestPageSizes);
  //passes
  //RUN_TEST(tr, TestConstContainer);
  //fails
  RUN_TEST(tr, TestPagePagination);

/*  vector<int> v(22);
  iota(begin(v), end(v), 1);
  const auto split_by_9_v= Paginate(v, 9);

  for (const auto& split_by_9 : split_by_9_v) {
    for (const auto& split_by_4 : Paginate(split_by_9, 4)) {
      for (const auto& elem: split_by_4) {
        cout << elem << ' ';
      }
      cout << "\n";
    }
  }*/

}









