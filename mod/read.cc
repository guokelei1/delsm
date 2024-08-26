#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <unistd.h>

#include "leveldb/comparator.h"
#include "leveldb/db.h"

using namespace leveldb;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::to_string;
using std::vector;

int value_size = 10;

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
  string db_location = "/tmp/testdb";
  Status status = DB::Open(options, db_location, &db);
  assert(status.ok() && "Open Error");

  string value = generate_value(0);
  string key = "0000000000891035";
  status = db->Put(write_options, key, value);
  string read_value;
  status = db->Get(read_options, key, &read_value);
  cout << "Read Value: " << read_value << endl;
  string key2 = "891035";
  status = db->Get(read_options, key2, &read_value);
  cout << "Read Value: " << read_value << endl;
}