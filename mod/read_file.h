#ifndef LEVELDB_READ_FILE_H
#define LEVELDB_READ_FILE_H


#include "mod/util.h"
namespace delsm{


void process_file(const char *filepath);
void process_directory(const char *dirpath) ;

void print_total_size();

void read_file(const char* dirpath);

}

#endif //LEVELDB_READ_FILE_Hs