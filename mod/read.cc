#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <time.h>
#include <unistd.h>

#include "leveldb/comparator.h"
#include "leveldb/db.h"

#include "util.h"

using namespace leveldb;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::to_string;
using std::vector;
using namespace delsm;

int value_size = 1;

static const std::string kStaticString(1, 'a');
// 创建一个静态的4096长度的字符串

string generate_value(uint64_t value) {
  string value_string = to_string(value);
  string result =
      string(value_size - value_string.length(), '2') + value_string;
  return std::move(result);
}

int main() {
  Options options;
  options.create_if_missing = true;
  DB* db;
  leveldb::ReadOptions read_options;
  leveldb::WriteOptions write_options;
  write_options.sync = false;
  string db_location = "/mnt/d/testdb";

  string command = "rm -rf " + db_location;
  int rc;
  rc = system(command.c_str());

  Status status = DB::Open(options, db_location, &db);
  assert(status.ok() && "Open Error");
  printf("begin\n");

  double start_time = delsm::env->NowMicros();

  for (int i = 0; i < 102400; i++) {
    string key = to_string(i);
    status = db->Put(write_options, key, kStaticString);
    assert(status.ok() && "Put Error");
  }
  if (delsm::MOD > 0) {
    delsm::db->vlog->Sync();
  }

  double end_time = delsm::env->NowMicros();

  printf("end\n");
  double time_spent = (double)(end_time - start_time) / 1000000;
  printf("Execution time: %.2f seconds\n", time_spent);
}