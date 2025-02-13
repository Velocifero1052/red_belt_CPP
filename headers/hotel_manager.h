//
// Created by Rakhmon Radjabov on 07/07/23.
//

#ifndef RED_BELT_C___HOTEL_MANAGER_H
#define RED_BELT_C___HOTEL_MANAGER_H

#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <map>
#include <queue>


class HotelManager {
public:
  void Book(int64_t time, const std::string& hotel_name,
            int client_id, int room_count) {
    current_time_ = time;
    hotels_[hotel_name].Book({time, client_id, room_count});
  }
  int ComputeClientCount(const std::string& hotel_name) {
    return hotels_[hotel_name].ComputeClientCount(current_time_);
  }
  int ComputeRoomCount(const std::string& hotel_name) {
    return hotels_[hotel_name].ComputeRoomCount(current_time_);
  }

private:
  struct Booking {
    int64_t time;
    int client_id;
    int room_count;
  };

  class HotelInfo {
  public:
    void Book(const Booking& booking) {
      last_bookings_.push(booking);
      room_count_ += booking.room_count;
      ++client_booking_counts_[booking.client_id];
    }
    int ComputeClientCount(int64_t current_time) {
      RemoveOldBookings(current_time);
      return client_booking_counts_.size();
    }
    int ComputeRoomCount(int64_t current_time) {
      RemoveOldBookings(current_time);
      return room_count_;
    }
  private:
    static const int TIME_WINDOW_SIZE = 86400;
    std::queue<Booking> last_bookings_;
    int room_count_ = 0;
    std::map<int, int> client_booking_counts_;

    void PopBooking() {
      const Booking& booking = last_bookings_.front();
      room_count_ -= booking.room_count;
      const auto client_stat_it =
          client_booking_counts_.find(booking.client_id);
      if (--client_stat_it->second == 0) {
        client_booking_counts_.erase(client_stat_it);
      }
      last_bookings_.pop();
    }
    void RemoveOldBookings(int64_t current_time) {
      while (
          !last_bookings_.empty()
          && last_bookings_.front().time
             <= current_time - TIME_WINDOW_SIZE
          ) {
        PopBooking();
      }
    }
  };

  int64_t current_time_ = 0;
  std::map<std::string, HotelInfo> hotels_;
};


void test_() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  HotelManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    std::string query_type;
    std::cin >> query_type;

    if (query_type == "BOOK") {
      int64_t time;
      std::cin >> time;
      std::string hotel_name;
      std::cin >> hotel_name;
      int client_id, room_count;
      std::cin >> client_id >> room_count;
      manager.Book(time, hotel_name, client_id, room_count);
    } else {
      std::string hotel_name;
      std::cin >> hotel_name;
      if (query_type == "CLIENTS") {
        std::cout << manager.ComputeClientCount(hotel_name) << "\n";
      } else if (query_type == "ROOMS") {
        std::cout << manager.ComputeRoomCount(hotel_name) << "\n";
      }
    }
  }
}


#endif //RED_BELT_C___HOTEL_MANAGER_H
