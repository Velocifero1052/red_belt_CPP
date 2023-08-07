#include <array>
#include <string_view>

using std::array;
using std::string_view;

const size_t SIZE = 10;

int main() {

  array<char, SIZE> a = {'a','a','a','a','a','a','a','a','a','a'};
  auto s = string_view(a.data(), a.size());
  auto b = string_view(a.data(), a.size());
  auto c = string_view(a.data(), a.size());
  auto d = string_view(a.data(), a.size());
  auto e =  string_view(a.begin());
  auto f =  string_view(&a[0], a.size());

  return 0;
}