

#ifndef INDEX_H_
#define INDEX_H_


#include <glib.h>
#include "mod/util.h"

namespace delsm {


typedef unsigned char fingerprint[20];
const int index_chunk_size = 4096;

/* The buffer size > 2 * destor.rewrite_buffer_size */
/* All fingerprints that have been looked up in the index
 * but not been updated. */
struct simple_index{
    /* map a fingerprint to a queue of indexElem */
    /* Index all fingerprints in the index buffer. */
    GHashTable *buffered_fingerprints;
    /* The number of buffered chunks */
    int chunk_num;
};

struct chunk{
    fingerprint fp;
    int chunk_address;
    int length;
    int ref_count;
};


/*
 * The function is used to initialize memory structures of a fingerprint index.
 */
void init_index();

// 对给定的value进行去重操作，返回value的地址
uint64_t dedup(const Slice& key,const leveldb::Slice& value);

gboolean g_fingerprint_equal(const void* fp1, const void* fp2);

}  // namespace delsm

#endif  // INDEX_H_