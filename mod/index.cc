#include "index.h"

#include <cstdint>

#include "isa-l_crypto/mh_sha1.h"

namespace delsm {

struct simple_index sindex;
struct mh_sha1_ctx* ctx;



void init_index() {
  // 初始化哈希表
  sindex.buffered_fingerprints =
      g_hash_table_new_full(g_int64_hash, g_fingerprint_equal, NULL, NULL);
  sindex.chunk_num = 0;

  // 初始化哈希上下文

  ctx = (struct mh_sha1_ctx*)malloc(sizeof(struct mh_sha1_ctx));
}

uint64_t dedup(const Slice& key, const leveldb::Slice& value) {
  // 创建临时块
  chunk* tmpchunk = (struct chunk*)malloc(sizeof(struct chunk));
  mh_sha1_init(ctx);
  mh_sha1_update_base(ctx, value.data(), value.size());
  mh_sha1_finalize_base(ctx, tmpchunk->fp);

  // 在哈希表中查找指纹，若找到，则直接返回address，并销毁临时快
  // 若没有找到，则插入临时块，调用vlog_record函数
  chunk* tq = (struct chunk*)g_hash_table_lookup(sindex.buffered_fingerprints,
                                                 tmpchunk->fp);
  if (tq != NULL) {
    free(tmpchunk);
    tq->ref_count++;
    return tq->chunk_address;
  } else {
    tmpchunk->length = value.size();
    tmpchunk->ref_count = 1;
    uint64_t address = delsm::db->vlog->AddRecord(key, value);
    tmpchunk->chunk_address = address;
    g_hash_table_insert(sindex.buffered_fingerprints, &tmpchunk->fp, tmpchunk);
    sindex.chunk_num++;
    return address;
  }
}

gboolean g_fingerprint_equal(const void* void_fp1, const void* void_fp2) {
  fingerprint* fp1 = (fingerprint*)void_fp1;
  fingerprint* fp2 = (fingerprint*)void_fp2;
  return !memcmp(fp1, fp2, sizeof(fingerprint));
}

}  // namespace delsm