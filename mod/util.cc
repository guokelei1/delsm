//
// Created by daiyi on 2020/02/02.
//

#include "util.h"

#include <util/mutexlock.h>
#include <x86intrin.h>

using std::to_string;

namespace delsm{

// 0 represents the initial leveldb, and 1 represents the leveldb of kv
// separation.
int MOD = 1;

leveldb::DBImpl* db;
leveldb::Env* env;

}  // namespace adgMod