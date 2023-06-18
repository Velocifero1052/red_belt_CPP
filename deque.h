//
// Created by comme on 6/18/2023.
//

#ifndef RED_BELT_C___DEQUE_H
#define RED_BELT_C___DEQUE_H

#include <vector>
#include <stdexcept>

using namespace std;

template<typename T>
class Deque {
    vector<T> front;
    vector<T> back;
public:
    Deque() {
    };
    bool Empty() const {
        return front.empty() && back.empty();
    }
    size_t Size() const {
        return front.size() + back.size();
    }
    T& operator[](size_t index) {
        if (index < front.size()) {
            return front[front.size() - 1 - index];
        }
        return back[index - front.size()];
    }
    const T& operator[](size_t index) const {
        if (index < front.size()) {
            return front[front.size() - 1 - index];
        }
        return back[index - front.size()];
    }
    const T& At(size_t index) const {
        if (index >= Size()) {
            throw out_of_range("out of range");
        }
        return operator[](index);
    }
    T& At(size_t index) {
        if (index >= Size()) {
            throw out_of_range("out of range");
        }
        return operator[](index);
    }
    const T& Front() const {
        if (front.empty()) {
            return back.front();
        }
        return front.back();
    }
    T& Front() {
        if (front.empty()) {
            return back.front();
        }
        return front.back();
    }
    const T& Back() const {
        if (back.empty()) {
            return front.front();
        }
        return back.back();
    }
    T& Back() {
        if (back.empty()) {
            return front.front();
        }
        return back.back();
    }
    void PushFront(const T& v) {
        front.push_back(v);
    }
    void PushBack(const T& v) {
        back.push_back(v);
    }
};

void deque_tests() {
    {
        Deque<int> d;
        ASSERT(d.Empty());
        d.PushFront(10);
        ASSERT(!d.Empty());
        ASSERT_EQUAL(d.Size(), 1);
    }
    {
        Deque<int> d;
        ASSERT(d.Empty());
        d.PushBack(10);
        ASSERT(!d.Empty());
        ASSERT_EQUAL(d.Size(), 1);
    }
    {
        Deque<int> d;
        const int SIZE = 10;
        for (int i = 0; i < SIZE; i++) {
            d.PushFront(SIZE - i - 1);
        }
        for (int i = 0; i < SIZE; i++) {
            ASSERT_EQUAL(i, d[i]);
        }
    }
    {
        Deque<int> d;
        const int SIZE = 10;
        for (int i = 0; i < SIZE; i++) {
            d.PushBack(i);
        }
        for(int i = 0; i < SIZE; i++) {
            ASSERT_EQUAL(i, d[i]);
        }
    }
    {
        Deque<int> d;
        const int SIZE = 10;
        for (int i = 0; i < SIZE; i++) {
            d.PushBack(i);
        }
        for(int i = 0; i < SIZE; i++) {
            d[i]++;
        }
        for(int i = 0; i < SIZE; i++) {
            ASSERT_EQUAL(i + 1, d[i]);
        }
    }
    {
        Deque<int> d;
        const int SIZE = 10;
        for (int i = 0; i < SIZE; i++) {
            d.PushFront(SIZE - i - 1);
        }
        for (int i = 0; i < SIZE; i++) {
            ASSERT_EQUAL(i, d.At(i));
        }
    }
    {
        Deque<int> d;
        const int SIZE = 10;
        for (int i = 0; i < SIZE; i++) {
            d.PushBack(i);
        }
        for(int i = 0; i < SIZE; i++) {
            d.At(i)++;
        }
        for(int i = 0; i < SIZE; i++) {
            ASSERT_EQUAL(i + 1, d[i]);
        }
    }
    {
        Deque<int> d;
        const int SIZE = 10;
        for (int i = 0; i < SIZE; i++) {
            d.PushFront(SIZE - i - 1);
        }

        ASSERT_EQUAL(0, d.Front());
        ASSERT_EQUAL(9, d.Back());
        d.Front() = 100;
        ASSERT_EQUAL(100, d.Front());
        d.Back() = 101;
        ASSERT_EQUAL(101, d.Back());
    }
    {
        Deque<int> d;
        const int SIZE = 10;
        for (int i = 0; i < SIZE; i++) {
            d.PushBack(i);
        }

        ASSERT_EQUAL(0, d.Front());
        ASSERT_EQUAL(9, d.Back());
        d.Front() = 100;
        ASSERT_EQUAL(100, d.Front());
        d.Back() = 101;
        ASSERT_EQUAL(101, d.Back());
    }
    {
        Deque<int> d;
        d.PushBack(4);
        d.PushFront(3);
        ASSERT_EQUAL(d[0], 3);
        ASSERT_EQUAL(d[1], 4);
    }
    {
        Deque<int> d;
        d.PushBack(4);
        d.PushFront(3);
        ASSERT_EQUAL(d.At(0), 3);
        ASSERT_EQUAL(d.At(1), 4);
    }
    {
        Deque<int> d;
        d.PushBack(4);
        d.PushFront(3);
        d.PushFront(2);
        d.PushFront(1);
        ASSERT_EQUAL(d.At(0), 1);
        ASSERT_EQUAL(d.At(1), 2);
        ASSERT_EQUAL(d.At(2), 3);
        ASSERT_EQUAL(d.At(3), 4);
    }
    {
        Deque<int> d;
        d.PushFront(4);
        d.PushBack(3);
        d.PushFront(2);
        d.PushBack(1);
        ASSERT_EQUAL(d.At(0), 2);
        ASSERT_EQUAL(d.At(1), 4);
        ASSERT_EQUAL(d.At(2), 3);
        ASSERT_EQUAL(d.At(3), 1);
        ASSERT_EQUAL(d.Front(), 2);
        ASSERT_EQUAL(d.Back(), 1);
    }
    {
        Deque<int> d;
        d.PushFront(3);
        d.PushFront(2);
        d.PushFront(1);
        ASSERT_EQUAL(d.Back(), 3);
        ASSERT_EQUAL(d.Front(), 1);
        for (int i = 0; i < 3; i++) {
            ASSERT_EQUAL(d.At(i), i + 1);
        }
    }
    {
        Deque<int> d;
        d.PushBack(1);
        d.PushBack(2);
        d.PushBack(3);
        ASSERT_EQUAL(d.Back(), 3);
        ASSERT_EQUAL(d.Front(), 1);
        for (int i = 0; i < 3; i++) {
            ASSERT_EQUAL(d.At(i), i + 1);
        }
    }
    {

    }
}

void test_deque_basic() {
    Deque<int> d;
    ASSERT_EQUAL(d.Size(), 0);
    d.PushFront(1);
    d.PushFront(2);
    d.PushFront(3);

    d.PushBack(10);
    d.PushBack(20);
    d.PushBack(30);

    ASSERT_EQUAL(d.Size(), 6);

    ASSERT_EQUAL(d.Front(), 3);
    ASSERT_EQUAL(d.Back(), 30);

    ASSERT_EQUAL(d[0], 3);
    ASSERT_EQUAL(d[1], 2);
    ASSERT_EQUAL(d[3], 10);
    ASSERT_EQUAL(d[4], 20);

}

void test_deque_advanced() {
    Deque<int> f;

    f.PushFront(1);
    f.PushFront(2);
    f.PushFront(3);

    ASSERT_EQUAL(f.Front(), 3);
    ASSERT_EQUAL(f.Back(), 1);

    Deque<int> b;

    b.PushBack(10);
    b.PushBack(20);
    b.PushBack(30);

    ASSERT_EQUAL(b.Front(), 10);
    ASSERT_EQUAL(b.Back(), 30);

    ASSERT_EQUAL(f[0], 3);
    ASSERT_EQUAL(f[1], 2);
    ASSERT_EQUAL(f[2], 1);

    ASSERT_EQUAL(b[0], 10);
    ASSERT_EQUAL(b[1], 20);
    ASSERT_EQUAL(b[2], 30);
}

void test_modification() {
    Deque<int> d;
    ASSERT_EQUAL(d.Size(), 0);
    d.PushFront(1);
    d.PushFront(2);
    d.PushFront(3);

    d.PushBack(10);
    d.PushBack(20);
    d.PushBack(30);

    ASSERT_EQUAL(d.At(3), 10);
    d[3] = 11;
    ASSERT_EQUAL(d.At(3), 11);
    d[0] = 111;
    ASSERT_EQUAL(d[0], 111);
}



#endif //RED_BELT_C___DEQUE_H
