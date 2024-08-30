#include "read_file.h"

namespace delsm {

/* the buffer size for read phase */
#define DEFAULT_BLOCK_SIZE 1048576  // 1MB
int totl_size = 0;
int totl_file = 0;
int  chunk_num = 0;
void process_file(const char* filepath) {
  static unsigned char buf[DEFAULT_BLOCK_SIZE];
  // 这里添加处理文件的代码
  // printf("Processing file: %s\n", filepath);
  FILE* fp;
  if ((fp = fopen(filepath, "r")) == NULL) {
    perror("The reason is");
    exit(1);
  }
  int size = 0;
  while ((size = fread(buf, 1, DEFAULT_BLOCK_SIZE, fp)) != 0) {
    // 这里添加处理文件内容的代码
    // printf("Read %d bytes\n", size);
    totl_size += size;
    unsigned char* data = (unsigned char*)malloc(size);
    memcpy(data, buf, size);
    int leftlen = size;
    int leftoff = 0;
    while (leftoff < size) {
      int chunk_size = delsm::fastcdc_chunk_data(data + leftoff, leftlen);
      leftlen -= chunk_size;
        leftoff += chunk_size;
        chunk_num++;
    }
  }
  fclose(fp);
}

void process_directory(const char* dirpath) {
  DIR* dir = opendir(dirpath);
  if (dir == NULL) {
    perror("Failed to open directory");
    return;
  }

  struct dirent* entry;
  while ((entry = readdir(dir)) != NULL) {
    // 忽略当前目录和上一级目录
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    // 构建完整的文件路径
    char filepath[PATH_MAX];
    snprintf(filepath, sizeof(filepath), "%s/%s", dirpath, entry->d_name);

    struct stat path_stat;
    stat(filepath, &path_stat);

    if (S_ISDIR(path_stat.st_mode)) {
      // 如果是目录，则递归处理
      process_directory(filepath);
    } else {
      // 如果是文件，则处理文件
      process_file(filepath);
      totl_file++;
    }
  }

  closedir(dir);
}

void print_total_size() {
  printf("Total size: %d KB\n", totl_size / 1024 );
  printf("Total file: %d \n", totl_file);
    printf("Total chunk: %d \n", chunk_num);
    printf("Average chunk size: %d \n", totl_size / chunk_num);
}
void read_file(const char* dirpath) {
  delsm::fastcdc_init(4096);
  process_directory(dirpath);
}
}  // namespace delsm