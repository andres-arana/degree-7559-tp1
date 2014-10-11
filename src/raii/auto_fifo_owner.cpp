#include "raii/auto_fifo_owner.h"
#include "syscalls/file.h"
#include <sys/stat.h>

using namespace std;
using namespace raii;

namespace {
  const int PERMISSIONS = 0666;
}

auto_fifo_owner::auto_fifo_owner(const string &path)
  : fifo_path(path) {
    syscalls::mknod(fifo_path, S_IFIFO | ::PERMISSIONS);
  }

string auto_fifo_owner::path() const {
  return fifo_path;
}

auto_fifo_owner::~auto_fifo_owner() {
  syscalls::unlink(fifo_path);
}
