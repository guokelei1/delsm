//
// Created by daiyi on 2020/02/02.
// a collection of global variables and flags/states/parameters

#ifndef LEVELDB_UTIL_H
#define LEVELDB_UTIL_H

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "db/db_impl.h"
#include "leveldb/slice.h"
#include "leveldb/env.h"
#include <x86intrin.h>



namespace delsm {

// 0 represents the initial leveldb, and 1 represents the leveldb of kv separation.
extern int MOD;

extern leveldb::DBImpl* db;
extern leveldb::Env* env;
}


#endif //LEVELDB_UTIL_H
