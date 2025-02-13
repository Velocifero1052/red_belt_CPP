//
// Created by Rakhmon Radjabov on 21/07/23.
//

#ifndef RED_BELT_C___LINKED_LIST_H
#define RED_BELT_C___LINKED_LIST_H
#include <vector>
#include "../test_runner.h"

template <typename T>
class LinkedList {
public:
  struct Node {
    T value;
    Node* next = nullptr;
  };

  ~LinkedList() {
    Node *current = head;

    while (current != nullptr) {
      Node* new_current = current->next;
      delete current;
      current = new_current;
    }

  }

  void PushFront(const T& value) {
    Node* new_head = new Node;
    new_head->next = head;
    new_head->value = value;
    head = new_head;
  }

  void InsertAfter(Node* node, const T& value) {
    if (node == nullptr) PushFront(value);
    else {
      Node* new_node = new Node;
      new_node->value = value;
      Node* prev_next = node->next;
      node->next = new_node;
      new_node->next = prev_next;
    }
  }

  void RemoveAfter(Node* node) {
    if (node == nullptr) PopFront();
    else if (node->next != nullptr){
      Node* prev_next = node->next;
      Node* new_next = node->next->next;
      delete prev_next;
      node->next = new_next;
    }
  }

  void PopFront() {
    if (head != nullptr) {
      Node* new_head = head->next;
      delete head;
      head = new_head;
    }
  }

  Node* GetHead() { return head; }

  const Node* GetHead() const { return head; }

private:
  Node* head = nullptr;
};

template <typename T>
std::vector<T> ToVector(const LinkedList<T>& list) {
  std::vector<T> result;
  for (auto node = list.GetHead(); node; node = node->next) {
    result.push_back(node->value);
  }
  return result;
}

void TestPushFront() {
  LinkedList<int> list;

  list.PushFront(1);
  ASSERT_EQUAL(list.GetHead()->value, 1);
  list.PushFront(2);
  ASSERT_EQUAL(list.GetHead()->value, 2);
  list.PushFront(3);
  ASSERT_EQUAL(list.GetHead()->value, 3);

  const vector<int> expected = {3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
  LinkedList<string> list;

  list.PushFront("a");
  auto head = list.GetHead();
  ASSERT(head);
  ASSERT_EQUAL(head->value, "a");

  list.InsertAfter(head, "b");
  const vector<string> expected1 = {"a", "b"};
  ASSERT_EQUAL(ToVector(list), expected1);

  list.InsertAfter(head, "c");
  const vector<string> expected2 = {"a", "c", "b"};
  ASSERT_EQUAL(ToVector(list), expected2);
}

void TestRemoveAfter() {
  LinkedList<int> list;
  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }

  const vector<int> expected = {5, 4, 3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);

  auto next_to_head = list.GetHead()->next;
  list.RemoveAfter(next_to_head); // удаляем 3
  list.RemoveAfter(next_to_head); // удаляем 2

  const vector<int> expected1 = {5, 4, 1};
  ASSERT_EQUAL(ToVector(list), expected1);

  while (list.GetHead()->next) {
    list.RemoveAfter(list.GetHead());
  }
  ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront() {
  LinkedList<int> list;

  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }
  for (int i = 1; i <= 5; ++i) {
    list.PopFront();
  }
  ASSERT(list.GetHead() == nullptr);
}


#endif //RED_BELT_C___LINKED_LIST_H
