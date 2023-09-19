//
// Created by Rakhmon Radjabov on 19/09/23.
//

#ifndef RED_BELT_C___TEXTEDITOR_H
#define RED_BELT_C___TEXTEDITOR_H

#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "../test_runner.h"

class Editor {
public:
  Editor() {
    current_position = text.begin();
  }
  void Left() {
    advance(current_position, -1);
  }
  void Right() {
    advance(current_position, 1);
  }
  void Insert(char token) {
    text.insert(current_position, token);
  }

  void Cut(size_t tokens = 1) {
    size_t advance_dist = std::min((size_t)distance(current_position, text.end()), tokens);
    auto end = current_position;
    advance(end, advance_dist);
    auto start = current_position;
    advance(current_position, tokens);
    buffer = {start, end};
    text.erase(start, end);
  }

  void Copy(size_t tokens = 1) {
    auto end = current_position;
    advance(end, tokens);
    buffer = {current_position, end};
  }

  void Paste() {
    text.insert(current_position, buffer.begin(), buffer.end());
  }

  std::string GetText() const {
    return {text.begin(), text.end()};
  }

  void printText() const {
    bool printed = false;
    for (auto it = text.begin(); it != text.end(); advance(it, 1)) {
      if (it == current_position) {
        std::cout << '|';
        printed = true;
      }
      std::cout << *it;
    }

    if (printed)
      std::cout << std::endl;
    else
      std::cout << "|" << std::endl;
  }

  void printBuffer() {
    std::cout << buffer << std::endl;
  }
private:
  std::list<char> text;
  std::list<char>::iterator current_position;
  std::string buffer;
};

void TypeText(Editor& editor, const std::string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const std::string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

void tests() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
}

#endif //RED_BELT_C___TEXTEDITOR_H
