#include "raii/temp_file.h"
#include "syscalls/file.h"
#include <sys/stat.h>

using namespace std;
using namespace raii;

namespace {
  const int PERMISSIONS = 0666;
}

temp_file::temp_file(const std::string &path)
  : file_path(path) {
    syscalls::mknod(file_path, S_IFREG | ::PERMISSIONS);
}

temp_file::~temp_file() {
  syscalls::unlink(file_path);
}
