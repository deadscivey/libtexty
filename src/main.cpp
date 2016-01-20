#include <glog/logging.h>
#include <folly/Format.h>
#include <folly/FileUtil.h>
#include <pthread.h>
#include <thread>
#include <chrono>
#include <bitset>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <atomic>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>

#include "pretty_print.h"
#include "hashing.h"
#include "texty/SimHasher.h"
#include "texty/ConstantSpaceSimHasher.h"

#include "texty/BloomFilter.h"

#include "util.h"
#include "shingle.h"

using texty::SimHasher;

using namespace std;

struct Thing {
  string name;
  Thing(string name): name(name){}
  Thing() {
    LOG(INFO) << "construct (" << name << ")";
  }
  ~Thing() {
    LOG(INFO) << "destruct (" << name << ")";
  }
};

struct IntBox {
  int x;
  IntBox(int x): x(x){}
};

using pretty_print::prettyLog;

struct AtomHaving {
  uint16_t x;
  std::atomic<uintptr_t> something {0};
  bool compare_exchange_strong(uintptr_t expect, uintptr_t next) {
    return something.compare_exchange_strong(expect, next);
  }
  void store(uintptr_t x) {
    something.store(x);
  }
  uintptr_t load() {
    return something.load();
  }
};

std::map<string, string> loadData() {
  std::vector<string> fnames;
  for (size_t i = 1; i < 5; i++) {
    ostringstream oss;
    oss << "text/doc" << i << ".txt";
    fnames.push_back(oss.str());
  }
  std::map<string, string> data;
  for (auto &fname: fnames) {
    string current;
    CHECK(folly::readFile(fname.c_str(), current));
    data[fname] = current;
  }
  return data;
}

int main() {
  auto docs = loadData();
  // std::random_device rd;
  auto seeded = 17;
  texty::ConstantSpaceSimHasher<1024, 30> hasher(
    [](const string &text, uint64_t seed) { return hashing::city_hash_64(text, seed); },
    seeded
  );
  texty::SimHasher<string> hasher2(
    [](const string &text, uint64_t seed) { return hashing::city_hash_64(text, seed); },
    seeded
  );
  std::map<string, vector<string>> shingled;
  for (auto &item: docs) {
    shingled[item.first] = shingle::shingle(item.second, 2);
  }
  std::map<string, uint64_t> hashed;
  for (auto &item: shingled) {
    hashed[item.first] = hasher2.hash(item.second);
  }
  for (auto &item: hashed) {
    for (auto &other: hashed) {
      if (item.first == other.first) {
        continue;
      }
      auto dist = util::hammingDistance(item.second, other.second);
      LOG(INFO) << item.first << " vs " << other.first << " -> " << dist;
    }
  }
  std::map<string, uint64_t> constantHashed;
  for (auto &item: docs) {
    constantHashed[item.first] = hasher.hash(item.second);
  }
  for (auto &item: constantHashed) {
    for (auto &other: constantHashed) {
      if (item.first == other.first) {
        continue;
      }
      auto dist = util::hammingDistance(item.second, other.second);
      LOG(INFO) << item.first << " vs " << other.first << " -> " << dist;
    }
  }

}

// int main() {
//   Post p1(1);
//   Post p2(1);
//   Barrier bar(2);

//   AtomHaving something;
//   thread t1([&p1, &p2, &bar, &something]() {
//     something.store(17);
//     p1.post();
//     p2.wait();
//     auto x = something.load();
//     LOG(INFO) << x;
//     bar.wait();
//   });
//   thread t2([&p1, &p2, &bar, &something]() {
//     p1.wait();
//     auto x = something.load();
//     LOG(INFO) << x;
//     uintptr_t expected = 17;
//     something.compare_exchange_strong(expected, 26);
//     p2.post();
//     bar.wait();
//   });
//   t1.join();
//   t2.join();
//   HPSystem::get()->init();
//   vector<int> nums {5, 3, 7};
//   prettyLog(nums);
//   HPList<int> ls;
//   ls.insert(5);
//   ls.insert(9);
//   auto snap = ls.badSnapshot();
//   prettyLog(snap);
// }
// int main() {
//   HPSystem::get()->init(chrono::milliseconds(10));
//   auto th1 = new Thing("joe");
//   auto th2 = new Thing("sam");
//   Post p1(1);
//   Post p2(1);
//   thread t1([&th1, &p1, &p2]() {
//     {
//       auto acc = HPSystem::get()->getHazard(th1);
//       p1.post();
//       this_thread::sleep_for(chrono::milliseconds(500));      
//     }
//     p2.wait();
//     this_thread::sleep_for(chrono::milliseconds(1000));
//   });
//   thread t2([&th1, &p1, &p2]() {
//     p1.wait();
//     HPSystem::get()->dealloc(th1);
//     LOG(INFO) << "here";
//     p2.post();
//     this_thread::sleep_for(chrono::milliseconds(1000));    
//   });
//   t1.join();
//   t2.join();
// }
