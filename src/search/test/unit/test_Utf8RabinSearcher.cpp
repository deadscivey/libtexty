#include <gtest/gtest.h>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <glog/logging.h>
#include "search/Utf8RabinSearcher.h"
#include "string_views/ByteStringWindow.h"
#include "string_views/Utf8View.h"

using namespace std;
using namespace texty::search;
using namespace texty::string_views;

TEST(TestUtf8RabinSearcher, Basic) {
  map<size_t, unordered_map<uint64_t, Utf8View>> hashes;
  vector<string> toFind {
    "fis", "dog", "are"
  };
  const uint32_t ALPHA = 101;
  const uint64_t MOD_N = 5120000;
  RabinFingerprinter finger(ALPHA, MOD_N);
  for (auto &item: toFind) {
    auto hashed = finger.hash(item);
    LOG(INFO) << "\t[ " << item.size() << " ]  :  " << hashed;
    ByteStringWindow window(item);
    if (!hashes.count(item.size())) {
      hashes.insert(std::make_pair(
        item.size(), 
        unordered_map<uint64_t, Utf8View> {}
      ));
    }
    hashes[item.size()].insert(std::make_pair(
      hashed, window.asUtf8View()
    ));
  }
  Utf8RabinSearcher searcher(ALPHA, hashes);
  string toSearch = "fishes are extremely fish, are very very very bad";
  {
    ByteStringWindow window(toSearch);
    ostringstream oss;
    for (auto cp: window.asUtf8View()) {
      oss << cp << " ";
    }
    LOG(INFO) << oss.str();
  }
  ByteStringWindow window(toSearch);
  auto found = searcher.findAll(window.asUtf8View());
  for (auto &item: found) {
    ostringstream oss;
    oss << "{ ";
    for (auto cp: item.first) {
      oss << cp << " ";
    }
    oss << " } : [ " << item.second.first << ", " << item.second.second << " ]";
    LOG(INFO) << oss.str();
  }
  EXPECT_EQ(3, found.size());
  LOG(INFO) << "\n\tFOUND\n\n";
}
