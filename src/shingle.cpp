#include "shingle.h"
#include <mitie/conll_tokenizer.h>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <utf8.h>
#include <utf8/unchecked.h>

#include <set>
#include <glog/logging.h>
#include "texty/ShingleView2.h"


using namespace std;

namespace shingle {


  vector<string> tokenize(const string &text) {
    texty::TokenView view(text);
    vector<string> result;
    auto it = view.begin();
    size_t prevLast = 99;
    for (;;) {
      LOG(INFO) << "here";      
      if (!it.good()) break;
      LOG(INFO) << "here";
      auto current = *it;
      if (current.second == prevLast) {
        break;
      }
      LOG(INFO) << "here";      

      prevLast = current.second;
      result.push_back(text.substr(current.first, current.second - current.first));
      LOG(INFO) << "here" << " : " << current.first << " -> " << current.second;
      it = it++;
    }
    LOG(INFO) << "done";
    return result;
  }
  // vector<string> tokenize(const string &text) {
  //   Utf8View view(text);
  //   vector<string> result;
  //   string current;
  //   current = "";
  //   for (auto cpp: view) {
  //     auto cp = cpp.second;
  //     if (cp > 255) continue;
  //     uint8_t c = (uint8_t) cp;
  //     char cc = c;
  //     if (cc == ' ' || isPunctuation(cc)) {
  //       result.push_back(current);
  //       current = "";
  //     } else {
  //       current.push_back(cc);
  //     }
  //   }
  //   if (current.size() > 0) {
  //     result.push_back(current);
  //   }
  //   return result;
  // }
  vector<string> shingle(const string &text, size_t n) {
    vector<string> result;
    texty::ShingleView2 view(text);
    auto it = view.begin();
    auto end = view.end();
    // for (auto item: view) {
    //   ostringstream oss;
    //   size_t i1 = std::get<0>(item).first;
    //   size_t i2 = std::get<0>(item).second;
    //   oss << text.substr(i1, i2 - i1);
    //   auto j1 = std::get<1>(item).first;
    //   auto j2 = std::get<1>(item).second;
    //   oss << " ";
    //   oss << text.substr(j1, j2 - j1);
    //   result.push_back(oss.str());      
    // }
    for (;;) {
      if (!it.good()) break;
      if (it == end) break;
      auto item = *it;
      ostringstream oss;
      size_t i1 = std::get<0>(item).first;
      size_t i2 = std::get<0>(item).second;
      oss << text.substr(i1, i2 - i1);
      auto j1 = std::get<1>(item).first;
      auto j2 = std::get<1>(item).second;
      oss << " ";
      oss << text.substr(j1, j2 - j1);
      result.push_back(oss.str());
      ++it;
    }
    return result;
  }
    // vector<string> result;
    // auto tokes = tokenize(text);
    // for (size_t i = 0; i <= (tokes.size() - n); i++) {
    //   ostringstream oss;
    //   for (size_t j = 0; j < n; j++) {
    //     oss << tokes[i + j];
    //     if (j != n - 1) {
    //       oss << " ";
    //     }
    //   }
    //   result.push_back(oss.str());
    // }
    // LOG(INFO) << "done";
    // return result;
  // }
  // vector<string> tokenize(const string &text) {
  //   string current, next;
  //   istringstream iss {text};
  //   mitie::conll_tokenizer toke(iss);
  //   vector<string> result;
  //   while (toke(current)) {
  //     auto notDone = toke(next);
  //     if (next.size() && next[0] == '\'') {
  //       current += next;
  //       result.push_back(current);
  //     } else {
  //       result.push_back(next);
  //     }
  //     if (!notDone) break;
  //     result.push_back(current);
  //   }
  //   return result;
  // }
}
