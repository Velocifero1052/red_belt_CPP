
#include "http_request.h"
#include "stats.h"

#include <map>
#include <string_view>

using namespace std;

Stats::Stats() {
  for (const string_view& method: {"GET", "PUT", "POST", "DELETE", "UNKNOWN"}) {
    method_stats[method] = 0;
  }
  for (const string_view& uri: {"/", "/order", "/product", "/basket", "/help", "unknown"}) {
    uri_stats[uri] = 0;
  }
}

void Stats::AddMethod(std::string_view method) {
  if (method_stats.count(method) == 0 && method != "UNKNOWN")
    method_stats["UNKNOWN"]++;
  else
    method_stats[method]++;
}

void Stats::AddUri(std::string_view uri) {
  if (uri_stats.count(uri) == 0 && uri != "unknown")
    uri_stats["unknown"]++;
  else
    uri_stats[uri]++;
}

[[nodiscard]] const std::map<std::string_view, int>& Stats::GetMethodStats() const {
  return method_stats;
}

[[nodiscard]] const std::map<std::string_view, int>& Stats::GetUriStats() const {
  return uri_stats;
}

string_view trim(string_view in) {
  auto left = in.begin();
  for (;; ++left) {
    if (left == in.end())
      return string_view();
    if (!isspace(*left))
      break;
  }
  auto right = in.end() - 1;
  for (; right > left && isspace(*right); --right);
  return string_view(left, std::distance(left, right) + 1);
}

std::vector<std::string_view> Split(const std::string_view str_, const char delim = ' ') {
  auto str = trim(str_);
  std::vector<std::string_view> result;

  int indexCommaToLeftOfColumn = 0;
  int indexCommaToRightOfColumn = -1;

  for (int i=0;i<static_cast<int>(str.size());i++) {
    if (str[i] == delim) {
      indexCommaToLeftOfColumn = indexCommaToRightOfColumn;
      indexCommaToRightOfColumn = i;
      int index = indexCommaToLeftOfColumn + 1;
      int length = indexCommaToRightOfColumn - index;
      std::string_view column(str.data() + index, length);
      result.push_back(column);
    }
  }
  const std::string_view finalColumn(str.data() + indexCommaToRightOfColumn + 1, str.size() - indexCommaToRightOfColumn - 1);
  result.push_back(finalColumn);
  return result;
}

tuple<string_view, string_view, string_view> SplitRequestStringView(const std::string_view str_, const char delim = ' ') {
  auto str = trim(str_);
  std::array<std::string_view, 3> result;

  int indexCommaToLeftOfColumn = 0;
  int indexCommaToRightOfColumn = -1;
  int j = 0;
  for (int i=0; i<static_cast<int>(str.size()); i++) {
    if (str[i] == delim) {
      indexCommaToLeftOfColumn = indexCommaToRightOfColumn;
      indexCommaToRightOfColumn = i;
      int index = indexCommaToLeftOfColumn + 1;
      int length = indexCommaToRightOfColumn - index;
      std::string_view column(str.data() + index, length);
      result[j] = column;
      j++;
    }
  }
  const std::string_view finalColumn(str.data() + indexCommaToRightOfColumn + 1, str.size() - indexCommaToRightOfColumn - 1);
  result[2] = finalColumn;
  return {result[0], result[1], result[2]};
}

HttpRequest ParseRequest(std::string_view line_) {
  auto line = trim(line_);
  auto res = SplitRequestStringView(line);
  return {get<0>(res), get<1>(res), get<2>(res)};
}

Stats ServeRequests(istream& input) {
  Stats result;
  for (string line; getline(input, line);) {
    const HttpRequest req = ParseRequest(line);
    result.AddUri(req.uri);
    result.AddMethod(req.method);
  }
  return result;
}
