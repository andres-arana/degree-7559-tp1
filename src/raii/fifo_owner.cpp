#include "raii/fifo_owner.h"
#include "syscalls/file.h"
#include <sys/stat.h>

using namespace std;
using namespace raii;

namespace {
  const int PERMISSIONS = 0666;
}

fifo_owner::fifo_owner(const string &path)
  : fifo_path(path) {
    syscalls::mknod(fifo_path, S_IFIFO | ::PERMISSIONS);
  }

string fifo_owner::path() const {
  return fifo_path;
}

fifo_owner::~fifo_owner() {
  syscalls::unlink(fifo_path);
}


