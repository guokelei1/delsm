//
// Created by daiyi on 2020/02/02.
// a collection of global variables and flags/states/parameters

#ifndef LEVELDB_UTIL_H
#define LEVELDB_UTIL_H

#include "db/db_impl.h"
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <dirent.h>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include <x86intrin.h>

#include "leveldb/env.h"
#include "leveldb/slice.h"

#include "mod/chunking.h"
#include "mod/read_file.h"
#include "mod/sds.h"
#include "mod/timer.h"

using std::string;

namespace delsm {

// 0 represents the initial leveldb, and 1 represents the leveldb of kv
// separation.
extern int MOD;

extern leveldb::DBImpl* db;
extern leveldb::Env* env;
extern leveldb::WriteOptions write_options;
extern leveldb::ReadOptions read_options;

}  // namespace delsm

#endif  // LEVELDB_UTIL_H
