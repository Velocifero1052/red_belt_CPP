#pragma once

#include "http_request.h"

#include <string_view>
#include <sstream>
#include <map>
#include <algorithm>

class Stats {
public:
  Stats();
  void AddMethod(std::string_view method);
  void AddUri(std::string_view uri);
  [[nodiscard]] const std::map<std::string_view, int>& GetMethodStats() const;
  [[nodiscard]] const std::map<std::string_view, int>& GetUriStats() const;
private:
  std::map<std::string_view, int> method_stats;
  std::map<std::string_view, int> uri_stats;
};

HttpRequest ParseRequest(std::string_view line);