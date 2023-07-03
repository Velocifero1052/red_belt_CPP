#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>

using namespace std;

class ReadingManager {
public:

  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        sorted_users_(),
        user_positions_(MAX_USER_COUNT_ + 1, -1) {}

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

private:

  static const int MAX_USER_COUNT_ = 100'000;

  vector<int> user_page_counts_;
  vector<int> sorted_users_;
  vector<int> user_positions_;

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

class ReadingManager2 {
public:
  ReadingManager2() {
    users.resize(MAX_USER_COUNT, 0);
    pages.resize(MAX_PAGES_COUNT, 0);
    user_count = 0;
  }

  void Read(int user_id, int page_count) {
    user_id--;

    if (users[user_id] == 0) {
      user_count++;
    } else {
      int prev_page = users[user_id];
      pages[prev_page - 1]--;
    }

    users[user_id] = page_count;
    pages[page_count - 1]++;
  }
  void print_pages(int number_of_pages = 10) {
    for (int i = 0; i < number_of_pages; i++) {
      cout << pages[i] << " ";
    }
    cout << endl;
  }

  double Cheer(int user_id) const {
    user_id--;
    if (user_count == 1 && users[user_id] != 0) {
      return 1;
    }

    if (users[user_id] == 0) {
      return 0;
    }

    int accum = 0;
    for (auto it = pages.begin(); it != pages.begin() + users[user_id] - 1; it++) {
      accum += *it;
    }
   // accumulate(pages.begin(), pages.begin() + users[user_id], accum);

    cout << "#########################" << endl;
    cout << "Users curr page: " << users[user_id] << endl;
    cout << "Accumulated " << accum << endl;
    cout << "#########################" << endl;

    return accum * 1.0 / user_count;
  }



private:
  static const int MAX_USER_COUNT = 100'000;
  static const int MAX_PAGES_COUNT = 1'000;
  int user_count{};
  vector<int> users;
  vector<int> pages;
};

int main() {

  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;
  ReadingManager2 manager2;

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
      manager2.Read(user_id, page_count);
      manager2.print_pages();
    } else if (query_type == "CHEER") {
      //cout << setprecision(6) << manager.Cheer(user_id) << "\n";
      cout << setprecision(6) << manager2.Cheer(user_id) << '\n';
    }
  }

  return 0;
}