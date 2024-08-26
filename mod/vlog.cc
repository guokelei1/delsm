//
// Created by daiyi on 2020/03/23.
//

#include "vlog.h"
#include "util.h"

#include <fcntl.h>
#include <sys/stat.h>

#include "util/coding.h"


using std::string;

const int buffer_size_max = 300 * 1024;

namespace delsm {

VLog::VLog(const std::string& vlog_name) : writer(nullptr), reader(nullptr) {
  delsm::env->NewWritableFile(vlog_name, &writer);
  delsm::env->NewRandomAccessFile(vlog_name, &reader);
  buffer.reserve(buffer_size_max * 2);
  struct ::stat file_stat;
  ::stat(vlog_name.c_str(), &file_stat);
  vlog_size = file_stat.st_size;
  //printf("vlog_size:%ld\n", vlog_size);
}

uint64_t VLog::AddRecord(const Slice& key, const Slice& value) {
  PutLengthPrefixedSlice(&buffer, key);
  PutVarint32(&buffer, value.size());
  uint64_t result = vlog_size + buffer.size();
  buffer.append(value.data(), value.size());
  //printf("AddRecord:%ld\n", result);
  return result;
}

string VLog::ReadRecord(uint64_t address, uint32_t size) {
  if (address >= vlog_size)
  {
   printf("Read from buffer,address:%ld\n", address);
    return string(buffer.c_str() + address - vlog_size, size);
  }
 // printf("Read from disk,address:%ld\n", address);
  char* scratch = new char[size];
  Slice value;
  reader->Read(address, size, &value, scratch);
  string result(value.data(), value.size());
  delete[] scratch;
  return result;
}

void VLog::Flush() {
  if (buffer.empty()) return;

  vlog_size += buffer.size();
  writer->Append(buffer);
  writer->Flush();
  buffer.clear();
  buffer.reserve(buffer_size_max * 2);
}

void VLog::Sync() {
  Flush();
  writer->Sync();
}

VLog::~VLog() { Flush(); }

}  // namespace adgMod