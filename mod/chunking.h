#ifndef MOD_CHUNKING_H_
#define MOD_CHUNKING_H_

#include "isa-l_crypto/md5_mb.h"
#include "mod/util.h"

namespace delsm {
void fastcdc_init(uint32_t expectCS);
int fastcdc_chunk_data(unsigned char* p, int n);
}  // namespace delsm

#endif  // MOD_CHUNKING_H_