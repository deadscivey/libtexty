#pragma once
#include <string>
#include <sstream>
#include <glog/logging.h>
#include "util/pretty_print_predef.h"

namespace texty { namespace util { namespace pretty_print {

template<>
struct PrettyPrinter<std::string> {
  static void pprint(std::ostringstream &oss, const std::string &ref) {
    oss << "'" << ref << "'";
  }
};

template<typename T>
struct PrettyPrinter<std::vector<T>> {
  static void pprint(std::ostringstream &oss, const std::vector<T> &ref) {
    oss << "vector([ ";
    if (!ref.empty()) {
      size_t last = ref.size() - 1;
      for (size_t i = 0; i <= last; i++) {
        prettyPrint(oss, ref[i]);
        if (i != last) {
          oss << ", ";
        }
      }
    }
    oss << " ])";
  }
};

template<typename T>
void prettyLog(const T &ref) {
  std::string msg = prettyPrint(ref);
  LOG(INFO) << msg;
}

}}} // texty::util::pretty_print

