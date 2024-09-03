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

static const std::string kStaticString(4096, 'a');
static const std::string kStaticString2(1024, 'b');
// 创建一个静态的4096长度的字符串

string generate_value(uint64_t value) {
  string value_string = to_string(value);
  string result =
      string(value_size - value_string.length(), '2') + value_string;
  return std::move(result);
}
void test_file_open() {
   //const sds dir_name = "/home/gkl/testdata";
  const sds dir_name = "/home/gkl/testaa";

  delsm::read_file(dir_name);
  delsm::print_total_size();
}

int main() {
  Options options;
  options.create_if_missing = true;
  DB* db;
  leveldb::ReadOptions read_options;
  leveldb::WriteOptions write_options;
  write_options.sync = false;
  string db_location = "/home/gkl/testdb";

  string command = "rm -rf " + db_location;
  int rc;
  rc = system(command.c_str());

  Status status = DB::Open(options, db_location, &db);
  assert(status.ok() && "Open Error");

  delsm::read_options = read_options;
  delsm::write_options = write_options;

  delsm::Stats* stats = delsm::Stats::GetInstance();
  stats->StartTimer(0);
  stats->PauseTimer(0);
  printf("begin\n");
  stats->StartTimer(2);
  stats->StartTimer(3);
  double start_time = delsm::env->NowMicros();
  stats->PauseTimer(2);
  test_file_open();
  if (delsm::MOD > 0) {
    delsm::db->vlog->Sync();
  }
  stats->PauseTimer(3);
  double end_time = delsm::env->NowMicros();
  printf("end\n");
  double time_spent = (double)(end_time - start_time) ;
  printf("Execution time: %.2f seconds\n", time_spent);
  stats->ReportTime();
  return 0;
}