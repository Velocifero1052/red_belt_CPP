//#include "test_runner.h"
//#include "airline_ticket.h"
//#include "test_runner.h"
#include <vector>
#include <iostream>

using namespace std;

template<typename T>
class Deque {
public:
    Deque() {
    }
    bool Empty() const {
        return begin.empty() && end.empty();
    }
    size_t Size() const {
        return begin.size() + end.size();
    };
    T& operator[](size_t index) {
        if (begin.size() > index) {
            return begin[begin.size() - index - 1];
        } else if (end.size() > index) {
            return end[index];
        } else if (Size() > index) {
            return end[index - begin.size()];
        }
    };
    const T& operator[](size_t index) const {
        if (begin.size() > index) {
            return begin[begin.size() - index - 1];
        } else if (end.size() > index) {
            return end[index];
        } else if (Size() > index) {
            return end[index - begin.size()];
        }
    };
    void PushFront(const T& elem) {
        begin.push_back(elem);
    }
    void PushBack(const T& elem) {
        end.push_back(elem);
    }

private:
    vector<T> begin;
    vector<T> end;
};

int main() {
    {
        Deque<int> dq;
        dq.PushFront(1);
        dq.PushFront(2);
        dq.PushFront(3);
        size_t i = 0;
        cout << dq[i] << endl;
    }
    {
        Deque<int> dq;
        dq.PushBack(1);
        dq.PushBack(2);
        dq.PushBack(3);
        size_t i = 0;
        cout << dq[i] << endl;
    }
    {
        Deque<int> dq;
        dq.PushFront(1);
        dq.PushFront(2);
        dq.PushFront(3);
        dq.PushBack(4);
        dq.PushBack(5);
        size_t i = 3;
        cout << dq[i] << endl;
    }
    {
        cout << "######################" << endl;
        Deque<int> dq;
        dq.PushFront(1);
        dq.PushFront(2);
        dq.PushFront(3);
        dq.PushBack(4);
        dq.PushBack(5);
        for(size_t i = 0; i < dq.Size(); i++) {
            cout << dq[i] << " ";
        }
        cout << "######################" << endl;
    }

    return 0;
}

