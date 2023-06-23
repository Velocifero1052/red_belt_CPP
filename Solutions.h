//
// Created by Rakhmon Radjabov on 06/06/23.
//

#ifndef RED_BELT_C___SOLUTIONS_H
#define RED_BELT_C___SOLUTIONS_H

#include "test_runner.h"
#include "student.h"
#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <random>

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(1.0, 10.0);

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {

    auto max = find_if(first, last, pred);
    if (max == last) {
        return last;
    }

    auto curr_position = max;

    while (-1) {
        advance(curr_position, 1);
        auto res = find_if(curr_position, last, pred);

        if (res == last) {
            break;
        } else {
            if (*res > *max) {
                max = res;
            }
        }
    }

    return max;
}

template <class ForwardIterator, class UnaryPredicate>
ForwardIterator max_element_if_authors(ForwardIterator first, ForwardIterator last, UnaryPredicate p) {
    ForwardIterator maxElemIt = find_if(first, last, p);
    for (ForwardIterator cur = maxElemIt; cur != last; ++cur) {
        // cur != maxElemIt is checked to avoid re-calculation of p(*maxElemIt) at first iteration
        if (cur != maxElemIt && p(*cur) && *maxElemIt < *cur) {
            maxElemIt = cur;
        }
    }
    return maxElemIt;
}

void TestUniqueMax() {
    auto IsEven = [](int x) {
        return x % 2 == 0;
    };

    const list<int> hill{2, 4, 8, 9, 6, 4, 2};
    auto max_iterator = hill.begin();
    advance(max_iterator, 2);

    vector<int> numbers(10);
    iota(numbers.begin(), numbers.end(), 1);

    Assert(
            max_element_if(numbers.begin(), numbers.end(), IsEven) == --numbers.end(),
            "Expect the last element"
    );
    Assert(
            max_element_if(hill.begin(), hill.end(), IsEven) == max_iterator,
            "Expect the maximal even number"
    );
}

void TestSeveralMax() {
    struct IsCapitalized {
        bool operator()(const string &s) {
            return !s.empty() && isupper(s.front());
        }
    };

    const forward_list<string> text{"One", "two", "Three", "One", "Two",
                                    "Three", "one", "Two", "three"};
    auto max_iterator = text.begin();
    advance(max_iterator, 4);

    Assert(
            max_element_if(text.begin(), text.end(), IsCapitalized()) == max_iterator,
            "Expect thr first \"Two\""
    );
}

void TestNoMax() {
    const vector<int> empty;
    const string str = "Non-empty string";

    auto AlwaysTrue = [](int) {
        return true;
    };
    Assert(
            max_element_if(empty.begin(), empty.end(), AlwaysTrue) == empty.end(),
            "Expect end for empty container"
    );

    auto AlwaysFalse = [](char) {
        return false;
    };
    Assert(
            max_element_if(str.begin(), str.end(), AlwaysFalse) == str.end(),
            "Expect end for AlwaysFalse predicate"
    );
}

void test_max_by_predicate() {
    TestRunner tr;
    tr.RunTest(TestUniqueMax, "TestUniqueMax");
    tr.RunTest(TestSeveralMax, "TestSeveralMax");
    tr.RunTest(TestNoMax, "TestNoMax");
}

#define PRINT_VALUES(out, x, y) out << (x) << '\n' << (y) << '\n'

void print_values_tests() {
    TestRunner tr;
    tr.RunTest([] {
        ostringstream output;
        PRINT_VALUES(output, 5, "red belt");
        ASSERT_EQUAL(output.str(), "5\nred belt\n");
    }, "PRINT_VALUES usage example");
}

#define CONCAT(b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a ## b

#define UNIQ_ID CONCAT(__LINE__)


struct Substring {
    string& s;
    size_t first, last;

    char& operator[](size_t index) {
        return s[first + index];
    }

    const char& operator[](size_t index) const {
        return s[first + index];
    }

    size_t size() const {
        return last - first;
    }
    string::iterator begin() { return s.begin() + first; } string::iterator end() { return s.begin() + last; }
};

void test_method() {
    string three_words = "c++ red belt";
    Substring second_word{three_words, 4, 7};

    for (char& letter : second_word) {
        letter = toupper(letter);
    }
}

template<typename T>
class Table {
public:
    Table(size_t n_, size_t m_) {
        Resize(n_, m_);
    }
    vector<T> operator[](size_t index) const {
        return table[index];
    }

    vector<T>& operator[](size_t index) {
        return table[index];
    }
    void Resize(size_t n_, size_t m_) {
        table.resize(n_);
        for (int i = 0; i < n_; i++) {
            table[i].resize(m_);
        }
        n = n_;
        m = m_;
    }
    pair<size_t, size_t> Size() const {
        return make_pair(this->n, this->m);
    }
private:
    vector<vector<T>> table;
    size_t n, m;
};


char get_rand_char() {
  static string charset("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
  return charset[rand() % charset.size()];
}


string generate_random_string(size_t n) {
  char rbuf[n];
  generate(rbuf, rbuf+n, &get_rand_char);
  return string(rbuf, n);
}


bool Compare(const Student& first, const Student& second) {
  return first.Less(second);
}


Student generate_student() {
  double algorithms_mark =  dis(gen);
  double cpp_mark =  dis(gen);

  Student s;
  s.first_name = generate_random_string(100);
  s.last_name = generate_random_string(150);
  s.marks = {{"c++", cpp_mark}, {"algorithms", algorithms_mark}};
  s.rating = (algorithms_mark + cpp_mark) / 2.0;

  return s;
}


vector<Student> generate_students(int num) {
  vector<Student> students(num);

  for (int i = 0; i < num; i++) {
    students.push_back(generate_student());
  }

  return students;
}

#endif //RED_BELT_C___SOLUTIONS_H
