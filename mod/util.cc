//
// Created by daiyi on 2020/02/02.
//

#include "util.h"

#include <util/mutexlock.h>
#include <x86intrin.h>

using std::to_string;

namespace delsm{

// 0 represents the initial leveldb,
//1 represents the leveldb of kv separation.
// 2 represents simple_index
int MOD = 1;

leveldb::DBImpl* db;
leveldb::Env* env;
leveldb::WriteOptions write_options;
leveldb::ReadOptions read_options;

}  // namespace adgMod