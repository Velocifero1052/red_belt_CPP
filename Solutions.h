//
// Created by Rakhmon Radjabov on 06/06/23.
//

#ifndef RED_BELT_C___SOLUTIONS_H
#define RED_BELT_C___SOLUTIONS_H

#include "test_runner.h"

#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>
#include <iterator>
#include <algorithm>

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

void TestUniqueMax() {
    auto IsEven = [](int x) {
        return x % 2 == 0;
    };

    const std::list<int> hill{2, 4, 8, 9, 6, 4, 2};
    auto max_iterator = hill.begin();
    advance(max_iterator, 2);

    std::vector<int> numbers(10);
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

#endif //RED_BELT_C___SOLUTIONS_H
