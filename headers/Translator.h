//
// Created by Rakhmon Radjabov on 09/08/23.
//

#ifndef RED_BELT_C___TRANSLATOR_H
#define RED_BELT_C___TRANSLATOR_H
#include <string_view>
#include <string>
#include <map>


class Translator {
public:
  void Add(std::string_view source_, std::string_view target_) {

    std::string source(source_.begin(), source_.end());
    std::string target(target_.begin(), target_.end());

    if (data.count({source_.begin(), source_.end()}) == 0) {
      auto it = data.insert({source, target}).first;
      forward[it->first] = it->second;
      backward[it->second] = it->first;
    } else {

      std::string old_target = data.at(source);
      backward.erase(old_target);
      auto it = data.insert_or_assign(source, target).first;
      forward[it->first] = it->second;
      backward[it->second] = it->first;

    }

  }
  std::string_view TranslateForward(std::string_view source) const {

    if (forward.count(source) != 0) {
      return forward.at(source);
    }  else {
      return "";
    }
  }
  std::string_view TranslateBackward(std::string_view target) const {
    if (backward.count(target) != 0) {
      return backward.at(target);
    } else {
      return "";
    }
  }

private:

  std::map<std::string, std::string> data;
  std::map<std::string_view, std::string_view> forward;
  std::map<std::string_view, std::string_view> backward;

};

#endif //RED_BELT_C___TRANSLATOR_H
