#include "profile.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

vector<string> SplitIntoWords(const string& text) {
  vector<string> words;

  string current_word;
  for (const char c: text) {
    if (c == ' ')
      words.push_back(move(current_word));
    else
      current_word.push_back(c);
  }
  words.push_back(current_word);
  return words;
}

string ReadTitle() {
  return "Hello world!";
}

uint64_t ReadBigNumber() {
  return 1000'000'000;
}

string ReadFirstName() {
  return "FirstName";
}

string ReadLastName() {
  return "LastName";
}

int main() {
  string first_name = ReadFirstName();
  string last_name = ReadLastName();
  string full_name = first_name + last_name;
  cout << first_name << last_name << endl;
  return 0;
}
