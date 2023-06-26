#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <iomanip>
//#include "test_runner.h"

using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        sorted_users_(),
        user_positions_(MAX_USER_COUNT_ + 1, -1) {
    for (int i = 1; i <= 1000; i++) {
      page_to_users.push_back(0);
    }
  }

  void Read(int user_id, int page_count) {
    if (user_page_counts_[user_id] == 0) {
      AddUser(user_id);
    }
    user_page_counts_[user_id] = page_count;
    int& position = user_positions_[user_id];
    while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
      SwapUsers(position, position - 1);
    }
  }

  void Read2(int user_id, int page_count) {
    int prev_page_number;
    if (user_to_page.count(user_id) == 0) {
      user_to_page[user_id] = page_count;
      prev_page_number = 0;
    } else {
      prev_page_number = user_to_page[user_id];
      user_to_page[user_id] = page_count;
    }

    for (int i = prev_page_number; i < page_count; i++) {
      page_to_users[i]++;
    }

  }

  double Cheer(int user_id) const {
    if (user_page_counts_[user_id] == 0) {
      return 0;
    }
    const int user_count = GetUserCount();
    if (user_count == 1) {
      return 1;
    }
    const int page_count = user_page_counts_[user_id];
    int position = user_positions_[user_id];
    while (position < user_count &&
           user_page_counts_[sorted_users_[position]] == page_count) {
      ++position;
    }
    if (position == user_count) {
      return 0;
    }

    return (user_count - position) * 1.0 / (user_count - 1);
  }

  double Cheer2(int user_id) const {

    if (user_to_page.count(user_id) == 0) {
      return 0;
    }

    if (user_to_page.size() == 1) {
      return 1;
    }

    int current_user_page = user_to_page.at(user_id);
    int users_count = user_to_page.size();
    //int prev_page_read_amount = page_to_users[current_user_page - 1];
    cout << "#######################" << endl;
    cout << current_user_page - 1 << endl;
    cout << "#######################" << endl;
    return (users_count - current_user_page) * 1.0 / (users_count - 1);
  }

  void print_pages(int page_limit) {
    for (int i = 0; i < page_limit; i++) {
      cout << page_to_users[i] << " ";
    }
    cout << endl;
  }


private:

  static const int MAX_USER_COUNT_ = 100'000;

  vector<int> user_page_counts_;
  vector<int> sorted_users_;
  vector<int> user_positions_;
  map<int, int> user_to_page;
  vector<int> page_to_users;

  int GetUserCount() const {
    return sorted_users_.size();
  }

  void AddUser(int user_id) {
    sorted_users_.push_back(user_id);
    user_positions_[user_id] = sorted_users_.size() - 1;
  }

  void SwapUsers(int lhs_position, int rhs_position) {
    const int lhs_id = sorted_users_[lhs_position];
    const int rhs_id = sorted_users_[rhs_position];
    swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
    swap(user_positions_[lhs_id], user_positions_[rhs_id]);
  }
};


int main() {

  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      //manager.Read(user_id, page_count);
      manager.Read2(user_id, page_count);
   //   manager.print_pages(page_count + 5);
    } else if (query_type == "CHEER") {
      //cout << setprecision(6) << manager.Cheer(user_id) << "\n";
      cout << setprecision(6) << manager.Cheer2(user_id) << '\n';
    }
  }

  return 0;
}









